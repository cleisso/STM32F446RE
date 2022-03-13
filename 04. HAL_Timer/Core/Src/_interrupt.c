/*
 * _interrupt.c
 *
 *  Created on: Jan 11, 2022
 *      Author: ctbri
 */

#include "_interrupt.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
