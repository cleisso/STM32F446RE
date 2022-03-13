/*
 * _usart.c
 *
 *  Created on: Jan 31, 2022
 *      Author: ctbri
 */

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "_usart.h"


/********************************************************************
 *	DEFINIÇÕES DE HARDWARE
 ********************************************************************/
gpio_t USART1_RX = {GPIOA, 10, ALTERNATE};
gpio_t USART1_TX = {GPIOA,  9, ALTERNATE};

gpio_t USART2_RX = {GPIOA, 3, ALTERNATE};
gpio_t USART2_TX = {GPIOA, 2, ALTERNATE};

gpio_t USART3_RX = {GPIOC, 11, ALTERNATE};
gpio_t USART3_TX = {GPIOC, 10, ALTERNATE};

gpio_t UART4_RX = {GPIOA, 1, ALTERNATE};
gpio_t UART4_TX = {GPIOA, 0, ALTERNATE};

gpio_t UART5_RX = {GPIOE, 7, ALTERNATE};
gpio_t UART5_TX = {GPIOE, 8, ALTERNATE};

gpio_t USART6_RX = {GPIOC, 7, ALTERNATE};
gpio_t USART6_TX = {GPIOC, 6, ALTERNATE};


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
void InicializaUSART (usart_t channel, uint32_t baudRate)
{
	gpio_register_t *gpio;
	usart_register_t *usart;
	uint32_t mantissaBaudRate;
	uint32_t fractionBaudRate;
	uint32_t aux;

	// Calculando os valores a serem configurados para o respectivo Baud Rate
	if (channel == _USART1 || channel == _USART6)
		aux = APB2_FREQUENCY/baudRate;
	else
		aux = APB1_FREQUENCY/baudRate;

	mantissaBaudRate = aux >> 4;
	fractionBaudRate = aux & 0xFUL;

	// Verificando se a mantissa é compatível com o tamanho do registrador
	if (mantissaBaudRate >= 4096)
		return;

	// Selecionando o canal USART e configurando os respectivos GPIOs
	switch (channel)
	{
		default:
		case _USART1:
			gpio = (gpio_register_t *)GPIOA;

			ConfiguraGPIO(&USART1_RX);
			gpio->AFRH = (gpio->AFRH & ~(0xFUL << ((USART1_RX.gpioPin - 8)*4))) | (0x7UL << ((USART1_RX.gpioPin - 8)*4));

			ConfiguraGPIO(&USART1_TX);
			gpio->AFRH = (gpio->AFRH & ~(0xFUL << ((USART1_TX.gpioPin - 8)*4))) | (0x7UL << ((USART1_TX.gpioPin - 8)*4));

			usart = (usart_register_t *)USART1;
			USART1_ENABLE;
			break;

		case _USART2:
			gpio = (gpio_register_t *)GPIOA;

			ConfiguraGPIO(&USART2_RX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (USART2_RX.gpioPin * 4))) | (0x7UL << (USART2_RX.gpioPin * 4));

			ConfiguraGPIO(&USART2_TX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (USART2_TX.gpioPin * 4))) | (0x7UL << (USART2_TX.gpioPin * 4));

			usart = (usart_register_t *)USART2;
			USART2_ENABLE;
			break;

		case _USART3:
			gpio = (gpio_register_t *)GPIOC;

			ConfiguraGPIO(&USART3_RX);
			gpio->AFRH = (gpio->AFRH & ~(0xFUL << ((USART3_RX.gpioPin - 8)*4))) | (0x7UL << ((USART3_RX.gpioPin - 8)*4));

			ConfiguraGPIO(&USART3_TX);
			gpio->AFRH = (gpio->AFRH & ~(0xFUL << ((USART3_TX.gpioPin - 8)*4))) | (0x7UL << ((USART3_TX.gpioPin - 8)*4));

			usart = (usart_register_t *)USART3;
			USART3_ENABLE;
			break;

		case _UART4:
			gpio = (gpio_register_t *)GPIOA;

			ConfiguraGPIO(&UART4_RX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (UART4_RX.gpioPin * 4))) | (0x8UL << (UART4_RX.gpioPin * 4));

			ConfiguraGPIO(&UART4_TX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (UART4_TX.gpioPin * 4))) | (0x8UL << (UART4_TX.gpioPin * 4));

			usart = (usart_register_t *)UART4;
			UART4_ENABLE;
			break;

		case _UART5:
			gpio = (gpio_register_t *)GPIOE;

			ConfiguraGPIO(&UART5_RX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (UART5_RX.gpioPin * 4))) | (0x8UL << (UART5_RX.gpioPin * 4));

			ConfiguraGPIO(&UART5_TX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (UART5_TX.gpioPin * 4))) | (0x8UL << (UART5_TX.gpioPin * 4));

			usart = (usart_register_t *)UART5;
			UART5_ENABLE;
			break;

		case _USART6:
			gpio = (gpio_register_t *)GPIOC;

			ConfiguraGPIO(&USART6_RX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (USART6_RX.gpioPin * 4))) | (0x8UL << (USART6_RX.gpioPin * 4));

			ConfiguraGPIO(&USART6_TX);
			gpio->AFRL = (gpio->AFRL & ~(0xFUL << (USART6_TX.gpioPin * 4))) | (0x8UL << (USART6_TX.gpioPin * 4));

			usart = (usart_register_t *)USART6;
			USART6_ENABLE;
			break;
	}

	// Oversampling by 16
	usart->CR1 &= ~(0x1UL << 15);
	// 1 Start bit, 8 Data bits, n Stop bit
	usart->CR1 &= ~(0x1UL << 12);
	// Habilitando a transmissão
	usart->CR1 |= (0x1UL << 3);
	// Habilitando a recepção
	usart->CR1 |= (0x1UL << 2);
	// 1 Stop bit
	usart->CR2 &= ~(0x3UL << 12);
	// Configurando o Baud Rate
	usart->BRR |= (mantissaBaudRate & 0xFFFUL) << 4;
	usart->BRR |= (fractionBaudRate & 0xFUL);

	// Ligando a USART do respectivo canal
	usart->CR1 |= 0x1UL << 13;
}

