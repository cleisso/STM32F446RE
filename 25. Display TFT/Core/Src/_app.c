/*
 * _app.c
 *
 *  Created on: Mar 2, 2022
 *      Author: ctbri
 */

#include "_app.h"

/*	Funções da Biblioteca de TFT
 *
 * Inicializa o LCD a partir do seu ID (Driver do display)
 * void tft_init (uint16_6 ID);
 *
 * Reseta o LCD
 * void reset (void);
 *
 * Retorna a leitura do ID do display
 * uint16_t tft_readID (void);
 *
 * Ajusta a orientação do LCD
 * void setRotation (uint8_t rotation);
 * Permite 4 configurações:
 * 		- 0: Modo Retrato: 		MY (Linha) = 0 (de cima para baixo)
 * 						   		MX (Coluna) = 1 (da esquerda para direita)
 * 						   		MV (Row/Column Exchange) = 0 (Retrato)
 * 						   		ML (Refresh Vertical) = 0 (de cima para baixo)
 * 						  		MH (Refresh Horizontal) = 0 (da esquerda para direita)
 *
 * 		- 1: Modo Paisagem: 	MY (Linha) = 0 (de cima para baixo)
 * 						   		MX (Coluna) = 0 (da direita para esquerda)
 * 						   		MV (Row/Column Exchange) = 1 (Paisagem)
 * 						   		ML (Refresh Vertical) = 0 (de cima para baixo)
 * 						   		MH (Refresh Horizontal) = 0 (da esquerda para direita)
 *
 * 		- 2: Modo Retrato 180:	MY (Linha) = 1 (de baixo para cima)
 * 						   		MX (Coluna) = 0 (da direita para esquerda (de cabeça p/ baixo fica esquerda para direita))
 * 						   		MV (Row/Column Exchange) = 0 (Retrato)
 * 						  		ML (Refresh Vertical) = 1 (de baixo para cima)
 * 						   		MH (Refresh Horizontal) = 0 (da esquerda para direita)
 *
 * 		- 3: Modo Paisagem 180:	MY (Linha) = 1 (de baixo para cima)
 * 						   		MX (Coluna) = 1 (da direita para esquerda)
 * 						   		MV (Row/Column Exchange) = 1 (Paisagem)
 * 						   		ML (Refresh Vertical) = 1 (de baixo para cima)
 * 						   		MH (Refresh Horizontal) = 0 (da esquerda para direita)
 *
 * Inverte as cores do display
 * void invertDisplay (uint8_t invert);	0: não inverte as cores
 * 										1: inverte as cores
 *
 * Realiza o scroll vertical da tela. Determina uma região (delimitado pelo "inicio"
 * e "fim") e realiza o deslocamento através do "offset"
 * (positivo - deslocamento para cima, negativo - deslocamento para baixo)
 * void vertScroll (int16_t begin, int16_t end, int16_t offset);
 *
 * Desenha um pixel na tela
 * void drawPixel (int16_t linha, int16_t coluna, uint16_t cor);
 */

extern const unsigned short fosforo_95x63[5985];
extern const unsigned short bean_157x157[24649];
extern const unsigned short duck_hunt_320x240[76800];

void _main (void)
{
	HAL_TIM_Base_Start(&htim1);

	tft_gpio_init();
	tft_init(tft_readID());

	setRotation(0);
	fillScreen(WHITE);
	fillScreen(WHITE);

	//testFillScreen();

	/*printnewtstr(16, RED, &mono12x7bold, 1, (uint8_t *)"Hello World!");
	printnewtstr(32, RED, &mono12x7bold, 1, (uint8_t *)"Hello World!");
	printnewtstr(48, RED, &mono12x7bold, 1, (uint8_t *)"Hello World!");
	printnewtstr(64, RED, &mono12x7bold, 1, (uint8_t *)"Hello World!");*/
	//printnewtstr(80, RED, &mono12x7bold, 1, (uint8_t *)"Hello World!");

	/*for (int i = 0; i < 10; ++i)
	{
		drawPixel(0, i, WHITE);
		drawPixel(119, i, WHITE);
		drawPixel(239, i, WHITE);
	}*/

	/*setFont(&mono12x7bold);
	setTextColor(RED);
	setTextBackColor(WHITE);
	_setCursor(100, 0);
	printstr_bc((uint8_t*)"teste");*/

	setRotation(0);
	_drawRGBBitmap(100, 100, fosforo_95x63, 63, 95);

	while (1)
	{
	}
}
