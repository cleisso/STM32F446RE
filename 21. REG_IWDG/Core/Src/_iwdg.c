/*
 * _iwdg.c
 *
 *  Created on: Feb 6, 2022
 *      Author: ctbri
 */

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "_iwdg.h"


/********************************************************************
 *	DEFINIÇÃO DE CONSTANTES
 ********************************************************************/
#define IWDG_CONFIG	(0x5555)
#define IWDG_RESET	(0xAAAA)
#define IWDG_START	(0xCCCC)


/********************************************************************
 *	TIPOS DE DADOS
 ********************************************************************/
typedef volatile struct
{
	uint32_t KR;
	uint32_t PR;
	uint32_t RLR;
	uint32_t SR;
} iwdg_register_t;


/********************************************************************
 *	SUBROTINA DE INICIALIZAÇÃO DO INDEPENDENT WATCHDOG TIMER
 ********************************************************************/
void InicializaIWDG (uint16_t timeRegister, iwdg_prescaler_t prescaler)
{
	iwdg_register_t *iwdgReg = (iwdg_register_t *)IWDG;

	// Habilita para realizar a configuração do Watchdog
	iwdgReg->KR = IWDG_CONFIG;

	// Configura o prescaler
	iwdgReg->PR = prescaler & 0x7;

	// Configura o registrador de recarga
	iwdgReg->RLR = timeRegister & 0xFFF;

	// Carrega o valor de recarga
	iwdgReg->KR = IWDG_RESET;

	// Habilita o watchdog
	iwdgReg->KR = IWDG_START;
}


/********************************************************************
 *	SUBROTINA QUE REINICIA A CONTAGEM DO INDEPEDENT WATCHDOG
 ********************************************************************/
void ResetaIWDG (void)
{
	iwdg_register_t *iwdgReg = (iwdg_register_t *)IWDG;

	iwdgReg->KR = IWDG_RESET;
}
