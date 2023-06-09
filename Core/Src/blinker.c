/*
 * blinker.c
 *
 *  Created on: Jun 9, 2023
 *      Author: Psi
 */

#include "main.h"

void blinker_Blink(uint16_t d, int16_t repeats) {
	while (repeats != 0) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(d);

		if (repeats != -1)
			repeats--;
	}
}

void blinker_Heartbeat(uint16_t shortBeat, uint16_t longBeat, int16_t repeats) {
	while (repeats != 0) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(shortBeat);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(shortBeat);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(shortBeat);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(longBeat);

		if (repeats != -1)
			repeats--;
	}
}
