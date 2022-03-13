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

	SERVOMOTOR_ANGLE(0);

	while (1)
	{
		for (int i = 0; i <=180; ++i)
		{
			SERVOMOTOR_ANGLE(i);
			HAL_Delay(20);
		}

		for (int i = 180; i >= 0; --i)
		{
			SERVOMOTOR_ANGLE(i);
			HAL_Delay(20);
		}
	}
}
