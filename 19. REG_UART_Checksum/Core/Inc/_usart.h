/*
 * _uart.h
 *
 *  Created on: Jan 31, 2022
 *      Author: ctbri
 */

#ifndef INC__USART_H_
#define INC__USART_H_

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "_gpio.h"

/********************************************************************
 *	DEFINIÇÕES DE HARDWARE
 ********************************************************************/
// Não possui


/********************************************************************
 *	DEFINIÇÃO DE CONSTANTES
 ********************************************************************/
#define APB1_FREQUENCY	(42000000UL)
#define APB2_FREQUENCY	(84000000UL)


/********************************************************************
 *	TIPOS DE DADO
 ********************************************************************/
typedef struct
{
	uint32_t SR;	// Status Register
	uint32_t DR;	// Data Register
	uint32_t BRR;	// Baud Rate Register
	uint32_t CR1;	// Control Register 1
	uint32_t CR2;	// Control Register 2
	uint32_t CR3;	// Control Register 3
	uint32_t GTPR;	// Guard Time and Prescaler Register
} usart_register_t;

typedef enum
{
	_USART1,
	_USART2,
	_USART3,
	_UART4,
	_UART5,
	_USART6
} usart_t;


/********************************************************************
 *	DECLARAÇÃO DE VARIÁVEIS
 ********************************************************************/
// Não possui


/********************************************************************
 *	DECLARAÇÃO DAS SUBROTINAS
 ********************************************************************/
void InicializaUSART (usart_t channel, uint32_t baudRate);
void EscreveUSART (usart_t channel, char data);
void StringUSART (usart_t channel, char *buffer, uint8_t sizeBuffer);
char LeUSART (usart_t channel);

/********************************************************************
 *	DEFINIÇÃO DE MACROS
 ********************************************************************/
#define USART1_ENABLE	(*(uint32_t *)(RCC_BASE + 0x44UL) |= (0x1UL << 4 ))
#define USART2_ENABLE	(*(uint32_t *)(RCC_BASE + 0x40UL) |= (0x1UL << 17))
#define USART3_ENABLE	(*(uint32_t *)(RCC_BASE + 0x40UL) |= (0x1UL << 18))
#define UART4_ENABLE	(*(uint32_t *)(RCC_BASE + 0x40UL) |= (0x1UL << 19))
#define UART5_ENABLE	(*(uint32_t *)(RCC_BASE + 0x40UL) |= (0x1UL << 20))
#define USART6_ENABLE	(*(uint32_t *)(RCC_BASE + 0x44UL) |= (0x1UL << 5 ))

#endif /* INC__USART_H_ */
