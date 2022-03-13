/*
 * app.c
 *
 *  Created on: Jan 11, 2022
 *      Author: ctbri
 */

/* Para controlar o DutyCycle de um PWM, deve-se realizar a configuração do respectivo registrador CCRx
 * (onde x corresponde ao número do canal, podendo ser de 1 à 4). O seu valor irá variar de 0 (0%) ao
 * valor configurado no Counter Period (neste caso, 1000, equivalente a 100%). Ao modificar o conteúdo
 * de CCRx, o PWM é atualizado automaticamente.
 */

#include "app.h"

void _main (void)
{
	uint8_t dutyCycle = 0;
	uint8_t flagButton = 0;
	uint32_t timeButton = 0;

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	while (1)
	{
		if (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
		{
			if (!timeButton && !flagButton)
				timeButton = HAL_GetTick();

			if ((HAL_GetTick() - timeButton) > 10)
			{
				flagButton = 1;
				timeButton = 0;
			}
		}
		else if (flagButton)
		{
			if (!timeButton && flagButton)
				timeButton = HAL_GetTick();

			if ((HAL_GetTick() - timeButton) > 10)
			{
				flagButton = 0;
				timeButton = 0;

				dutyCycle = dutyCycle + 10;
				if (dutyCycle > 100)
					dutyCycle = 0;

				htim1.Instance->CCR1 = (htim1.Init.Period + 1)*(dutyCycle/100.0);
			}
		}
		else
			timeButton = 0;

	}
}
