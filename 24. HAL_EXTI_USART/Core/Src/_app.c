/*
 * _app.c
 *
 *  Created on: Feb 13, 2022
 *      Author: ctbri
 */

#include "_app.h"

volatile uint8_t flagUART2 = 0;
volatile char bufferRX[6] = "";

void _main (void)
{
	HAL_UART_Receive_IT(&huart2, (uint8_t *)bufferRX, sizeof(bufferRX) - 1);

	while (1)
	{
		if (flagUART2)
		{
			char bufferTX[40];
			uint8_t sizeTX;

			bufferRX[sizeof(bufferRX)-1] = '\0';
			sizeTX = snprintf(bufferTX, sizeof(bufferTX), "Recebido via int. da USART2: %s\r\n", bufferRX);
			HAL_UART_Transmit(&huart2, (uint8_t *)bufferTX, sizeTX, 100);
			flagUART2 = 0;
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart2)
	{
		flagUART2 = 1;
		HAL_UART_Receive_IT(&huart2, (uint8_t *)bufferRX, sizeof(bufferRX) - 1);
	}
}
