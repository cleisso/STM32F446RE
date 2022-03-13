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
// Não possui


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{

	InicializaUSART(_USART2, 9600);

	while (1)
	{
		char character = LeUSART(_USART2);

		if (character)
		{
			if (character >= '0' && character <= '9')
				StringUSART(_USART2, "O caracter recebido eh do tipo numerico!\r\n", 50);
			else if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
				StringUSART(_USART2, "O caracter recebido eh do tipo letra!\r\n", 50);
			else if (character >= ' ' && character <= '~')
				StringUSART(_USART2, "O caracter recebido e do tipo simbolo!\r\n", 50);

			character = 0;
		}
	}
}
