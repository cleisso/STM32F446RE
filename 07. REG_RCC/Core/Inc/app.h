/*
 * app.h
 *
 *  Created on: Jan 23, 2022
 *      Author: ctbri
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"
#include "_gpio.h"
#include "_rcc.h"

#define LED_PORT	(GPIOA)
#define LED_PIN		(5)

void _main (void);

#endif /* INC_APP_H_ */
