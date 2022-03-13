/*
 * app.c
 *
 *  Created on: Jan 6, 2022
 *      Author: ctbri
 */

#include "app.h"

void _main (void)
{
	while (1)
	{
		for (uint8_t i = 1; i <= 5; ++i)
		{
			for (uint8_t j = 0; j < 5; ++j)
			{
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				HAL_Delay(50*i);
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
				HAL_Delay(50*i);
			}
		}
	}
}
