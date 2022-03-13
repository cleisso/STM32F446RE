/********************************************************************
 *	@brief	 :	Biblioteca do encoder
 *	
 *	@author	 :	Cleisson
 *	@date	 :	24/10/2021
 *	@version :	A
 ********************************************************************/

#ifndef ENCODER_H
#define ENCODER_H

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
// Não possui


/********************************************************************
 *	TIPOS DE DADO
 ********************************************************************/
// Configura o encoder que será utilizado
typedef struct
{
	gpio_t data;
	gpio_t clock;
	gpio_t button;
	
	int16_t quantPulsos;
	
	uint32_t timeButton;
	uint8_t flagButtonAux;
	uint8_t flagButtonPulse;
	uint8_t flagButtonPress;
	uint8_t fsm;

	uint8_t habilitaEncoder;
} encoder_t;

// Valores de retorno das funções (status de funcionamento)
typedef enum
{
	ERRO_ENCODER = -1,
	OK_ENCODER = 0,

	NO_PRESS_BUTTON = 0,
	PULSE_BUTTON = 1,
	PRESS_BUTTON = 2
} check_encoder_t;


/********************************************************************
 *	DECLARAÇÃO DE VARIÁVEIS
 ********************************************************************/
// Não possui


/********************************************************************
 *	DECLARAÇÃO DAS SUBROTINAS
 ********************************************************************/
check_encoder_t InicializaEncoder (encoder_t *encoder);
check_encoder_t FinalizaEncoder (encoder_t *encoder);
check_encoder_t VerificaEncoder (encoder_t *encoder);
int16_t LeEncoder (encoder_t *encoder);
check_encoder_t ZeraEncoder (encoder_t *encoder);
check_encoder_t LeBotaoEncoder (encoder_t *encoder);


/********************************************************************
 *	DEFINIÇÃO DE MACROS
 ********************************************************************/
// Não possui


#endif
