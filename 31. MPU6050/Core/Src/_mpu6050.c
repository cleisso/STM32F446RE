/*
 * _mpu6050.c
 *
 *  Created on: Mar 10, 2022
 *      Author: ctbri
 */

/* MPU6050_light library for Arduino
 *
 * Authors: Romain JL. Fétick (github.com/rfetick)
 *              simplifications and corrections
 *          Tockn (github.com/tockn)
 *              initial author (v1.5.2)
 */

#include "_mpu6050.h"

static void delay (uint8_t _delay)
{
	HAL_Delay(_delay);
}

static uint32_t millis ()
{
	return HAL_GetTick();
}

/* INIT and BASIC FUNCTIONS */
uint8_t MPU6050_begin (mpu6050_t *mpu6050)
{
	MPU6050_setFilterGyroCoef(mpu6050, DEFAULT_GYRO_COEFF);
	MPU6050_setGyroOffsets(mpu6050, 0, 0, 0);
	MPU6050_setAccOffsets(mpu6050, 0, 0, 0);
	MPU6050_writeData(mpu6050, MPU6050_SMPLRT_DIV_REGISTER, 0x00);
	MPU6050_writeData(mpu6050, MPU6050_CONFIG_REGISTER, 0x00);
	MPU6050_setGyroConfig(mpu6050, 1);
	MPU6050_setAccConfig(mpu6050, 0);

	uint8_t status = MPU6050_writeData(mpu6050, MPU6050_PWR_MGMT_1_REGISTER, 0x01);

	MPU6050_update(mpu6050);

	mpu6050->angleX = MPU6050_getAccAngleX(*mpu6050);
	mpu6050->angleY = MPU6050_getAccAngleY(*mpu6050);
	mpu6050->preInterval = millis();

	return status;
}

uint8_t MPU6050_writeData (mpu6050_t *mpu6050, uint8_t reg, uint8_t data)
{
	uint8_t buffer[] = {reg, data};
	int8_t status = 0;

	if (mpu6050->hi2c == NULL)
		status = 1;
	else if (HAL_I2C_Master_Transmit(mpu6050->hi2c, MPU6050_ADDR, buffer, sizeof(buffer), 5) != HAL_OK)
		status = 1;

	// 0 if success
	return status;
}

// This method is not used internaly, maybe by user...
uint8_t MPU6050_readData (mpu6050_t *mpu6050, uint8_t reg, uint8_t *buffer, uint8_t size)
{
	uint8_t status = 0;

	if (mpu6050->hi2c == NULL)
	{
		status = 1;
	}
	else
	{
		HAL_I2C_Master_Transmit(mpu6050->hi2c, MPU6050_ADDR | 0x01, &reg, 1, 5);

		if (HAL_I2C_Master_Receive(mpu6050->hi2c, MPU6050_ADDR | 0x01, buffer, size, 5) != HAL_OK)
			status = 1;
	}

	return status;
}

/* SETTER */
uint8_t MPU6050_setGyroConfig (mpu6050_t *mpu6050, int16_t config_num)
{
	int8_t status;

	switch (config_num)
	{
		case 0: // range = +- 250 °/s
			mpu6050->gyro_lsb_to_degsec = 131.0;
			status = MPU6050_writeData(mpu6050, MPU6050_GYRO_CONFIG_REGISTER, 0x00);
			break;

		case 1: // range = +- 500 °/s
			mpu6050->gyro_lsb_to_degsec = 65.5;
			status = MPU6050_writeData(mpu6050, MPU6050_GYRO_CONFIG_REGISTER, 0x08);
			break;

		case 2: // range = +- 1000 °/s
			mpu6050->gyro_lsb_to_degsec = 32.8;
			status = MPU6050_writeData(mpu6050, MPU6050_GYRO_CONFIG_REGISTER, 0x10);
			break;

		case 3: // range = +- 2000 °/s
			mpu6050->gyro_lsb_to_degsec = 16.4;
			status = MPU6050_writeData(mpu6050, MPU6050_GYRO_CONFIG_REGISTER, 0x18);
			break;

		default: // error
			status = 1;
			break;
	}

	return status;
}

uint8_t MPU6050_setAccConfig (mpu6050_t *mpu6050, int16_t config_num)
{
	int8_t status;

	switch (config_num)
	{
		case 0: // range = +- 2 g
			mpu6050->acc_lsb_to_g = 16384.0;
			status = MPU6050_writeData(mpu6050, MPU6050_ACCEL_CONFIG_REGISTER, 0x00);
			break;

		case 1: // range = +- 4 g
			mpu6050->acc_lsb_to_g = 8192.0;
			status = MPU6050_writeData(mpu6050, MPU6050_ACCEL_CONFIG_REGISTER, 0x08);
			break;

		case 2: // range = +- 8 g
			mpu6050->acc_lsb_to_g = 4096.0;
			status = MPU6050_writeData(mpu6050, MPU6050_ACCEL_CONFIG_REGISTER, 0x10);
			break;

		case 3: // range = +- 16 g
			mpu6050->acc_lsb_to_g = 2048.0;
			status = MPU6050_writeData(mpu6050, MPU6050_ACCEL_CONFIG_REGISTER, 0x18);
			break;

		default: // error
			status = 1;
			break;
	}

	return status;
}

void MPU6050_setGyroOffsets (mpu6050_t *mpu6050, float x, float y, float z)
{
	mpu6050->gyroXoffset = x;
	mpu6050->gyroYoffset = y;
	mpu6050->gyroZoffset = z;
}

