/*
 * app.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ctbri
 */

#include "app.h"

gpio_t * const gpioa = (gpio_t *)GPIOA_ADDRESS;
gpio_t * const gpioc = (gpio_t *)GPIOC_ADDRESS;

void _main (void)
{
	uint8_t flagLed = 0;
	uint8_t flagButton = 0;
	uint32_t timeButton = 0;

	// Habilitando o barramento do GPIOA e GPIOC
	GPIOA_ENABLE;
	GPIOC_ENABLE;

	// Inicialização do LED
	gpioa->MODER = (gpioa->MODER & ~(0x3 << LED*2)) | (0x1 << LED*2);
	gpioa->OTYPER = gpioa->OTYPER & ~(0x1 << LED);
	gpioa->OSPEEDR = gpioa->OSPEEDR & ~(0x3 << LED*2);
	gpioa->BSRR = 0x1 << (LED + 16);

	// Inicialização do Botão
	gpioc->MODER = gpioc->MODER & ~(0x3 << BUTTON*2);
	gpioc->PUPDR = gpioc->PUPDR & ~(0x3 << BUTTON*2);

	while (1)
	{
		if ((gpioc->IDR & (0x1 << BUTTON)) == 0)
		{
			if (timeButton < 100000)
				++timeButton;
			else
				timeButton = 0, flagButton = 1;
		}
		else
		{
			if (flagButton == 1)
			{
				if (timeButton > 0)
					--timeButton;
				else
				{
					flagButton = 0;

					if (flagLed == 1)
					{
						flagLed = 0;
						gpioa->BSRR = 0x1 << (LED + 16);
					}
					else
					{
						flagLed = 1;
						gpioa->BSRR = 0x1 << (LED);
					}
				}
			}
			else
			{
				timeButton = 0;
			}
		}
	}
}
