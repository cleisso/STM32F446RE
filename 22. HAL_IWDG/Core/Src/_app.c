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
// Não possui

/********************************************************************
 *	DEFINIÇÕES DE HARDWARE
 ********************************************************************/
gpio_t LED = {GPIOA, GPIO_PIN_5, OUTPUT};
gpio_t BUTTON = {GPIOC, GPIO_PIN_13, INPUT};


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	ConfiguraGPIO(&LED);
	ConfiguraGPIO(&BUTTON);
	InicializaIWDG(&hiwdg);

	HAL_GPIO_WritePin(LED.gpioPort, LED.gpioPin, GPIO_PIN_SET);
	HAL_Delay(2000);

	while (1)
	{
		HAL_GPIO_WritePin(LED.gpioPort, LED.gpioPin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED.gpioPort, LED.gpioPin, GPIO_PIN_RESET);
		HAL_Delay(100);

		if (!HAL_GPIO_ReadPin(BUTTON.gpioPort, BUTTON.gpioPin))
			ResetaIWDG(&hiwdg);
	}
}
