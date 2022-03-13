/*
 * _interrupt.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ctbri
 */

#include "_interrupt.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == B1_Pin)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
			for (uint16_t i = 0; i < 10000; ++i);
	}
}
