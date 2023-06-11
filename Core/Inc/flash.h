/*
 * flash.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Psi
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"
#include "fatfs.h"

FRESULT flash_Mount();
FRESULT flash_Unmount();
FRESULT flash_OpenFile(FIL *file, char *name);
FRESULT flash_CloseFile(FIL *file);
FRESULT flash_WriteAppend(FIL *file, uint8_t *data, uint32_t size);

#endif /* INC_FLASH_H_ */
