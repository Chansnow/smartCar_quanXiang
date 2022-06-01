#include "FIRELOCK.h"

struct MOTORpid motor_1;
struct MOTORpid motor_2;
struct MOTORpid motor_3;
struct MOTORpid motor_4;
int16 LF,LB,RF,RB;
int16 lf,lb,rf,rb;

//void V_Init(struct resolution_v* wheels)
//{
//    wheels->vx = 0;
//    wheels->vy = 0;
//    wheels->vz = 0;
//    wheels->v1 = 0;
//    wheels->v2 = 0;
//    wheels->v3 = 0;
//    wheels->v4 = 0;
//}
// s1 RF s2 RB s3 LF s4 LB
void Motor_spd(int16 s1,int16 s2,int16 s3,int16 s4)
{
    if(s3>0)
            {
                pwm_duty(PWM4_CH3_B8,s3);
                pwm_duty(PWM4_CH4_B9,0);

            }
            else
            {
                pwm_duty(PWM4_CH4_B9,-s3);
                pwm_duty(PWM4_CH3_B8,0);
            }
            if(s4>0)
            {
                pwm_duty(PWM2_CH4_B11,s4);
                pwm_duty(PWM2_CH3_B10,0);
            }
            else
            {
                pwm_duty(PWM2_CH4_B11,0);
                pwm_duty(PWM2_CH3_B10,-s4);
            }
            if(s1>0)
            {
                pwm_duty(PWM4_CH2_B7,0);
                pwm_duty(PWM4_CH1_B6,s1);
            }
            else
            {
                pwm_duty(PWM4_CH2_B7,-s1);
                pwm_duty(PWM4_CH1_B6,0);
            }
            if(s2>0)
            {
                pwm_duty(PWM2_CH2_B3,s2);
                pwm_duty(PWM2_CH1_A15,0);
            }
            else
            {
                pwm_duty(PWM2_CH2_B3,0);
                pwm_duty(PWM2_CH1_A15,-s2);
            }
}

void PID_motor(int set_speed1,int set_speed2, int set_speed3, int set_speed4)
{
    int16 value1=0,value2=0,value3=0,value4=0;
//    if (Car_Y == DIR_F)
//    {
        MOTOR_PID(&motor_1, set_speed1, RF);//pid计算
        MOTOR_PID(&motor_2, set_speed2, RB);
        MOTOR_PID(&motor_3, set_speed3, LF);
        MOTOR_PID(&motor_4, set_speed4, LB);

        value1 = (int16)(motor_1.value+0.5+pwm_buchang+x_buchang_r);
        value2 = (int16)(motor_2.value+0.5-pwm_buchang+x_buchang_l);
        value3 = (int16)(motor_3.value+0.5-pwm_buchang-x_buchang_l);
        value4 = (int16)(motor_4.value+0.5+pwm_buchang-x_buchang_r);
//    }
//    else if (Car_Y == DIR_B)
//    {
//        MOTOR_PID(&motor_1, -set_speed1, RF);//pid计算
//        MOTOR_PID(&motor_2, -set_speed2, RB);
//        MOTOR_PID(&motor_3, -set_speed3, LF);
//        MOTOR_PID(&motor_4, -set_speed4, LB);
//
//        value1 = (int16)(motor_1.value+0.5+pwm_buchang+x_buchang_l);
//        value2 = (int16)(motor_2.value+0.5-pwm_buchang+x_buchang_r);
//        value3 = (int16)(motor_3.value+0.5-pwm_buchang-x_buchang_r);
//        value4 = (int16)(motor_4.value+0.5+pwm_buchang-x_buchang_l);
//
//    }
    if (value1 > (float)MOTOR_MAX) value1 = MOTOR_MAX;
    if (value1 < (float)MOTOR_MIN) value1 = MOTOR_MIN;
    if (value2 > (float)MOTOR_MAX) value2 = MOTOR_MAX;
    if (value2 < (float)MOTOR_MIN) value2 = MOTOR_MIN;
    if (value3 > (float)MOTOR_MAX) value3 = MOTOR_MAX;
    if (value3 < (float)MOTOR_MIN) value3 = MOTOR_MIN;
    if (value4 > (float)MOTOR_MAX) value4 = MOTOR_MAX;
    if (value4 < (float)MOTOR_MIN) value4 = MOTOR_MIN;

    Motor_spd(value1, value2, value3, value4);

}

void motor_init(void)
{
        pwm_init(PWM2_CH2_B3,  18000, 0);      //RB  前
        pwm_init(PWM2_CH1_A15, 18000, 0);      //RB  后
        pwm_init(PWM2_CH3_B10, 18000, 0);      //LB  前
        pwm_init(PWM2_CH4_B11, 18000, 0);     //LB  后
        pwm_init(PWM4_CH1_B6,  18000, 0);     //RF  前
        pwm_init(PWM4_CH2_B7,  18000, 0);     //RF  后
        pwm_init(PWM4_CH3_B8,  18000, 0);     //LF  前
        pwm_init(PWM4_CH4_B9,  18000, 0);     //LF  后
        pwm_init(PWM1_CH3_A10, 50,   0); //舵机
}
