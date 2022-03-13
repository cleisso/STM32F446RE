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
encoder_t encoder = {	.data = {GPIOA, GPIO_PIN_6, INPUT},
						.clock = {GPIOA, GPIO_PIN_7, INPUT},
						.button = {GPIOB, GPIO_PIN_6, INPUT}};

gpio_t led = {GPIOA, GPIO_PIN_5, OUTPUT};


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	InicializaEncoder(&encoder);
	ConfiguraGPIO(&led);

	while (1)
	{
		static uint32_t timeRefresh = 0;
		static char buffer[50] = {0};
		uint8_t sizeString = 0;

		VerificaEncoder(&encoder);

		if (LeBotaoEncoder(&encoder) != NO_PRESS_BUTTON)
		{
			HAL_GPIO_TogglePin(led.gpioPort, led.gpioPin);
		}

		if ((HAL_GetTick() - timeRefresh) > 2000)
		{
			sizeString = snprintf(buffer, sizeof(buffer), "Qtd de Pulsos: %d\r\n", LeEncoder(&encoder));
			HAL_UART_Transmit(&huart2, (uint8_t *)buffer, sizeString, 50);

			timeRefresh = HAL_GetTick();
		}
	}
}
