#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "FIRELOCK.h"

#define MOTOR_MAX       (+9800)
#define MOTOR_MIN       (-9800)
void Motor_spd(int16 s1,int16 s2,int16 s3,int16 s4);
void PID_motor(int set_speed1,int set_speed2, int set_speed3, int set_speed4);
void motor_init(void);
//void V_Init(struct resolution_v* wheels);

#endif
