/*
 * flash.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Psi
 */


#include "flash.h"
#include "fatfs.h"

void flash_Mount() {
	FRESULT fr = f_mount(&USERFatFS, "/", 0);
	if (fr != FR_OK) {
		__NOP();
	}
}

void flash_Unmount() {
	FRESULT fr = f_mount(0, "", 0);
	if (fr != FR_OK) {
		__NOP();
	}
}

void flash_WriteAppend(char *name, uint8_t *data, uint32_t size) {
	UINT bwr;
	FRESULT fr;
	FIL file;

	fr = f_open(&file, "123.txt", FA_OPEN_APPEND | FA_WRITE);

	if (fr != FR_OK) {
		__NOP();
	}

	fr = f_write(&file, data, size, &bwr);

	if (fr != FR_OK) {
		__NOP();
	}

	f_close(&file);
}