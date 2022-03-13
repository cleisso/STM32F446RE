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
	uint8_t pwrLED = 0;

	uint16_t prescaler = 0;
	uint8_t time = 0;

	ConfiguraGPIO(&led);
	InicializaUSART(_USART2, 9600);

	while (1)
	{
		char cmdUSART = LeUSART(_USART2);

		if (pwrLED > time)
			EscreveGPIO(&led, 1);
		else
			EscreveGPIO(&led, 0);

		switch (cmdUSART)
		{
			case '0':	pwrLED = 0;		break;
			case '1':	pwrLED = 10;	break;
			case '2':	pwrLED = 20;	break;
			case '3':	pwrLED = 30;	break;
			case '4':	pwrLED = 40;	break;
			case '5':	pwrLED = 50;	break;
			case '6':	pwrLED = 60;	break;
			case '7':	pwrLED = 70;	break;
			case '8':	pwrLED = 80;	break;
			case '9':	pwrLED = 90;	break;
			case 'A':	pwrLED = 100;	break;

			default:					break;
		}

		if (++prescaler >= 100)
		{
			prescaler = 0;

			if (++time >= 100)
				time = 0;
		}
	}
}
