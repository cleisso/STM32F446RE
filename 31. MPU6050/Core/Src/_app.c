/*
 * _app.c
 *
 *  Created on: Mar 10, 2022
 *      Author: ctbri
 */

#include "_app.h"

void _main (void)
{
	uint32_t timer = HAL_GetTick();

	mpu6050_t mpu6050 = {&hi2c1};

	MPU6050_begin(&mpu6050);
	MPU6050_calcOffset(&mpu6050, 1, 1);

	while (1)
	{
		MPU6050_update(&mpu6050);

		if ((HAL_GetTick() - timer) > 1000)
		{
			float teste;

			// Ler Acc X, Y e Z
			teste = MPU6050_getAccX(mpu6050);
			teste = MPU6050_getAccY(mpu6050);
			teste = MPU6050_getAccZ(mpu6050);

			// Ler Gyro X, Y e Z
			teste = MPU6050_getGyroX(mpu6050);
			teste = MPU6050_getGyroY(mpu6050);
			teste = MPU6050_getGyroZ(mpu6050);

			// Ler Angulo X, Y e Z
			teste = MPU6050_getAngleX(mpu6050);
			teste = MPU6050_getAngleY(mpu6050);
			teste = MPU6050_getAngleZ(mpu6050);

			// Ler Acc. Angulo X e Y
			teste = MPU6050_getAccAngleX(mpu6050);
			teste = MPU6050_getAccAngleY(mpu6050);

			// Ler temperatura
			teste = MPU6050_getTemp(mpu6050);

			teste = teste + 1;
		}
	}
}
