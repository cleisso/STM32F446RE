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

#include "stdio.h"

#include "main.h"
#include "usart.h"

void _main (void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC__APP_H_ */
