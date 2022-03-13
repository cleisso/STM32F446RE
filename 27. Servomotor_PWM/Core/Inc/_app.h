/*
 * _app.h
 *
 *  Created on: Mar 3, 2022
 *      Author: ctbri
 */

#ifndef INC__APP_H_
#define INC__APP_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "tim.h"
#include "usart.h"

#define	SERVOMOTOR_ANGLE(x)		(htim3.Instance->CCR4 = (uint16_t)(2000.0*(x)/180.0 + 500))

void _main (void);

#endif /* INC__APP_H_ */
