/*
 * app.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ctbri
 */

#include "app.h"

void _main (void)
{
	uint8_t flagLed = 0;
	uint8_t flagButton = 0;
	uint32_t timeButton = 0;

	while (1)
	{
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
		{
			if (timeButton < 100000)
				++timeButton;
			else
				timeButton = 0, flagButton = 1;
		}
		else
		{
			if (flagButton == 1)
			{
				if (timeButton > 0)
					--timeButton;
				else
				{
					flagButton = 0;

					if (flagLed == 1)
					{
						flagLed = 0;
						HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					}
					else
					{
						flagLed = 1;
						HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					}
				}
			}
			else
			{
				timeButton = 0;
			}
		}

	}
}
