/*
 * _gpio.h
 *
 *  Created on: Jan 30, 2022
 *      Author: ctbri
 */

#ifndef INC__GPIO_H_
#define INC__GPIO_H_

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


/********************************************************************
 *	DEFINIÇÕES DE HARDWARE
 ********************************************************************/
// Não possui


/********************************************************************
 *	DEFINIÇÃO DE CONSTANTES
 ********************************************************************/
#define OUTPUT	(0)
#define INPUT	(1)


/********************************************************************
 *	TIPOS DE DADO
 ********************************************************************/
typedef const struct
{
	GPIO_TypeDef *gpioPort;
	uint32_t gpioPin;
	uint8_t gpioDirection;
} gpio_t;


/********************************************************************
 *	DECLARAÇÃO DE VARIÁVEIS
 ********************************************************************/
// Não possui


/********************************************************************
 *	DECLARAÇÃO DAS SUBROTINAS
 ********************************************************************/
void ConfiguraGPIO (gpio_t *gpio);


/********************************************************************
 *	DEFINIÇÃO DE MACROS
 ********************************************************************/
#define GPIOA_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 0))
#define GPIOB_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 1))
#define GPIOC_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 2))
#define GPIOD_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 3))
#define GPIOE_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 4))
#define GPIOF_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 5))
#define GPIOG_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 6))
#define GPIOH_DISABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) &= ~(0x1 << 7))

#define GPIOA_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 0))
#define GPIOB_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 1))
#define GPIOC_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 2))
#define GPIOD_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 3))
#define GPIOE_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 4))
#define GPIOF_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 5))
#define GPIOG_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 6))
#define GPIOH_ENABLE	(*(uint32_t *)(RCC_BASE + 0x30UL) |= (0x1 << 7))

#endif /* INC__GPIO_H_ */
