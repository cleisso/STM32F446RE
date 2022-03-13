/*
 * _app.h
 *
 *  Created on: Mar 6, 2022
 *      Author: ctbri
 */

#ifndef INC__APP_H_
#define INC__APP_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "usart.h"

#include "stdio.h"

#include "tft/fonts.h"
#include "tft/functions.h"
#include "tft/tft.h"
#include "tft/user_setting.h"

#define LANDSCAPE				(1)
#define VELOCITY				(10)
#define TIME_ANIMATION			(100)

extern const unsigned short pacman01_60x60[3600];
extern const unsigned short pacman02_60x60[3600];
extern const unsigned short pacman03_60x60[3600];
extern const unsigned short monster_28x28[784];

void _main (void);

#endif /* INC__APP_H_ */