void EscreveUSART (usart_t channel, char data)
{
	usart_register_t *usart;

	switch (channel)
	{
		default:
		case _USART1:	usart = (usart_register_t *)USART1;	break;
		case _USART2:	usart = (usart_register_t *)USART2;	break;
		case _USART3:	usart = (usart_register_t *)USART3;	break;
		case _UART4:	usart = (usart_register_t *)UART4;	break;
		case _UART5:	usart = (usart_register_t *)UART5;	break;
		case _USART6:	usart = (usart_register_t *)USART6;	break;
	}

	usart->DR = data & 0xFFUL;
	while (!((usart->SR >> 7) & 0x1UL) || !((usart->SR >> 6) & 0x1UL));
	usart->SR &= ~(0x1UL << 6);
}

void StringUSART (usart_t channel, char *buffer, uint8_t sizeBuffer)
{
	uint8_t i = 0;

	while (i < sizeBuffer && *buffer != '\0')
	{
		EscreveUSART(channel, *buffer);
		++buffer;
	}
}

char LeUSART (usart_t channel)
{
	usart_register_t *usart;

	switch (channel)
	{
		default:
		case _USART1:	usart = (usart_register_t *)USART1;	break;
		case _USART2:	usart = (usart_register_t *)USART2;	break;
		case _USART3:	usart = (usart_register_t *)USART3;	break;
		case _UART4:	usart = (usart_register_t *)UART4;	break;
		case _UART5:	usart = (usart_register_t *)UART5;	break;
		case _USART6:	usart = (usart_register_t *)USART6;	break;
	}

	if ((usart->SR >> 5) & 0x1UL)
		return ((char)usart->DR);
	else
		return (0);
}
