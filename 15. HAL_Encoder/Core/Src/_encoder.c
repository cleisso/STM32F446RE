/********************************************************************
 *	@brief	 :	Biblioteca do encoder
 *	
 *	@author	 :	Cleisson
 *	@date	 :	24/10/2021
 *	@version :	A
 ********************************************************************/

/********************************************************************
 *	BIBLIOTECAS
 ********************************************************************/
#include "_encoder.h"


/********************************************************************
 *	DEFINIÇÃO DE CONSTANTES
 ********************************************************************/
// Determina o tempo em que o botão necessita permanecer acionado
// para habilitar função secundária
#define TIME_PRESS_BUTTON	(3000)


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
 *	SUBROTINA DE INICIALIZAÇÃO DO ENCODER
 ********************************************************************/
check_encoder_t InicializaEncoder (encoder_t *encoder)
{
	if (!encoder->habilitaEncoder)
	{
		ConfiguraGPIO(&encoder->data);
		ConfiguraGPIO(&encoder->clock);
		ConfiguraGPIO(&encoder->button);

		encoder->quantPulsos = 0;
		encoder->timeButton = 0;
		encoder->flagButtonAux = 0;
		encoder->flagButtonPulse = 0;
		encoder->flagButtonPress = 0;
		encoder->fsm = 0;

		encoder->habilitaEncoder = 1;
	}

	return OK_ENCODER;
}


/********************************************************************
 *	SUBROTINA QUE FINALIZA O FUNCIONAMENTO DO ENCODER
 ********************************************************************/
check_encoder_t FinalizaEncoder (encoder_t *encoder)
{
	if (encoder->habilitaEncoder)
		encoder->habilitaEncoder = 0;

	return OK_ENCODER;
}


/********************************************************************
 *	SUBROTINA QUE REALIZA MONITORAMENTO DO FUNCIONAMENTO DO ENCODER
 ********************************************************************/
check_encoder_t VerificaEncoder (encoder_t *encoder)
{
	// Verifica se o encoder foi habilitado
	if (encoder->habilitaEncoder == 0)
		return ERRO_ENCODER;
	
	// Verifica o acionamento do botão do encoder
	if (encoder->flagButtonPulse == 0 && encoder->flagButtonPress == 0)
	{
		if (HAL_GPIO_ReadPin(encoder->button.gpioPort, encoder->button.gpioPin) == 0 && encoder->flagButtonAux == 0)
		{
			// Debouncing do botão ao ser pressionado
			HAL_Delay(10);

			encoder->timeButton = HAL_GetTick();
			encoder->flagButtonAux = 1;
		}
		else if (encoder->flagButtonAux == 1)
		{
			// Verifica se o botão é mantido pressionado por "muito" tempo.
			// Se sim, retorna flag de pressionamento, se não, retorna flag de pulso
			if (HAL_GPIO_ReadPin(encoder->button.gpioPort, encoder->button.gpioPin) == 0)
			{
				if (encoder->timeButton != 0 && (HAL_GetTick() - encoder->timeButton) > TIME_PRESS_BUTTON)
				{
					encoder->timeButton = 0;
					encoder->flagButtonPress = 1;
				}
			}
			else
			{
				// Debouncing do botão ao ser solto
				HAL_Delay(10);

				if (encoder->timeButton != 0)
				{
					encoder->timeButton = 0;
					encoder->flagButtonPulse = 1;
				}
				
				// Apaga a flag auxiliar, indicando que o botão foi solto
				encoder->flagButtonAux = 0;
			}
		}
	}

	// Máquina de estados do funcionamento do encoder
	switch (encoder->fsm)
	{
		case 0:
			if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 1;
			else if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 4;
			break;

		// Sentido Horário
		case 1:
			if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 2;
			else if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 0;
			break;

		case 2:
			if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 3;
			else if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 1;
			break;

		case 3:
			if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
			{
				++encoder->quantPulsos;
				encoder->fsm = 0;
			}
			else if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 2;
			break;

		// Sentido Anti-Horário
		case 4:
			if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 5;
			else if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 0;
			break;

		case 5:
			if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 6;
			else if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 4;
			break;

		case 6:
			if (HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
			{
				--encoder->quantPulsos;
				encoder->fsm = 0;
			}
			else if (!HAL_GPIO_ReadPin(encoder->clock.gpioPort, encoder->clock.gpioPin) && !HAL_GPIO_ReadPin(encoder->data.gpioPort, encoder->data.gpioPin))
				encoder->fsm = 5;
			break;
	}

	return OK_ENCODER;
}


/********************************************************************
 *	SUBROTINA QUE RETORNA A QUANTIDADE DE PULSOS LIDOS PELO ENCODER
 ********************************************************************/
int16_t LeEncoder (encoder_t *encoder)
{
	if (encoder->habilitaEncoder == 0)
		return 0;

	return (encoder->quantPulsos);
}


/********************************************************************
 *	SUBROTINA QUE ZERA A CONTAGEM DE PULSOS DO ENCODER
 ********************************************************************/
check_encoder_t ZeraEncoder (encoder_t *encoder)
{
	if (encoder->habilitaEncoder == 0)
		return ERRO_ENCODER;

	encoder->quantPulsos = 0;

	return OK_ENCODER;
}


/********************************************************************
 *	SUBROTINA QUE RETORNA O MODO COMO O BOTÃO FOI PRESSIONADO
 ********************************************************************/
check_encoder_t LeBotaoEncoder (encoder_t *encoder)
{
	if (encoder->habilitaEncoder == 0)
		return ERRO_ENCODER;

	if (encoder->flagButtonPulse == 1)
	{
		encoder->flagButtonPulse = 0;
		return PULSE_BUTTON;
	}

	if (encoder->flagButtonPress == 1)
	{
		encoder->flagButtonPress = 0;
		return PRESS_BUTTON;
	}

	return NO_PRESS_BUTTON;
}
