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
	GPIO_InitTypeDef gpioConfig = {0};

	if (gpio->gpioPort == GPIOA)		GPIOA_ENABLE;
	else if (gpio->gpioPort == GPIOB)	GPIOB_ENABLE;
	else if (gpio->gpioPort == GPIOC)	GPIOC_ENABLE;
	else if (gpio->gpioPort == GPIOD)	GPIOD_ENABLE;
	else if (gpio->gpioPort == GPIOE)	GPIOE_ENABLE;
	else if (gpio->gpioPort == GPIOF)	GPIOF_ENABLE;
	else if (gpio->gpioPort == GPIOG)	GPIOG_ENABLE;
	else if (gpio->gpioPort == GPIOH)	GPIOH_ENABLE;
	else								return;

	if (gpio->gpioDirection == OUTPUT)
	{
		gpioConfig.Mode = GPIO_MODE_OUTPUT_PP;
		gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;
	}
	else
	{
		gpioConfig.Mode = GPIO_MODE_INPUT;
		gpioConfig.Pull = GPIO_PULLUP;
	}

	gpioConfig.Pin = gpio->gpioPin;

	HAL_GPIO_Init(gpio->gpioPort, &gpioConfig);

	if (gpio->gpioDirection == OUTPUT)
		HAL_GPIO_WritePin(gpio->gpioPort, gpio->gpioPin, GPIO_PIN_RESET);
}
