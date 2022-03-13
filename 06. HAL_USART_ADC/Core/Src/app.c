/*
 * app.c
 *
 *  Created on: Jan 12, 2022
 *      Author: ctbri
 */

/* Para utilizar o ADC, deve-se realizar o Start para realizar a conversão. Para cada Polling estará sendo realizado a
 * conversão e leitura de um canal do ADC. O ADC é de 12 bits.
 *
 * Para enviar uma mensagem via serial, recomenda-se utilizar um buffer para armazenar a mensagem e uma variável para armazenar
 * a quantidade de bytes que serão enviados (para isso, utilizar o snprintf).
 */

#include "app.h"

void _main (void)
{
	float potVoltage = 0;
	uint32_t timeRefresh = HAL_GetTick();
	uint8_t buffer[20] = {0};
	int8_t size = 0;
	uint8_t command = 0;

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	while (1)
	{
		if ((HAL_GetTick() - timeRefresh) > 1000)
		{
			HAL_ADC_Start(&hadc1);
			if(!HAL_ADC_PollForConversion(&hadc1, 100))
				potVoltage = (HAL_ADC_GetValue(&hadc1) * ADC_VOLTAGE)/4095.0;

			size = snprintf((char *)buffer, sizeof(buffer), "Tensao: %.2f V\r\n", potVoltage);
			if (size > 0)
				HAL_UART_Transmit(&huart2, buffer, size, 100);

			timeRefresh = HAL_GetTick();
		}

		if (!HAL_UART_Receive(&huart2, &command, 1, 100))
		{
			if (command == 'a')
				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			else if (command == 'b')
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
			else if (command == 'c')
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

			command = 0;
		}
	}
}
