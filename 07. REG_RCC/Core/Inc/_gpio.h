/*
 * _gpio.h
 *
 *  Created on: Jan 6, 2022
 *      Author: ctbri
 */

#ifndef INC__GPIO_H_
#define INC__GPIO_H_

#include "main.h"

#define GPIOA_ADDRESS	(0x40020000UL)
#define GPIOB_ADDRESS	(0x40020400UL)
#define GPIOC_ADDRESS	(0x40020800UL)
#define GPIOD_ADDRESS	(0x40020C00UL)
#define GPIOE_ADDRESS	(0x40021000UL)
#define GPIOF_ADDRESS	(0x40021400UL)
#define GPIOG_ADDRESS	(0x40021800UL)
#define GPIOH_ADDRESS	(0x40021C00UL)

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

/*
 * MODER: Configura a direção do pino. Cada pino pode ser configurado de 4 maneiras:
 * 		00: Entrada (Reset)
 * 		01: Saída
 * 		10: Alternate Function Mode
 * 		11: Analog Mode
 *
 * OTYPER: Configura se o pino de saída será do tipo Push-Pull ou Open-Drain:
 * 		0: Push-Pull (Reset)
 * 		1: Open-Drain
 *
 * OSPEEDR: Configura a velocidade (Slew Rate) do pino. Cada pino pode ser configurado de 4 maneiras:
 * 		00: Low Speed - 4~8MHz (Reset, exceto para PB3)
 * 		01: Medium Speed - 25~50MHz
 * 		10: Fast Speed - 50~100MHz
 * 		11: High Speed - 100~180MHz (Reset PB3)
 *
 * PUPDR: Configura se o pino vai possuir ou não Pull-Up e Pull-Down:
 * 		00: Sem Pull-Up e Pull-Down (Reset, exceto para o PA13, PA14, PA15 e PB4)
 * 		01: Pull-Up (PA13, PA15 e PB4)
 * 		10: Pull-Down (PA14)
 * 		11: Reservado
 *
 * IDR: Permite realizar a leitura do respectivo pino
 *
 * ODR: Permite realizar a escrita do respectivo pino
 *
 * BSRR: Permite realizar a escrita do respectivo pino (este registrador é útil quando
 * 		 deseja-se garantir a atomicidade entre as operações). É dividido em duas partes:
 * 		 0~15: Set bits
 * 		 16~31: Reset bits
 *
 * LCKR: Permite bloquear a alteração dos registradores de configuração dos PORTs.
 * 		 Para realizar o bloqueio deve-se realizar uma sequência de escritas e leituras,
 * 		 conforme o datasheet. Após o bloqueio, o desbloqueio apenas ocorrerá quando
 * 		 ocorrer o reset.
 *
 * AFRL: Permite selecionar qual Alternate Function os pinos de 0~7 irão assumir.
 * 		 Há 16 modos de configuração para cada pino.
 *
 * AFRH: Permite selecionar qual Alternate Function os pinos de 8~15 irão assumir.
 * 		 Há 16 modos de configuração para cada pino.
 */

typedef volatile struct
{
	uint32_t MODER;		// GPIO Port Mode Register
	uint32_t OTYPER;	// GPIO Port Output Type Register
	uint32_t OSPEEDR;	// GPIO Port Speed Register
	uint32_t PUPDR;		// GPIO Port Pull-Up/Pull-Down Register
	uint32_t IDR;		// GPIO Port Input Data Register
	uint32_t ODR;		// GPIO Port Output Data Register
	uint32_t BSRR;		// GPIO Port Bit Set/Reset Register
	uint32_t LCKR;		// GPIO Port Configuration Lock Register
	uint32_t AFRL;		// GPIO Port Alternate Function Low Register
	uint32_t AFRH;		// GPIO Port Alternate Function High Register
} gpio_t;

void InicializaGPIO (void);

#endif /* INC__GPIO_H_ */
