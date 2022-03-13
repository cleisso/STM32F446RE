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
 *	DEFINIÇÕES DE CONSTANTES
 ********************************************************************/
#define TIMEOUT	(500)


/********************************************************************
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	char character = 0;
	char bufferRX[50] = {0};
	char bufferTX[50] = {0};

	InicializaUSART(_USART2, 9600);

	while (1)
	{
		character = LeUSART(_USART2);

		if (character)
		{
			uint32_t checksum = 0;
			uint8_t tamBuffer = 0;
			uint32_t time = HAL_GetTick();

			// Realiza a aquisição dos caracteres e realiza o cálculo do checksum
			while ((HAL_GetTick() - time) < TIMEOUT && tamBuffer < sizeof(bufferRX))
			{
				if (character)
				{
					bufferRX[tamBuffer] = character;
					checksum = checksum + character;
					++tamBuffer;
					time = HAL_GetTick();
				}

				character = LeUSART(_USART2);
			}

			// Pula uma linha no terminal
			StringUSART(_USART2, "\r\n", 2);

			// Imprime o valor de cada caracter recebido no buffer
			for (uint8_t i = 0; i < tamBuffer; ++i)
			{
				uint8_t sizeBuffer = snprintf(bufferTX, sizeof(bufferTX), "%c %c = %d\r\n", i ? '+' : ' ', bufferRX[i], bufferRX[i]);
				StringUSART(_USART2, bufferTX, sizeBuffer);
			}

			// Imprime traços horizontais
			for (uint8_t i = 0; i < 10; ++i)
				EscreveUSART(_USART2, '-');
			StringUSART(_USART2, "\r\n", 2);

			// Imprime checksum
			tamBuffer = snprintf(bufferTX, sizeof(bufferTX), "checksum = %lu\r\n\r\n", checksum);
			StringUSART(_USART2, bufferTX, tamBuffer);

			// Apaga o buffer de recepção
			for (uint8_t i = 0; i < sizeof(bufferRX); ++i)
				bufferRX[i] = 0;
		}
	}
}
