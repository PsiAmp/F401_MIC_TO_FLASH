/*
 * blinker.h
 *
 *  Created on: Jun 9, 2023
 *      Author: Psi
 */

#ifndef INC_BLINKER_H_
#define INC_BLINKER_H_

void blinker_BlinkOnce();
void blinker_Blink(uint16_t d);
void blinker_Heartbeat(uint16_t shortBeatDelay, uint8_t shortBeats, uint16_t longBeatDelay, uint8_t longBeats, int16_t repeats);

#endif /* INC_BLINKER_H_ */
