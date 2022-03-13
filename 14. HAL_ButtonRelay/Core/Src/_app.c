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
gpio_t button[2] = {{GPIOB, GPIO_PIN_9, INPUT},
		   	   	    {GPIOB, GPIO_PIN_8, INPUT}};

gpio_t relay[2] = {{GPIOA, GPIO_PIN_10, OUTPUT},
				   {GPIOB, GPIO_PIN_3 , OUTPUT}};

/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	for (uint8_t i = 0; i < 2; ++i)
	{
		ConfiguraGPIO(&button[i]);
		ConfiguraGPIO(&relay[i]);
		HAL_GPIO_WritePin(relay[i].gpioPort, relay[i].gpioPin, GPIO_PIN_SET);
	}

	while (1)
	{
		if (!HAL_GPIO_ReadPin(button[0].gpioPort, button[0].gpioPin))
		{
			HAL_Delay(10);
			while (!HAL_GPIO_ReadPin(button[0].gpioPort, button[0].gpioPin));
			HAL_Delay(10);

			HAL_GPIO_TogglePin(relay[0].gpioPort, relay[0].gpioPin);
		}

		if (!HAL_GPIO_ReadPin(button[1].gpioPort, button[1].gpioPin))
		{
			HAL_Delay(10);
			while (!HAL_GPIO_ReadPin(button[1].gpioPort, button[1].gpioPin));
			HAL_Delay(10);

			HAL_GPIO_TogglePin(relay[1].gpioPort, relay[1].gpioPin);
		}
	}
}
