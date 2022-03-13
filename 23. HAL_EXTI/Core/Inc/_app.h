/*
 * _app.h
 *
 *  Created on: Feb 13, 2022
 *      Author: ctbri
 */

#ifndef INC__APP_H_
#define INC__APP_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "main.h"

void _main (void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* INC__APP_H_ */
