/*
 * app.c
 *
 *  Created on: Feb 6, 2022
 *      Author: ctbri
 */

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "_app.h"


/********************************************************************
 *	DEFINIÇÕES DE CONSTANTES
 ********************************************************************/
// Tempo de IWatchdog de 5 segundos, c/ prescaler de 64
#define IWDG_TIME_5S	(2499)


/********************************************************************
 *	DEFINIÇÕES DE HARDWARE
 ********************************************************************/
gpio_t LED = {GPIOA, 5, OUTPUT};
gpio_t BUTTON = {GPIOC, 13, INPUT};


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	ConfiguraGPIO(&LED);
	ConfiguraGPIO(&BUTTON);
	InicializaIWDG(IWDG_TIME_5S, IWDG_PRESCALER_64);

	EscreveGPIO(&LED, 1);
	HAL_Delay(2000);

	while (1)
	{
		EscreveGPIO(&LED, 1);
		HAL_Delay(100);
		EscreveGPIO(&LED, 0);
		HAL_Delay(100);

		if (!LeGPIO(&BUTTON))
			ResetaIWDG();
	}
}
