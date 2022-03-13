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
#define MAX_VELOCITY			(25.5)
#define TARGET_POSITION_CURSOR	(6)
#define MAX_POSITION_CURSOR		(10)
#define HEIGHT_JUMP				(20)

extern const unsigned short sprite_ball_16x16[256];
extern const unsigned short sprite_basketball_hoop_40x55[2200];
extern const unsigned short sprite_boy_01_34x75[2550];
extern const unsigned short sprite_boy_02_34x75[2550];
extern const unsigned short sprite_boy_03_34x75[2550];

void _main (void);

#endif /* INC__APP_H_ */
