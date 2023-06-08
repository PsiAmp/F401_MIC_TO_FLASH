/*
 * audio.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Psi
 */

#include "main.h"
#include "audio.h"
#include "flash.h"

volatile int32_t audioDMABuffer[AUDIO_FRAME_SIZE * 2 * 4];
int16_t audioBuffer[AUDIO_FRAME_SIZE];

extern I2S_HandleTypeDef hi2s3;

void audio_Start() {
	HAL_I2S_Receive_DMA(&hi2s3, (uint16_t *)&audioDMABuffer, AUDIO_FRAME_SIZE * 4);
}

void audio_HalfCallback() {
	audio_ProcessDMABuffer(0);
}

void audio_FullCallback() {
	audio_ProcessDMABuffer(AUDIO_FRAME_SIZE * 4);
}

void audio_ProcessDMABuffer(uint16_t dmaBufferStart) {
	for (int i = 0; i < AUDIO_FRAME_SIZE; i++) {
		audioBuffer[i] = (int16_t)audioDMABuffer[dmaBufferStart + i * 4];
	}

	// Write audioBuffer to Flash
	flash_Mount();
	flash_WriteAppend("shahed.fp", &audioBuffer[0], AUDIO_FRAME_SIZE * 2);
	flash_Unmount();
}

