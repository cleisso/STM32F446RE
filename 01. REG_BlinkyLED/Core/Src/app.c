/*
 * app.c
 *
 *  Created on: Jan 6, 2022
 *      Author: ctbri
 */

#include "app.h"

volatile gpio_t * const gpioa = (gpio_t *)GPIOA_ADDRESS;

void _main (void)
{
	// Habilitando o Port A
	GPIOA_ENABLE;

	// Configurando o pino PA5 como saída
	gpioa->MODER = (gpioa->MODER & ~(0x3 << LED*2)) | (0x1 << LED*2);

	// Configurando a saída PA5 como Push-Pull
	gpioa->OTYPER = gpioa->OTYPER & ~(0x1 << LED);

	// Configurando a saída PA5 como baixa velocidade
	(gpioa->OSPEEDR = gpioa->OSPEEDR & ~(0x3 << LED*2));

	// Apagando o pino PA5
	gpioa->ODR = gpioa->ODR & ~(0x1 << LED);

	while (1)
	{
		for (uint8_t i = 1; i <= 5; ++i)
		{
			for (uint8_t j = 0; j < 10; ++j)
			{
				// Acendendo o LED
				gpioa->ODR = gpioa->ODR | (0x1 << LED);
				HAL_Delay(50 * i);

				// Apagando o LED
				gpioa->ODR = gpioa->ODR & ~(0x1 << LED);
				HAL_Delay(50 * i);
			}
		}
	}
}
