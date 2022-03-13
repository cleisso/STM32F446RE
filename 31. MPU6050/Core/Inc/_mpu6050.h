/*
 * _mpu6050.h
 *
 *  Created on: Mar 10, 2022
 *      Author: ctbri
 */

/* The register map is provided at
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * Mapping of the different gyro and accelero configurations:
 *
 * GYRO_CONFIG_[0,1,2,3] range = +- [250, 500,1000,2000] °/s
 *                       sensi =    [131,65.5,32.8,16.4] bit/(°/s)
 *
 * ACC_CONFIG_[0,1,2,3] range = +- [    2,   4,   8,  16] times the gravity (9.81m/s²)
 *                      sensi =    [16384,8192,4096,2048] bit/gravity
*/

#ifndef INC__MPU6050_H_
#define INC__MPU6050_H_



#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "i2c.h"

#include "math.h"



#define MPU6050_ADDR                  		((0x68) << 1)
#define MPU6050_SMPLRT_DIV_REGISTER   		(0x19)
#define MPU6050_CONFIG_REGISTER       		(0x1a)
#define MPU6050_GYRO_CONFIG_REGISTER  		(0x1b)
#define MPU6050_ACCEL_CONFIG_REGISTER 		(0x1c)
#define MPU6050_PWR_MGMT_1_REGISTER   		(0x6b)

#define MPU6050_GYRO_OUT_REGISTER     		(0x43)
#define MPU6050_ACCEL_OUT_REGISTER    		(0x3B)

#define RAD_2_DEG             				(57.29578) // [°/rad]
#define CALIB_OFFSET_NB_MES   				(500)
#define TEMP_LSB_2_DEGREE     				(340.0)    // [bit/celsius]
#define TEMP_LSB_OFFSET       				(12412.0)

#define DEFAULT_GYRO_COEFF    				(0.98)



typedef struct
{
	I2C_HandleTypeDef *hi2c;

	float gyro_lsb_to_degsec, acc_lsb_to_g;
	float gyroXoffset, gyroYoffset, gyroZoffset;
	float accXoffset, accYoffset, accZoffset;
    float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
    float angleAccX, angleAccY;
    float angleX, angleY, angleZ;
    long preInterval;
    float filterGyroCoef;		// complementary filter coefficient to balance gyro vs accelero data to get angle
} mpu6050_t;



uint8_t MPU6050_begin (mpu6050_t *mpu6050);
uint8_t MPU6050_writeData (mpu6050_t *mpu6050, uint8_t reg, uint8_t data);
uint8_t MPU6050_readData (mpu6050_t *mpu6050, uint8_t reg, uint8_t *buffer, uint8_t size);

void MPU6050_calcOffset (mpu6050_t *mpu6050, uint8_t is_calc_gyro, uint8_t is_calc_acc);

uint8_t MPU6050_setGyroConfig (mpu6050_t *mpu6050, int16_t config_num);
uint8_t MPU6050_setAccConfig (mpu6050_t *mpu6050, int16_t config_num);
void MPU6050_setGyroOffsets (mpu6050_t *mpu6050, float x, float y, float z);
void MPU6050_setAccOffsets (mpu6050_t *mpu6050, float x, float y, float z);

void MPU6050_setFilterGyroCoef (mpu6050_t *mpu6050, float gyro_coeff);
void MPU6050_setFilterAccCoef (mpu6050_t *mpu6050, float acc_coeff);

void MPU6050_fetchData (mpu6050_t *mpu6050);
void MPU6050_update (mpu6050_t *mpu6050);



#define MPU6050_calcGyroOffsets(mpu6050_pointer)	(MPU6050_calcOffset(mpu6050_pointer, 1, 0))
#define MPU6050_calcAccOffsets(mpu6050_pointer)		(MPU6050_calcOffset(mpu6050_pointer, 0, 1))

#define MPU6050_GyroXoffset(mpu6050)				((mpu6050).gyroXoffset)
#define MPU6050_GyroYoffset(mpu6050)				((mpu6050).gyroYoffset)
#define MPU6050_GyroZoffset(mpu6050)				((mpu6050).gyroZoffset)

#define MPU6050_AccXoffset(mpu6050)					((mpu6050).accXoffset)
#define MPU6050_AccYoffset(mpu6050)					((mpu6050).accYoffset)
#define MPU6050_AccZoffset(mpu6050)					((mpu6050).accZoffset)

#define MPU6050_getFilterGyroCoef(mpu6050)			((mpu6050).filterGyroCoef)
#define MPU6050_getFilterAccCoef(mpu6050)			(1.0 - (mpu6050).filterGyroCoef)

#define MPU6050_getTemp(mpu6050)					((mpu6050).temp)

#define MPU6050_getAccX(mpu6050)					((mpu6050).accX)
#define MPU6050_getAccY(mpu6050)					((mpu6050).accY)
#define MPU6050_getAccZ(mpu6050)					((mpu6050).accZ)

#define MPU6050_getGyroX(mpu6050)					((mpu6050).gyroX)
#define MPU6050_getGyroY(mpu6050)					((mpu6050).gyroY)
#define MPU6050_getGyroZ(mpu6050)					((mpu6050).gyroZ)

#define MPU6050_getAccAngleX(mpu6050)				((mpu6050).angleAccX)
#define MPU6050_getAccAngleY(mpu6050)				((mpu6050).angleAccY)

#define MPU6050_getAngleX(mpu6050)					((mpu6050).angleX)
#define MPU6050_getAngleY(mpu6050)					((mpu6050).angleY)
#define MPU6050_getAngleZ(mpu6050)					((mpu6050).angleZ)

#endif /* INC__MPU6050_H_ */
