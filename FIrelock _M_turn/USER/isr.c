#include "FIRELOCK.h"
#include "isr.h"
#include "headfile.h"

extern uint8 mpu_flag;
extern float gyro_c;
extern uint8 xuanzhuan_en;

void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update );


        icm_flag=1;
        encode_count++;
        encode();

        if(encode_count==3)
        {
            encode_count=0;
            encode_calculation();
            act_speed_L = (LF+LB)/2;
            act_speed_R = (RF+RB)/2;
             minus_l = LB - LF;
             minus_r = RB - RF;
//             send_up_speed[0]=LF;
//             send_up_speed[1]=wheels.v2;
//             send_up_speed[2]=LB;
//             send_up_speed[3]=wheels.v3;
//             send_up_speed[4]=RF;
//             send_up_speed[5]=wheels.v1;
//             send_up_speed[6]=RB;
//             send_up_speed[7]=wheels.v4;
             PID_motor(wheels.v1,wheels.v4,wheels.v2,wheels.v3);  //速度设置

             if(mpu_flag==1)
             {
                 gyro_c+=gyro_z*0.021;
                 if(gyro_c>80)
                 {
                     xuanzhuan_en=1;
                     mpu_flag=0;
                     gyro_c=0;
                 }
             }
             if(mpu_flag==2)
             {
                 gyro_c+=-gyro_z*0.021;
                 if(gyro_c>80)
                 {
                     xuanzhuan_en=1;
                     mpu_flag=0;
                     gyro_c=0;
                 }
             }




             if(Abs(LF)>Speed_Limit||Abs(RF)>Speed_Limit||Abs(LB)>Speed_Limit||Abs(RB)>Speed_Limit)      //保护措施1
             {
               motor_init();
               while(1)
               {
                    oled_int16(1, 3, 404);
                    Speed_caculation(&wheels,0,0,0);

               }

             }




        }
    }
}

void USART2_IRQHandler(void)
{
    camera_flag=1;
    get_slave_data();
}




