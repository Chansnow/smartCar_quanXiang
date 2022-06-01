/*
 * Flash.h
 *
 *  Created on: 2021Äê3ÔÂ1ÈÕ
 *      Author: plute
 */

#ifndef CODE_FLASH_H_
#define CODE_FLASH_H_


typedef enum
{
    Flash_flash_a_test,

    Flash_Max,
}flash_date;

void FLASH_WriteALL(void);
void FLASH_ReadALL(void);





#endif /* CODE_FLASH_H_ */
