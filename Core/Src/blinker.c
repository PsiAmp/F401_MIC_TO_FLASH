/*
 * blinker.c
 *
 *  Created on: Jun 9, 2023
 *      Author: Psi
 */

#include "main.h"

void blinker_BlinkOnce() {
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void blinker_Blink(uint16_t d, int16_t repeats) {
	while (repeats != 0) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(d);

		if (repeats != -1)
			repeats--;
	}
}

void blinker_Heartbeat(uint16_t shortBeatDelay, uint8_t shortBeats, uint16_t longBeatDelay, uint8_t longBeats, int16_t repeats) {
	while (repeats != 0) {
		for (int i = 0; i < shortBeats; i++) {
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			HAL_Delay(shortBeatDelay);
		}

		for (int i = 0; i < longBeats; i++) {
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			HAL_Delay(longBeatDelay);
		}

		if (repeats != -1)
			repeats--;
	}
}
