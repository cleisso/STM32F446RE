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
gpio_t led = {GPIOA, GPIO_PIN_5, OUTPUT};
gpio_t button = {GPIOC, GPIO_PIN_13, INPUT};


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	ConfiguraGPIO(&led);
	ConfiguraGPIO(&button);

	while (1)
	{
		if (!HAL_GPIO_ReadPin(button.gpioPort, button.gpioPin))
			HAL_GPIO_WritePin(led.gpioPort, led.gpioPin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(led.gpioPort, led.gpioPin, GPIO_PIN_RESET);
	}
}
