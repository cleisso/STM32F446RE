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
 *	SUBROTINA DE INICIALIZAÇÃO DO INDEPENDENT WATCHDOG TIMER
 ********************************************************************/
void InicializaIWDG (IWDG_HandleTypeDef *hiwdg)
{
	// Realiza a configuração do IWDG
	hiwdg->Instance = IWDG;
	hiwdg->Init.Prescaler = IWDG_PRESCALER_64;
	hiwdg->Init.Reload = IWDG_TIME_5S;

	// Inicializa o IWDG
	if (HAL_IWDG_Init(hiwdg) != HAL_OK)
	{
		Error_Handler();
	}
}


/********************************************************************
 *	SUBROTINA QUE REINICIA A CONTAGEM DO INDEPEDENT WATCHDOG
 ********************************************************************/
void ResetaIWDG (IWDG_HandleTypeDef *hiwdg)
{
	HAL_IWDG_Refresh(hiwdg);
}
