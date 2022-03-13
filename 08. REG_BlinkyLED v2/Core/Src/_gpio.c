/*
 * _gpio.c
 *
 *  Created on: Jan 30, 2022
 *      Author: ctbri
 */

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "_gpio.h"


/********************************************************************
 *	DEFINIÇÃO DE CONSTANTES
 ********************************************************************/
// Não possui


/********************************************************************
 *	TIPOS DE DADO
 ********************************************************************/
// Não possui


/********************************************************************
 *	DECLARAÇÃO DE VARIÁVEIS
 ********************************************************************/
// Não possui


/********************************************************************
 *	DECLARAÇÃO DAS SUBROTINAS
 ********************************************************************/
// Não possui


/********************************************************************
 *	SUBROTINA DE CONFIGURAÇÃO DE UMA GPIO
 ********************************************************************/
void ConfiguraGPIO (gpio_t *gpio)
{
	gpio_register_t *gpioReg = (gpio_register_t *)gpio->gpioPort;

	// Habilitando o barramento do PORT
	// Deve ser habilitado primeiro para poder habilitar a escrita nos registradores do respectivo PORT
	if (gpio->gpioPort == (uint32_t *)GPIOA)		GPIOA_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOB)	GPIOB_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOC)	GPIOC_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOD)	GPIOD_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOE)	GPIOE_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOF)	GPIOF_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOG)	GPIOG_ENABLE;
	else if (gpio->gpioPort == (uint32_t *)GPIOH)	GPIOH_ENABLE;
	else											return;

	// Configuração do pino
	if (gpio->gpioDirection == OUTPUT)
	{
		gpioReg->MODER &= ~(0x3UL << (2 * gpio->gpioPin));
		gpioReg->MODER |= 0x1UL << (2 * gpio->gpioPin);
		gpioReg->OTYPER &= ~(0x1UL << gpio->gpioPin);
		gpioReg->OSPEEDR &= ~(0x3UL << (2 * gpio->gpioPin));
		gpioReg->ODR &= ~(0x1UL << gpio->gpioPin);
	}
	else
	{
		gpioReg->MODER &= ~(0x3UL << (2 * gpio->gpioPin));
		gpioReg->PUPDR &= ~(0x3UL << (2 * gpio->gpioPin));
		gpioReg->PUPDR |= 0x1UL << (2 * gpio->gpioPin);
	}
}


/********************************************************************
 *	SUBROTINA QUE REALIZA A ESCRITA EM UMA GPIO
 ********************************************************************/
void EscreveGPIO (gpio_t *gpio, uint8_t logicState)
{
	gpio_register_t *gpioReg = (gpio_register_t *)gpio->gpioPort;

	if (logicState)
		gpioReg->BSRR |= 0x1UL << gpio->gpioPin;
	else
		gpioReg->BSRR |= 0x1UL << (gpio->gpioPin + 16);
}


/********************************************************************
 *	SUBROTINA QUE REALIZA A LEITURA EM UMA GPIO
 ********************************************************************/
uint8_t LeGPIO (gpio_t *gpio)
{
	gpio_register_t *gpioReg = (gpio_register_t *)gpio->gpioPort;

	return ((gpioReg->IDR >> gpio->gpioPin) & 0x1UL);
}
