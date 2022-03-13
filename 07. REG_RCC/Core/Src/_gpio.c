/*
 * _gpio.c
 *
 *  Created on: Jan 6, 2022
 *      Author: ctbri
 */

#include "_gpio.h"

void InicializaGPIO (void)
{
	gpio_t *gpioConfig;

	// Habilitando o barramento do PORTA
	// Deve ser habilitado primeiro para poder habilitar a escrita nos registradores do PORTA
		GPIOA_ENABLE;

	// Configurando o LED como saída
	gpioConfig = (gpio_t *)LED_PORT;
	gpioConfig->MODER &= ~(0x3UL << (2*LED_PIN));
	gpioConfig->MODER |= 0x1UL << (2*LED_PIN);
	gpioConfig->OTYPER &= ~(0x1UL << LED_PIN);
	gpioConfig->OSPEEDR &= ~(0x3UL << (2*LED_PIN));
}
