/*
 * _rcc.h
 *
 *  Created on: Jan 23, 2022
 *      Author: ctbri
 */

#ifndef INC__RCC_H_
#define INC__RCC_H_

#include "main.h"

#define USE_PLL

#define RCC_ADDRESS		(RCC_BASE)

#define _HSI_FREQUENCY	(16000000UL)	// High Speed Internal Clock - Definido de fábrica
#define _PLLM			(8)				// Deve ser um número entre 2 a 63. A saída de frequência deve ser entre 1MHz e 2MHz (recomendado, para evitar jitter)
#define _PLLN			(50)			// Deve ser um número entre 50 e 432. A saída de frequência deve ser entre 100MHz e 432MHz
#define _PLLP			(4)				// Deve ser um número entre 2, 4, 6 e 8. A saída de frequência deve ser entre 24MHz e 180MHz
#define _PLLR			(5)				// Deve ser um número entre 2 a 7. A saída de frequência deve ser entre 24MHz e 180MHz

#define _HPRE			(1)				// Deve ser um número entre 1, 2, 4, 8, 16, 64, 128, 256 e 512. A saída deve ser pelo menos maior que 25MHz
#define _PPRE1			(1)				// Deve ser um número entre 1, 2, 4, 8 e 16. A saída não deve ser maior que 45MHz (APB Low-Speed Prescaler)
#define _PPRE2			(1)				// Deve ser um número entre 1, 2, 4, 8 e 16. A saída não deve ser maior que 90MHz (APB High-Speed Prescaler)


typedef volatile struct
{
	uint32_t CR;			// RCC Clock Control Register
	uint32_t PLLCFGR;		// RCC PLL Configuration Register
	uint32_t CFGR;			// RCC Clock Configuration Register
	uint32_t CIR;			// RCC Clock Interrupt Register

	uint32_t AHB1RSTR;		// RCC AHB1 Peripheral Reset Register
	uint32_t AHB2RSTR;		// RCC AHB2 Peripheral Reset Register
	uint32_t AHB3RSTR;		// RCC AHB3 Peripheral Reset Register
	uint32_t APB1RSTR;		// RCC APB1 Peripheral Reset Register
	uint32_t APB2RSTR;		// RCC APB2 Peripheral Reset Register

	uint32_t AHB1ENR;		// RCC AHB1 Peripheral Clock Enable Register
	uint32_t AHB2ENR;		// RCC AHB2 Peripheral Clock Enable Register
	uint32_t AHB3ENR;		// RCC AHB3 Peripheral Clock Enable Register
	uint32_t APB1ENR;		// RCC APB1 Peripheral Clock Enable Register
	uint32_t APB2ENR;		// RCC APB2 Peripheral Clock Enable Register

	uint32_t AHB1LPENR;		// RCC AHB1 Peripheral Clock Enable in Low Power Mode Register
	uint32_t AHB2LPENR;		// RCC AHB2 Peripheral Clock Enable in Low Power Mode Register
	uint32_t AHB3LPENR;		// RCC AHB3 Peripheral Clock Enable in Low Power Mode Register
	uint32_t APB1LPENR;		// RCC APB1 Peripheral Clock Enable in Low Power Mode Register
	uint32_t APB2LPENR;		// RCC APB2 Peripheral Clock Enable in Low Power Mode Register

	uint32_t BDCR;			// RCC Backup Domain Control Register
	uint32_t CSR;			// RCC Clock Control and Status Register
	uint32_t SSCGR;			// RCC Spread Spectrum Clock Generation Register

	uint32_t PLLI2SCFGR;	// RCC PLL I2S Configuration Register
	uint32_t PLLSAICFGR;	// RCC PLL SAI Configuration Register
	uint32_t DCKCFGR;		// RCC Dedicated Clock Configuration Register
	uint32_t CKAGATENR;		// RCC Clocks Gated Enable Register
	uint32_t DCKCFGR2;		// RCC Dedicated Clock Configuration Register 2
} rcc_t;

void InicializaRCC (void);

#if (!(_PLLM >= 2 && _PLLM <= 63))
	#error ("Parametro PLLM deve ser um numero entre 2 e 63")
#endif

#if (!(_PLLN >= 50 && _PLLN <= 432))
	#error ("Parametro PLLN deve ser um numero entre 50 e 432")
#endif

#if (!(_PLLP == 2 || _PLLP == 4 || _PLLP == 6 || _PLLP == 8))
	#error ("Parametro PLLP deve ser um numero entre 2, 4, 6 e 8")
#endif

#if (!(_PLLR >= 2 && _PLLR <= 7))
	#error ("Parametro PLLR deve ser um numero entre 2 e 7")
#endif

#if (!(_HPRE == 1 || _HPRE == 2 || _HPRE == 4 || _HPRE == 16 || _HPRE == 64 || _HPRE == 128 || _HPRE == 256 || _HPRE == 512))
	#error ("Parametro HPRE deve ser um numero entre 1, 2, 4, 6, 8, 16, 64, 128, 256 e 512")
#endif

#if (!(_PPRE1 == 1 || _PPRE1 == 2 || _PPRE1 == 4 || _PPRE1 == 6 || _PPRE1 == 8))
	#error ("Parametro PPRE1 deve ser um numero entre 1, 2, 4, 6 e 8")
#endif

#if (!(_PPRE2 == 1 || _PPRE2 == 2 || _PPRE2 == 4 || _PPRE2 == 6 || _PPRE2 == 8))
	#error ("Parametro PPRE1 deve ser um numero entre 1, 2, 4, 6 e 8")
#endif

#if (!((_HSI_FREQUENCY / _PLLM) >= 1000000UL && (_HSI_FREQUENCY / _PLLM) <= 2000000UL))
	#error ("HSI_FREQUENCY / PLLM deve estar entre 1MHz e 2MHz")
#endif

#if (!((_HSI_FREQUENCY / _PLLM * _PLLN) >= 100000000UL && (_HSI_FREQUENCY / _PLLM * _PLLN) <= 432000000UL))
	#error ("HSI_FREQUENCY / PLLM * PLLN deve estar entre 100MHz e 432MHz")
#endif

#if (!((_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP) >= 24000000UL && (_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP) <= 180000000UL))
	#error ("HSI_FREQUENCY / PLLM * PLLN / PLLP deve estar entre 24MHz e 180MHz")
#endif

#if (!((_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP / _HPRE) >= 25000000UL && (_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP / _HPRE) <= 180000000UL))
	#error ("HSI_FREQUENCY / PLLM * PLLN / PLLP / HPRE deve estar entre 25MHz e 180MHz")
#endif

#if (!((_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP / _HPRE / _PPRE1) <= 45000000UL))
	#error ("HSI_FREQUENCY / PLLM * PLLN / PLLP / HPRE / PPRE1 deve ser menor que 45MHz")
#endif

#if (!((_HSI_FREQUENCY / _PLLM * _PLLN / _PLLP / _HPRE / _PPRE2) <= 45000000UL))
	#error ("HSI_FREQUENCY / PLLM * PLLN / PLLP / HPRE / PPRE2 deve ser menor que 90MHz")
#endif

#endif /* INC__RCC_H_ */
