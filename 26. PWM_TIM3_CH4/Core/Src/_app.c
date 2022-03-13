/*
 * _app.c
 *
 *  Created on: Mar 3, 2022
 *      Author: ctbri
 */

#include "_app.h"

void _main (void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	htim3.Instance->CCR4 = 50;

	while (1)
	{

	}
}