void MPU6050_setAccOffsets (mpu6050_t *mpu6050, float x, float y, float z)
{
	mpu6050->accXoffset = x;
	mpu6050->accYoffset = y;
	mpu6050->accZoffset = z;
}

void MPU6050_setFilterGyroCoef (mpu6050_t *mpu6050, float gyro_coeff)
{
	if ((gyro_coeff < 0) || (gyro_coeff > 1))
	{
		gyro_coeff = DEFAULT_GYRO_COEFF;
	}	// prevent bad gyro coeff, should throw an error...

	mpu6050->filterGyroCoef = gyro_coeff;
}

void MPU6050_setFilterAccCoef (mpu6050_t *mpu6050, float acc_coeff)
{
	MPU6050_setFilterGyroCoef(mpu6050, 1.0 - acc_coeff);
}

/* CALC OFFSET */
void MPU6050_calcOffset (mpu6050_t *mpu6050, uint8_t is_calc_gyro, uint8_t is_calc_acc)
{
	if(is_calc_gyro)
	{
		MPU6050_setGyroOffsets(mpu6050, 0, 0, 0);
	}

	if(is_calc_acc)
	{
		MPU6050_setAccOffsets(mpu6050, 0, 0, 0);
	}

	// 3*acc, 3*gyro
	float ag[6] = {0,0,0,0,0,0};

	for(int i = 0; i < CALIB_OFFSET_NB_MES; i++)
	{
		MPU6050_fetchData(mpu6050);

		ag[0] += mpu6050->accX;
		ag[1] += mpu6050->accY;
		ag[2] += (mpu6050->accZ - 1.0);
		ag[3] += mpu6050->gyroX;
		ag[4] += mpu6050->gyroY;
		ag[5] += mpu6050->gyroZ;

		// wait a little bit between 2 measurements
		delay(1);
	}

	if(is_calc_acc)
	{
		mpu6050->accXoffset = ag[0] / CALIB_OFFSET_NB_MES;
		mpu6050->accYoffset = ag[1] / CALIB_OFFSET_NB_MES;
		mpu6050->accZoffset = ag[2] / CALIB_OFFSET_NB_MES;
	}

	if(is_calc_gyro)
	{
		mpu6050->gyroXoffset = ag[3] / CALIB_OFFSET_NB_MES;
		mpu6050->gyroYoffset = ag[4] / CALIB_OFFSET_NB_MES;
		mpu6050->gyroZoffset = ag[5] / CALIB_OFFSET_NB_MES;
	}
}

/* UPDATE */
void MPU6050_fetchData (mpu6050_t *mpu6050)
{
	uint8_t reg = MPU6050_ACCEL_OUT_REGISTER;
	uint8_t buffer[14];
	MPU6050_readData(mpu6050, reg, buffer, sizeof(buffer));

	int16_t rawData[7]; // [ax,ay,az,temp,gx,gy,gz]

	for(int i = 0; i < (sizeof(rawData) / sizeof(rawData[0])); i++)
	{
		rawData[i] = (int16_t)(buffer[i*2]) << 8;
		rawData[i] = rawData[i] | (int16_t)(buffer[i*2 + 1]);
	}

	mpu6050->accX = ((float)rawData[0]) / mpu6050->acc_lsb_to_g - mpu6050->accXoffset;
	mpu6050->accY = ((float)rawData[1]) / mpu6050->acc_lsb_to_g - mpu6050->accYoffset;
	mpu6050->accZ = ((float)rawData[2]) / mpu6050->acc_lsb_to_g - mpu6050->accZoffset;

	mpu6050->temp = (rawData[3] + TEMP_LSB_OFFSET) / TEMP_LSB_2_DEGREE;

	mpu6050->gyroX = ((float)rawData[4]) / mpu6050->gyro_lsb_to_degsec - mpu6050->gyroXoffset;
	mpu6050->gyroY = ((float)rawData[5]) / mpu6050->gyro_lsb_to_degsec - mpu6050->gyroYoffset;
	mpu6050->gyroZ = ((float)rawData[6]) / mpu6050->gyro_lsb_to_degsec - mpu6050->gyroZoffset;
}

void MPU6050_update (mpu6050_t *mpu6050)
{
	// retrieve raw data
	MPU6050_fetchData(mpu6050);

	// process data to get angles
	float sgZ = (mpu6050->accZ >= 0) - (mpu6050->accZ < 0);

	mpu6050->angleAccX = atan2(mpu6050->accY, sgZ * sqrt(mpu6050->accZ * mpu6050->accZ + mpu6050->accX * mpu6050->accX)) * RAD_2_DEG;
	mpu6050->angleAccY = -atan2(mpu6050->accX, sqrt(mpu6050->accZ * mpu6050->accZ + mpu6050->accY * mpu6050->accY)) * RAD_2_DEG;

	uint32_t Tnew = millis();

	float dt = (Tnew - mpu6050->preInterval) * 1e-3;
	mpu6050->preInterval = Tnew;

	mpu6050->angleX = (mpu6050->filterGyroCoef * (mpu6050->angleX + mpu6050->gyroX * dt)) + ((1.0 - mpu6050->filterGyroCoef)*mpu6050->angleAccX);
	mpu6050->angleY = (mpu6050->filterGyroCoef * (mpu6050->angleY + mpu6050->gyroY * dt)) + ((1.0 - mpu6050->filterGyroCoef)*mpu6050->angleAccY);
	mpu6050->angleZ += (mpu6050->gyroZ * dt);
}
