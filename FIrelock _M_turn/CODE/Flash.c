/*
 * Flash.c
 *
 *  Created on: 2021Äê3ÔÂ1ÈÕ
 *      Author: plute
 */
#include "FIRELOCK.h"
 uint32 write_buff[40];
 uint32 read_buff[40];


void FLASH_WriteALL(void)
{
    write_buff[0]=position_zp0;
    write_buff[1]=position_zp1;
   // write_buff[2]=def_speed;
    write_buff[3]=position_zi0;
    write_buff[4]=position_zd0;
//    write_buff[5]=limit_p_out;
//    write_buff[6]=limit_pid_out;
    write_buff[7]=SETmotor_kp;
    write_buff[8]=SETmotor_ki;
    write_buff[9]=SETmotor_kd;
//    write_buff[10]=gyro_kalman_q;
//    write_buff[11]=gyro_kalman_r;

    write_buff[13]=mpu_offset;
    write_buff[14]=Speed_Limit;
    write_buff[15]=Set_Speed;
  //  write_buff[16]=mode_SP;
    write_buff[17]=HIGH_Speed;
    write_buff[18]=LOW_speed;
    write_buff[19]=is_fuzzy ;
   // write_buff[20]=stop_flag;
    write_buff[21]=k_curve;
    write_buff[22]=k_curve_in;
    write_buff[23]=k_curve_out;
    write_buff[24]=Rush_Speed;
//    write_buff[25]=pvlr_p;
//    write_buff[26]=pvlr_d;
//    write_buff[27]=pvfb;
    write_buff[28]=RING_Speed;
    write_buff[29]=RING_ru_Speed;
    write_buff[30]=X_Speed;
    write_buff[31]=position_zp0_x;
    write_buff[32]=position_zp1_x;
    write_buff[33]=position_zi0_x;
    write_buff[34]=position_zd0_x;
    write_buff[35]=steer_go;
    write_buff[36]=high_icm;
    write_buff[37]=K_centre;
    write_buff[38]=e_Foresight_threshold;


    flash_page_program(FLASH_SECTION_15,FLASH_PAGE_0,write_buff,40);
}


void FLASH_ReadALL(void)
{

     flash_page_read(FLASH_SECTION_15, FLASH_PAGE_0, read_buff, 40);
     position_zp0=read_buff[0];
     position_zp1=read_buff[1];
    // def_speed=read_buff[2];
     position_zi0=read_buff[3];
     position_zd0=read_buff[4];
//     limit_p_out=read_buff[5];
//     limit_pid_out=read_buff[6];
     SETmotor_kp=read_buff[7];
     SETmotor_ki=read_buff[8];
     SETmotor_kd=read_buff[9];
//     gyro_kalman_q=read_buff[10];
//     gyro_kalman_r=read_buff[11];

     mpu_offset=read_buff[13];
    // Speed_Limit=read_buff[14];
     Set_Speed=read_buff[15];
   //  mode_SP=read_buff[16];
     HIGH_Speed=read_buff[17];
     LOW_speed=read_buff[18];
     is_fuzzy =read_buff[19];
   //  stop_flag=read_buff[20];

     k_curve=read_buff[21];
     k_curve_in=read_buff[22];
     k_curve_out=read_buff[23];
     Rush_Speed=read_buff[24];
     pvlr_p =read_buff[25];
     pvlr_d=read_buff[26];
//     pvfb=read_buff[27];
     RING_Speed=read_buff[28];
     RING_ru_Speed=read_buff[29];
     X_Speed=read_buff[30];

     position_zp0_x=read_buff[31];
     position_zp1_x=read_buff[32];
     position_zi0_x=read_buff[33];
     position_zd0_x=read_buff[34];

     steer_go=read_buff[35];

     high_icm=read_buff[36];
     K_centre=read_buff[37];
     e_Foresight_threshold=read_buff[38];
}

