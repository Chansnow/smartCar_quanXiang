#include "firelock.h"


uint32 write_buff[20];
uint32 read_buff[20];


void FLASH_WriteALL(void)
{
    write_buff[0]=slope_R;
    write_buff[1]=r_cnt0;
    write_buff[2]=r_startU;
    write_buff[3]=r_startD;
    write_buff[4]=r_error;
//    write_buff[5]=;
//    write_buff[6]=;
    write_buff[7]=Foresight_up;
    flash_page_program(FLASH_SECTION_15,FLASH_PAGE_0,write_buff,20);
}


void FLASH_ReadALL(void)
{

     flash_page_read(FLASH_SECTION_15, FLASH_PAGE_0, read_buff, 20);
     slope_R=read_buff[0];
     r_cnt0=read_buff[1];
     r_startU=read_buff[2];
     r_startD=read_buff[3];
     r_error=read_buff[4];
//     =read_buff[5];
//     =read_buff[6];
     Foresight_up=read_buff[7];
}

