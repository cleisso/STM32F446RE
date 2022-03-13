/*
 * _app.c
 *
 *  Created on: Feb 13, 2022
 *      Author: ctbri
 */

#include "_app.h"

uint8_t flagB1Pin = 0;
uint8_t flagB2Pin = 0;

void _main (void)
{

	while (1)
	{
		if (flagB1Pin)
		{
			for (uint8_t i = 0; i < 5; ++i)
			{
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
				HAL_Delay(500);
			}

			flagB1Pin = 0;
		}

		if (flagB2Pin)
		{
			for (uint8_t i = 0; i < 5; ++i)
			{
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
				HAL_Delay(100);
			}

			flagB2Pin = 0;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == B1_Pin)
		flagB1Pin = 1;

	if (GPIO_Pin == B2_Pin)
		flagB2Pin = 1;
}
