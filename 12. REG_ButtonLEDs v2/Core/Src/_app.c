/*
 * _app.c
 *
 *  Created on: Jan 30, 2022
 *      Author: ctbri
 */

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "_app.h"


/********************************************************************
 *	DEFINIÇÕES DE HARDWARE
 ********************************************************************/
gpio_t button = {GPIOC, 13, INPUT};

gpio_t led[8] = {{GPIOC, 4, OUTPUT },
				 {GPIOB, 13, OUTPUT },
				 {GPIOA, 10, OUTPUT},
				 {GPIOB, 3, OUTPUT },
				 {GPIOB, 5, OUTPUT },
				 {GPIOB, 4, OUTPUT },
				 {GPIOB, 10, OUTPUT},
				 {GPIOA, 8, OUTPUT }};


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	static uint8_t ledState[8] = {0,1,0,1,0,1,0,1};
	static uint8_t ledEnable = 0;

	ConfiguraGPIO(&button);

	for (uint8_t i = 0; i < 8; ++i)
		ConfiguraGPIO(&led[i]);

	while (1)
	{
		if (!LeGPIO(&button))
		{
			HAL_Delay(10);
			while (!LeGPIO(&button));
			HAL_Delay(10);

			ledEnable = !ledEnable;
		}

		if (ledEnable)
		{
			for (uint8_t i = 0; i < 8; ++i)
			{
				ledState[i] = !ledState[i];
				EscreveGPIO(&led[i], ledState[i]);
			}

			HAL_Delay(200);
		}
		else
		{
			for (uint8_t i = 0; i < 8; ++i)
				EscreveGPIO(&led[i], 0);
		}
	}
}
