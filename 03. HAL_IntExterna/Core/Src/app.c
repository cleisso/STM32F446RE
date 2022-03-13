/*
 * app.c
 *
 *  Created on: Jan 7, 2022
 *      Author: ctbri
 */

/* OBS: Quando utiliza-se interrupção, não deve-se utilizar a função HAL_Delay, pois ela depende também da interrupção
 * da SysTick, acarretando no travamento do sistema. Essa função apenas deve ser utilizada fora da interrupção!
 * Deve-se evitar "while" dentro da interrupção pois isso também poderá afetar significativamente a precisão do SysTick!
 */

#include "app.h"

void _main (void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

	while (1);
}
