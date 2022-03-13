/*
 * _app.c
 *
 *  Created on: Mar 6, 2022
 *      Author: ctbri
 */

#include "_app.h"

typedef struct	// object_t
{
	const uint16_t *picture;
	const uint16_t sizeX;
	const uint16_t sizeY;
	uint16_t positionX;
	uint16_t positionY;
} object_t;

object_t ball =
{
	.picture = sprite_ball_16x16,
	.sizeX = 16,
	.sizeY = 16,
	.positionX = 57,
	.positionY = 240-75-HEIGHT_JUMP-1
};

object_t basketballHoop =
{
	.picture = sprite_basketball_hoop_40x55,
	.sizeX = 40,
	.sizeY = 55,
	.positionX = 237,
	.positionY = 90-1
};

object_t boy01 =
{
	.picture = sprite_boy_01_34x75,
	.sizeX = 34,
	.sizeY = 75,
	.positionX = 20,
	.positionY = 240-75-1
};

object_t boy02 =
{
	.picture = sprite_boy_02_34x75,
	.sizeX = 34,
	.sizeY = 75,
	.positionX = 20,
	.positionY = 240-75-1
};

object_t boy03 =
{
	.picture = sprite_boy_03_34x75,
	.sizeX = 34,
	.sizeY = 75,
	.positionX = 20,
	.positionY = 240-75-HEIGHT_JUMP-1
};

object_t intensityBar =
{
	.sizeX = 240,
	.sizeY = 40,
	.positionX = 40,
	.positionY = 20
};

static void IntensityBar (uint8_t positionCursor);

void _main (void)
{
	uint8_t rxDataUsart;
	uint8_t positionCursor;
	uint8_t gameState = 0;
	uint16_t point = 0;
	
	HAL_TIM_Base_Start(&htim1);
	tft_gpio_init();
	tft_init(tft_readID());
	setRotation(LANDSCAPE);
	setTextBackColor(BLACK);

	HAL_UART_Receive_IT(&huart2, &rxDataUsart, sizeof(rxDataUsart));

	while (1)
	{
		switch (gameState)
		{
			uint8_t buffer[20];

			case 0:
				fillScreen(WHITE);
				fillScreen(WHITE);

				_drawRGBBitmap(boy01.positionY, boy01.positionX, boy01.picture, boy01.sizeY, boy01.sizeX);
				_drawRGBBitmap(basketballHoop.positionY, basketballHoop.positionX, basketballHoop.picture, basketballHoop.sizeY, basketballHoop.sizeX);

				setFont(&mono12x7);
				setTextColor(RED);
				setCursor(40, 100);
				snprintf((char *)buffer, sizeof(buffer), "Placar: %d", point);
				printstr(buffer);

				rxDataUsart = 0;
				positionCursor = 0;
				++gameState;
				break;

			case 1:
				if (rxDataUsart)
				{
					if (rxDataUsart == ' ') ++gameState;

					rxDataUsart = 0;
					HAL_UART_Receive_IT(&huart2, &rxDataUsart, sizeof(rxDataUsart));
				}
				else
				{
					++positionCursor;
					if (positionCursor > MAX_POSITION_CURSOR) positionCursor = 1;
					IntensityBar(positionCursor);
					HAL_Delay(100);
				}
				break;

			case 2:
				for (uint8_t positionBoy = 0; positionBoy < HEIGHT_JUMP; ++positionBoy)
				{
					fillRect(boy02.positionX, boy02.positionY - positionBoy, boy02.sizeX, boy02.sizeY+1, WHITE);
					_drawRGBBitmap(boy02.positionY - positionBoy, boy02.positionX, boy02.picture, boy02.sizeY, boy02.sizeX);
					HAL_Delay(10);
				}

				_drawRGBBitmap(boy03.positionY, boy03.positionX, boy03.picture, boy03.sizeY, boy03.sizeX);
				++gameState;
				break;

			case 3:
			{
				uint8_t velocity = (MAX_VELOCITY / MAX_POSITION_CURSOR) * positionCursor;
				uint16_t rPositionX = 0;
				uint16_t rPositionY = 0;

				while ((ball.positionX + rPositionX) < HEIGHT && (ball.positionY - rPositionY) < WIDTH)
				{
					rPositionY = rPositionX - (rPositionX*rPositionX)/(velocity*velocity);

					_drawRGBBitmap(ball.positionY - rPositionY, ball.positionX + rPositionX, ball.picture, ball.sizeY, ball.sizeX);
					HAL_Delay(50);

					if ((ball.positionX + rPositionX) > basketballHoop.positionX 							&&
						(ball.positionX + rPositionX) < (basketballHoop.positionX + basketballHoop.sizeX)	&&
						(ball.positionY - rPositionY) > basketballHoop.positionY							&&
						(ball.positionY - rPositionY) < (basketballHoop.positionY + basketballHoop.sizeY)	 )
					{
						break;
					}
					else
					{
						rPositionX = rPositionX + 20;
					}
				}

				++gameState;
				break;
			}

			case 4:
				setFont(&mono18x7bold);
				setTextColor(WHITE);
				setCursor(60, 140);

				if (positionCursor == TARGET_POSITION_CURSOR)
				{
					printstr_bc((uint8_t *)"ACERTOU!!!");
					point = point + 3;
				}
				else
				{
					printstr_bc((uint8_t *) "ERROOUU!!!");
				}

				HAL_Delay(3000);
				gameState = 0;
				break;
		}
	}
}
static void IntensityBar (uint8_t positionCursor)
{
	static const uint16_t color[] =
	{
		0xDEFB,		// Gray
		0x33A7,		// Green 1
		0x6427,		// Green 2
		0x9486,		// Green 3
		0xCD07,		// Yellow 1
		0xFD87,		// Yellow 2
		0xFC85,		// Orange 1
		0xFBA4,		// Orange 2
		0xFAC3,		// Orange 3
		0xF9C2,		// Red 1
		0xF8E1		// Red 2
	};

	static const uint16_t numberDivision = sizeof(color) / sizeof(color[0]) - 1;

	if (positionCursor > numberDivision)
		return;

	uint16_t height = intensityBar.sizeY;
	uint16_t width = intensityBar.sizeX / numberDivision;

	for (uint8_t colorScale = 1; colorScale <= positionCursor; ++colorScale)
	{
		fillRect(intensityBar.positionX + width * (colorScale - 1), intensityBar.positionY, width, height, color[colorScale]);
	}

	for (uint8_t grayScale = positionCursor; grayScale < numberDivision; ++grayScale)
	{
		fillRect(intensityBar.positionX + width * grayScale, intensityBar.positionY, width, height, color[0]);
	}
}
