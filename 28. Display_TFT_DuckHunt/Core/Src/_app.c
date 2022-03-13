/*
 * _app.c
 *
 *  Created on: Mar 6, 2022
 *      Author: ctbri
 */

#include "_app.h"

typedef struct	// target_t
{
	int16_t posX;
	int16_t posY;
} target_t;

typedef struct	// object_t
{
	uint8_t flag;
	int16_t posX;
	int16_t posY;
} object_t;

static uint8_t targetMovement (uint8_t command);
static void targetDrawing (void);
static void shootObject (void);
static void killObject (void);
static uint8_t statusGame (void);
static void restartGame (void);

extern const unsigned short duck_hunt_320x240[76800];

target_t target = {0};

object_t duck[6] =
{
	[0].posY = 36, [0].posX = 37,
	[1].posY = 36, [1].posX = 135,
	[2].posY = 36, [2].posX = 233,
	[3].posY = 137, [3].posX = 86,
	[4].posY = 137, [4].posX = 184,
	[5].posY = 137, [5].posX = 282,
};

object_t mark[6] =
{
	[0].posY = 36, [0].posX = 86,
	[1].posY = 36, [1].posX = 184,
	[2].posY = 36, [2].posX = 282,
	[3].posY = 137, [3].posX = 37,
	[4].posY = 137, [4].posX = 135,
	[5].posY = 137, [5].posX = 233,
};

void _main (void)
{
	uint8_t rxDataUART = 0;

	HAL_TIM_Base_Start(&htim1);
	HAL_UART_Receive_IT(&huart2, &rxDataUART, 1);

	tft_gpio_init();
	tft_init(tft_readID());

	setRotation(LANDSCAPE);
	setFont(&mono18x7bold);
	setTextColor(RED);
	setTextBackColor(BLACK);
	fillScreen(WHITE);
	fillScreen(WHITE);

	_drawRGBBitmap(0, 0, duck_hunt_320x240, 240, 320);
	targetDrawing();

	while(1)
	{
		if (rxDataUART)
		{
			if (targetMovement(rxDataUART))
			{
				uint8_t message[2][20];
				uint8_t sizeMessage[2] =
				{
					[0] = snprintf((char *) message[0], sizeof(message[0]), "Target X: %u\r\n", target.posX),
					[1] = snprintf((char *) message[1], sizeof(message[1]), "Target Y: %u\r\n", target.posY)
				};

				HAL_UART_Transmit(&huart2, message[0], sizeMessage[0], 25);
				HAL_UART_Transmit(&huart2, message[1], sizeMessage[1], 25);
			}

			HAL_UART_Receive_IT(&huart2, &rxDataUART, 1);
			rxDataUART = 0;
		}
	}
}

static uint8_t targetMovement (uint8_t command)
{
	uint8_t flagAction = 1;

	switch (command)
	{
		case 'w':
			target.posY = target.posY - 10;
			if (target.posY < 0) target.posY = 0;
			break;

		case 'a':
			target.posX = target.posX - 10;
			if (target.posX < 0) target.posX = 0;
			break;

		case 's':
			target.posY = target.posY + 10;
			if (target.posY > WIDTH) target.posY = WIDTH;
			break;

		case 'd':
			target.posX = target.posX + 10;
			if (target.posX > HEIGHT) target.posX = HEIGHT;
			break;

		case ' ':
			shootObject();

			if (statusGame())
			{
				_setCursor(120, 70);
				printstr_bc((uint8_t *)"GAME OVER");
				HAL_Delay(3000);
				restartGame();
				flagAction = 0;
			}
			break;

		default:
			flagAction = 0;
			break;
	}

	if (flagAction)
	{
		_drawRGBBitmapWindow(target.posY - 30, target.posX - 30, duck_hunt_320x240, target.posY + 30, target.posX + 30);
		killObject();
		targetDrawing();
	}

	return flagAction;
}

static void targetDrawing (void)
{
	drawCircle(target.posX, target.posY, 10, RED);

	fillCircle(target.posX, target.posY, 2, RED);

	drawLine(target.posX - 13, target.posY, target.posX - 7, target.posY, RED);
	drawLine(target.posX + 13, target.posY, target.posX + 7, target.posY, RED);

	drawLine(target.posX, target.posY - 13, target.posX, target.posY - 7, RED);
	drawLine(target.posX, target.posY + 13, target.posX, target.posY + 7, RED);
}

static void shootObject (void)
{
	for (uint8_t i = 0; i < 6; ++i)
	{
		if (target.posX > (duck[i].posX - 10) &&
			target.posX < (duck[i].posX + 10) &&
			target.posY > (duck[i].posY - 10) &&
			target.posY < (duck[i].posY + 10))
		{
			duck[i].flag = 1;
			break;
		}

		if (target.posX > (mark[i].posX - 10) &&
			target.posX < (mark[i].posX + 10) &&
			target.posY > (mark[i].posY - 10) &&
			target.posY < (mark[i].posY + 10))
		{
			mark[i].flag = 1;
			break;
		}
	}
}

static void killObject (void)
{
	for (uint8_t i = 0; i < 6; ++i)
	{
		if (duck[i].flag)
			fillCircle(duck[i].posX, duck[i].posY, 25, WHITE);

		if (mark[i].flag)
			fillCircle(mark[i].posX, mark[i].posY, 25, WHITE);
	}
}

static uint8_t statusGame (void)
{
	uint8_t status = 0;

	for (uint8_t i = 0; i < 6; ++i)
	{
		if (mark[i].flag)
		{
			status = 1;
			break;
		}
	}

	return status;
}

static void restartGame (void)
{
	target.posX = 0;
	target.posY = 0;

	for (uint8_t i = 0; i < 6; ++i)
	{
		duck[i].flag = 0;
		mark[i].flag = 0;
	}

	_drawRGBBitmap(0, 0, duck_hunt_320x240, 240, 320);
	targetDrawing();
}
