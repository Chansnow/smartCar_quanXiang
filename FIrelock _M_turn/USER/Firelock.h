#ifndef USER_FIRELOCK_H_
#define USER_FIRELOCK_H_





#include "headfile.h"


//====head files====
#include "Get_deta.h"
#include "Init.h"
#include "Key.h"
#include "menu.h"
#include "Motor.h"
#include "PIDcontrol.h"
#include "Control.h"
#include "Flash.h"
#include "encode.h"
#include "topicm.h"
#include "send_data.h"

#include "math.h"

/*---------------------PARAMETER---------------------*/

/*-----控制数据-------*/

extern int16 HIGH_Speed,LOW_speed;
extern int16 def_speed;
extern int16 Set_Speed;
extern int16 RING_Speed;
extern int16 RING_ru_Speed;
extern int16 X_Speed;
extern int16 UP_Speed;
extern u8 mode_SP;
extern int16 turn_vy_h,turn_vy_l,turn_vz,turn_vy;
extern float turn_value;

extern uint8 k_curve,k_curve_in,k_curve_out;

extern int steer_go;

extern int16 vx,vy;
extern float vz;
extern int16 set_x;
extern uint8 encode_count;
extern int16 GO_Speed;

extern enum car_dir_go Car_Y;
extern enum car_dir_x Car_X;


/*-----电机控制数据-------*/
extern int16 LF,LB,RF,RB;
extern int16 lf,lb,rf,rb;
extern struct resolution_v wheels;


extern int16 Speed_Limit;
extern uint8 Track_Line_Num;
extern struct MOTORpid motor_1;
extern struct MOTORpid motor_2;
extern struct MOTORpid motor_3;
extern struct MOTORpid motor_4;

extern uint8 stop_flag;

extern int pwm_buchang ;  //为满足差速要求补偿占空比
extern int x_buchang_l ;
extern int x_buchang_r ;

extern int16 Rush_Speed;

extern int16 minus_l;    //前后轮差速
extern int16 minus_r;
extern int16 pvfb ;

/*-----摄像头数据-------*/
extern uint8 camera_flag;
extern uint8  ALL_flag;

extern uint8 e_Foresight_threshold;
extern float K_centre;
extern uint8 ring_e_F;
/*-----传输数据-------*/
extern uint8 Foresight;
extern int send_up_speed[30];


/*-----菜单数据-------*/
extern int16 run_mode;
extern uint8 change_enable;
extern uint8 cwheels;
extern uint8 Skey_flag;



/*-----PID数据-------*/
extern int16 act_speed_L,act_speed_R;
extern uint8 is_fuzzy;

extern struct Positionpid pid_position;
extern struct Positionpid pid_position_X;
extern struct Turnpid pid_turn;
extern struct Positionpid pid_curve;
extern int16 SETmotor_kp;
extern int16 SETmotor_ki;
extern int16 SETmotor_kd;

extern int16 position_zp0;
extern int16 position_zp1;
extern int16 position_zi0;
extern int16 position_zd0;

extern int16 position_zp0_x;//低速p
extern int16 position_zp1_x;//高速p
extern int16 position_zi0_x;//i
extern int16 position_zd0_x;// d后两个没用


extern float limit_p_out;
extern float limit_pid_out;

extern int16 SETTurn_Kp;
extern int16 SETTurn_Ki;
extern int16 SETTurn_Kd;

extern int16 pvlr_d,pvlr_p;

extern uint8 PIDsign,Picturesign,othersign;
extern uint8 PID_state,picture_state;


/*-----陀螺仪数据-------*/
extern int16 gyro_kalman_q;
extern int16 gyro_kalman_r;
extern float gyro_z;
extern uint8 icm_flag;
extern int16 mpu_offset;
extern int16 mpu_set;
extern int high_icm;
/*-----flash数据-------*/

extern uint32 write_buff[40];
extern uint32 read_buff[40];



#endif /* USER_FIRELOCK_H_ */
