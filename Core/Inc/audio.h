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
void audio_Pause();
void audio_Resume();
void audio_HalfCallback();
void audio_FullCallback();
void audio_ProcessDMABuffer(uint16_t dmaBufferStart);
void audio_ToggleRecord();
int16_t* audio_GetBuffer();
uint8_t* audio_BufferUpdated();

#endif /* INC_AUDIO_H_ */
