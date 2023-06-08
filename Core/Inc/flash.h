/*
 * flash.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Psi
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"

void flash_Mount();
void flash_Unmount();
void flash_WriteAppend(char *name, uint8_t *data, uint32_t size);

#endif /* INC_FLASH_H_ */
