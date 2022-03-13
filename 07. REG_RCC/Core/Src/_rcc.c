/*
 * _rcc.c
 *
 *  Created on: Jan 23, 2022
 *      Author: ctbri
 */

#include "_rcc.h"

void InicializaRCC (void)
{
	rcc_t *rcc = (rcc_t *)RCC_ADDRESS;
	uint8_t nop;
	//uint8_t statusInit = 0;

	// Configurando o regulador de tensão interno principal (não estudado)
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	// Realizando a inicialização da árvore de clock
	// Verificando se o PLL está ligado. Se estiver, alterar a fonte de Clock (HSI)
	if ((rcc->CFGR >> 2) & 0x3UL)
		rcc->CFGR &= ~(0x3UL);

	++nop;
	++nop;

	__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_0);

	// Realizando a configuração do PLL
	#ifdef USE_PLL
		// Desligando o PLL
		rcc->CR = rcc->CR & ~(0x1UL << 24);
		// Aguardando o PLL ser desligado
		while ((rcc->CR >> 25) & 0x1UL);

		// Ajustando o PLLM
		rcc->PLLCFGR = (rcc->PLLCFGR & ~(0x3FUL << 0))  | (_PLLM << 0);
		// Ajustando o PLLN
		rcc->PLLCFGR = (rcc->PLLCFGR & ~(0x1FFUL << 6)) | (_PLLN << 6);
		// Ajustando o PLLP
		rcc->PLLCFGR = (rcc->PLLCFGR & ~(0x3UL << 16))  | (_PLLP << 16);
		// Ajustando o PLLR
		rcc->PLLCFGR = (rcc->PLLCFGR & ~(0x7UL << 28))  | (_PLLR << 28);
	#endif

	// Configurando o Prescaler para o HCLK, APB1 e APB2
	// Ajustando o Prescaler de HCLK
	switch (_HPRE)
	{
		default:	rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4));
		case 2:		rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0x8UL << 4);	break;
		case 4:		rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0x9UL << 4);	break;
		case 8:		rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0xAUL << 4);	break;
		case 16:	rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0xBUL << 4);	break;
		case 64:	rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0xCUL << 4);	break;
		case 128:	rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0xDUL << 4);	break;
		case 256:	rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0xEUL << 4);	break;
		case 512:	rcc->CFGR = (rcc->CFGR & ~(0xFUL << 4)) | (0xFUL << 4);	break;
	}

	// Ajustando o Prescaler de APB1
	switch (_PPRE1)
	{
		default:	rcc->CFGR = (rcc->CFGR & ~(0x7UL << 10));
		case 2:		rcc->CFGR = (rcc->CFGR & ~(0x7UL << 10)) | (0x4UL << 10);	break;
		case 4:		rcc->CFGR = (rcc->CFGR & ~(0x7UL << 10)) | (0x5UL << 10);	break;
		case 8:		rcc->CFGR = (rcc->CFGR & ~(0x7UL << 10)) | (0x6UL << 10);	break;
		case 16:	rcc->CFGR = (rcc->CFGR & ~(0x7UL << 10)) | (0x7UL << 10);	break;
	}

	// Ajustando o Prescaler de APB2
	switch (_PPRE2)
	{
		default:	rcc->CFGR = (rcc->CFGR & ~(0x7UL << 13));
		case 2:		rcc->CFGR = (rcc->CFGR & ~(0x7UL << 13)) | (0x4UL << 13);	break;
		case 4:		rcc->CFGR = (rcc->CFGR & ~(0x7UL << 13)) | (0x5UL << 13);	break;
		case 8:		rcc->CFGR = (rcc->CFGR & ~(0x7UL << 13)) | (0x6UL << 13);	break;
		case 16:	rcc->CFGR = (rcc->CFGR & ~(0x7UL << 13)) | (0x7UL << 13);	break;
	}

	// Selecionando a fonte de CLK
	#ifdef USE_PLL
		// Ligando o PLL
		rcc->CR = rcc->CR | (0x1UL << 24);
		// Aguardando o PLL ser ligado
		while (!((rcc->CR >> 25) & 0x1UL));

		// Selecionando a fonte de CLK como a saída de PLL
		rcc->CFGR = (rcc->CFGR & ~(0x3UL << 0)) | (0x2UL << 0);

		switch (_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP / _HPRE / 30000000UL)
		{
			case 0:		__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_0);	break;
			case 1:		__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);	break;
			case 2:		__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_2);	break;
			case 3:		__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_3);	break;
			case 4:		__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_4);	break;
			default:	__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_5);	break;
		}
	#endif

	//return statusInit;
}
