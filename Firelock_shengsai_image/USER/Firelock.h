#ifndef USER_FIRELOCK_H_
#define USER_FIRELOCK_H_


#include "headfile.h"


extern uint8 ALL_flag;

extern uint8 endline_chu_hang_min;
extern uint8 slope_L,slope_R,r_cnt0,r_startU,r_startD,r_error,r_L,r_R;
extern int ringflag;
extern int ring_cnt,ring_start_R,ring_start_L;
extern uint8 ring_L,ring_R;
extern int ring_B_R;
extern uint8 startflag;
extern uint8 sanchaflag;
extern uint8 xuanzhuanflag;

extern int camera_count;
extern uint8 camera_count_flag;

extern uint8 rampflag;
extern u8 endline_Foresight;

extern uint8 endline_display;

extern float Error;
extern u8 Foresight_up ;

extern uint8 Foresight;
extern int Foresight_hang;
extern uint8 start_flag;
extern uint8 start_coner;
extern uint8 BlackEndMaxMax;

#include "Send_date.h"
#include "Init.h"
#include "Gete_image.h"
#include "Image_ring.h"
#include "Image_cross.h"
#include "Image_process.h"
#include "Key.h"
#include "menu.h"
#include "Main_control.h"
#include "flash.h"
#include "sancha.h"



#endif /* USER_FIRELOCK_H_ */
