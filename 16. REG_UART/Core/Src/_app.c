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


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	ConfiguraGPIO(&led);
	InicializaUSART(_USART2, 9600);
	StringUSART(_USART2, "teste\r\n", 10);

	while (1)
	{
		char dadoRX = LeUSART(_USART2);

		EscreveUSART(_USART2, 'a');

		if (dadoRX)
		{
			if (dadoRX == 'a')
				EscreveGPIO(&led, 1);
			else
				EscreveGPIO(&led, 0);
		}

		HAL_Delay(500);
	}
}
