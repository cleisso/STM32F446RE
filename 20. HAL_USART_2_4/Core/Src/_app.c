/*
 * _app.c
 *
 *  Created on: Feb 2, 2022
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
 *	PROGRAMA PRINCIPAL
 ********************************************************************/
void _main (void)
{
	uint8_t bufferUART2[50] = {0};
	uint8_t bufferUART4[50] = {0};

	while (1)
	{
		// Verifica se chegou informação via UART2
		if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE))
		{
			uint8_t tamBuffer = 0;

			// Recebe as informações via UART2
			HAL_UART_Receive(&huart2, bufferUART2, sizeof(bufferUART2), 500);

			// Realiza o envio/recepção das informações via UART4
			for (uint8_t i = 0; i < sizeof(bufferUART2); ++i)
			{
				if (bufferUART2[i])
				{
					HAL_UART_Transmit(&huart4, &bufferUART2[i], 1, 1);
					HAL_UART_Receive(&huart4, &bufferUART4[i], 1, 1);
					++tamBuffer;

					// Após o envio, apaga a posição do buffer
					bufferUART2[i] = 0;
				}
				else
					break;
			}

			// Realiza o envio das informações via UART2
			HAL_UART_Transmit(&huart2, bufferUART4, tamBuffer, 500);
		}
	}
}
