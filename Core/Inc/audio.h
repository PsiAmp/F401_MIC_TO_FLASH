/*
 * audio.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Psi
 */

#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_

#define AUDIO_FRAME_SIZE 1024

void audio_Start();
void audio_HalfCallback();
void audio_FullCallback();
void audio_ProcessDMABuffer(uint16_t dmaBufferStart);

#endif /* INC_AUDIO_H_ */
