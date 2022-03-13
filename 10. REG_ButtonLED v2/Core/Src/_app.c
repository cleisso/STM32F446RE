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
gpio_t led = {GPIOA, 5, OUTPUT};
gpio_t button = {GPIOC, 13, INPUT};


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	ConfiguraGPIO(&led);
	ConfiguraGPIO(&button);

	while (1)
	{
		if (!LeGPIO(&button))
			EscreveGPIO(&led, 1);
		else
			EscreveGPIO(&led, 0);
	}
}
