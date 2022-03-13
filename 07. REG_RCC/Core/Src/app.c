/*
 * app.c
 *
 *  Created on: Jan 23, 2022
 *      Author: ctbri
 */

#include "app.h"

void _main (void)
{
	InicializaRCC();
	InicializaGPIO();

	while (1)
	{
		HAL_GPIO_WritePin(LED_PORT, 1UL << LED_PIN, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED_PORT, 1UL << LED_PIN, GPIO_PIN_RESET);
		HAL_Delay(100);
	}
}

