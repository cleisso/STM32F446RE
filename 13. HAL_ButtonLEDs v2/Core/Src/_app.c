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
gpio_t button = {GPIOC, GPIO_PIN_13, INPUT};

gpio_t led[8] = {{GPIOC, GPIO_PIN_4,  OUTPUT},
				 {GPIOB, GPIO_PIN_13, OUTPUT},
				 {GPIOA, GPIO_PIN_10, OUTPUT},
				 {GPIOB, GPIO_PIN_3,  OUTPUT},
				 {GPIOB, GPIO_PIN_5,  OUTPUT},
				 {GPIOB, GPIO_PIN_4,  OUTPUT},
				 {GPIOB, GPIO_PIN_10, OUTPUT},
				 {GPIOA, GPIO_PIN_8,  OUTPUT}};


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
		if (!HAL_GPIO_ReadPin(button.gpioPort, button.gpioPin))
		{
			HAL_Delay(10);
			while (!HAL_GPIO_ReadPin(button.gpioPort, button.gpioPin));
			HAL_Delay(10);

			ledEnable = !ledEnable;
		}

		if (ledEnable)
		{
			for (uint8_t i = 0; i < 8; ++i)
			{
				ledState[i] = !ledState[i];
				HAL_GPIO_WritePin(led[i].gpioPort, led[i].gpioPin, ledState[i]);
			}

			HAL_Delay(500);
		}
		else
		{
			for (uint8_t i = 0; i < 8; ++i)
				HAL_GPIO_WritePin(led[i].gpioPort, led[i].gpioPin, GPIO_PIN_RESET);
		}
	}
}
