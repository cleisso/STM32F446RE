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


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	ConfiguraGPIO(&led);

	while (1)
	{
		HAL_GPIO_WritePin(led.gpioPort, led.gpioPin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(led.gpioPort, led.gpioPin, GPIO_PIN_RESET);
		HAL_Delay(100);
	}
}
