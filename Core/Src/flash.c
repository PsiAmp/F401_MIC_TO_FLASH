/*
 * flash.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Psi
 */

#include "flash.h"
#include "fatfs.h"

FRESULT flash_Mount() {
	FRESULT fr = f_mount(&USERFatFS, "/", 1);
	return fr;
}

FRESULT flash_Unmount() {
	FRESULT fr = f_mount(0, "", 0);
	return fr;
}

FRESULT flash_OpenFile(FIL *file, char *name) {
	FRESULT fr;
	fr = f_open(file, name, FA_OPEN_APPEND | FA_WRITE);
	return fr;
}

FRESULT flash_CloseFile(FIL *file) {
	FRESULT fr;
	fr = f_close(file);
	return fr;
}

FRESULT flash_WriteAppend(FIL *file, uint8_t *data, uint32_t size) {
	UINT bwr;
	FRESULT fr;
	fr = f_write(file, data, size, &bwr);
	return fr;
}
