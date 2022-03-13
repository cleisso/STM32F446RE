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

#define LANDSCAPE	(1)

void _main (void);

#endif /* INC__APP_H_ */
