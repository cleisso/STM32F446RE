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
	uint8_t flag;
} object_t;

object_t pacman[3] =
{
	[0] =
	{
		.picture = pacman01_60x60,
		.sizeX = 60,
		.sizeY = 60,
		.positionX = 0,
		.positionY = 90
	},

	[1] =
	{
		.picture = pacman02_60x60,
		.sizeX = 60,
		.sizeY = 60,
		.positionX = 0,
		.positionY = 90
	},

	[2] =
	{
		.picture = pacman03_60x60,
		.sizeX = 60,
		.sizeY = 60,
		.positionX = 0,
		.positionY = 90
	},
};

object_t monster =
{
	.picture = monster_28x28,
	.sizeX = 28,
	.sizeY = 28,
	.positionX = 270,
	.positionY = 106
};

object_t dot[] =
{
	[0].positionY = 120,

	[0].positionX = 90,
	[1].positionX = 120,
	[2].positionX = 150,
	[3].positionX = 180,
	[4].positionX = 210,
	[5].positionX = 240,
};

uint8_t pacmanAnimation = 0;
uint16_t rPositionX = 0;

static void VerifyDots (void);
static void RefreshDots (void);
static void VerifyMonster (void);
static void RefreshMonster (void);
static void ResetAnimation (void);

void _main (void)
{
	HAL_TIM_Base_Start(&htim1);
	tft_gpio_init();
	tft_init(tft_readID());
	setRotation(LANDSCAPE);
	fillScreen(BLACK);
	fillScreen(BLACK);

	while (1)
	{
		fillRect(pacman[pacmanAnimation].positionX + rPositionX - VELOCITY,
				 pacman[pacmanAnimation].positionY,
				 VELOCITY,
				 pacman[pacmanAnimation].sizeY,
				 BLACK);

		_drawRGBBitmap(pacman[pacmanAnimation].positionY,
				       pacman[pacmanAnimation].positionX + rPositionX,
					   pacman[pacmanAnimation].picture,
					   pacman[pacmanAnimation].sizeY,
					   pacman[pacmanAnimation].sizeY);

		VerifyDots();
		RefreshDots();

		VerifyMonster();
		RefreshMonster();

		rPositionX = rPositionX + VELOCITY;

		if (++pacmanAnimation == 3)
			pacmanAnimation = 0;

		if ((pacman[pacmanAnimation].positionX + rPositionX) >= 310)
			ResetAnimation();

		HAL_Delay(TIME_ANIMATION);
	}
}

static void VerifyDots (void)
{
	for (uint8_t i = 0; i < (sizeof(dot) / sizeof(dot[0])); ++i)
	{
		if (!dot[i].flag &&
			dot[i].positionX <= (pacman[pacmanAnimation].positionX + pacman[pacmanAnimation].sizeX/2 + rPositionX))
		{
			dot[i].flag = 1;
		}
	}
}

static void RefreshDots (void)
{
	for (uint8_t i = 0; i < (sizeof(dot) / sizeof(dot[0])); ++i)
	{
		if (!dot[i].flag)
		{
			fillCircle(dot[i].positionX, dot[0].positionY, 5, WHITE);
		}
	}
}

static void VerifyMonster (void)
{
	if (!monster.flag &&
		monster.positionX <= (pacman[pacmanAnimation].positionX + pacman[pacmanAnimation].sizeX/2 + rPositionX))
	{
		monster.flag = 1;
	}
}

static void RefreshMonster (void)
{
	if (!monster.flag)
	{
		_drawRGBBitmap(monster.positionY,
					   monster.positionX,
					   monster.picture,
					   monster.sizeY,
					   monster.sizeX);
	}
}

static void ResetAnimation (void)
{
	fillScreen(BLACK);
	fillScreen(BLACK);

	monster.flag = 0;

	for (uint8_t i = 0; i < (sizeof(dot) / sizeof(dot[0])); ++i)
		dot[i].flag = 0;

	pacmanAnimation = 0;
	rPositionX = 0;
}
