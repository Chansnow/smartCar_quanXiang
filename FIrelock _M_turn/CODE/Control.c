#include "FIRELOCK.h"
#include "math.h"


#define X_BUCHANG_LIMIT 3000
#define BUCHANG_LIMIT 10000
/***模糊PID用值***/
float PMAX,Prange,DMAX,Drange,ERRMAX,ERRrange,IMAX,Irange;

enum car_dir_go Car_Y=DIR_F;
enum car_dir_x Car_X=DIR_X_NO;

int high_icm=200;
int sancha_flag=0;
int sancha_cnt=0;
uint8 EA=1;
/***电机控制***/
struct resolution_v wheels;
struct Positionpid pid_position;
struct Positionpid pid_position_X;  //横跑pid

int set_Speet_D_bc;
int act_Speet_D_bc;
int E_Speet_D_bc;

uint8 last_Foresight[5];
uint8 last_F_flag;

int16 car_dir = 0;

uint8 stop_flag=1;

/***补偿参数***/
int16 minus_l=0;    //前后轮差速
int16 minus_r=0;
int16 act_speed_L=0,act_speed_R=0;

int pwm_buchang=0;  //为满足差速要求补偿占空比
int x_buchang_l=0;
int x_buchang_r=0;
int16 pvfb=15;
float K_centre=0;

/***速度控制***/
int16 HIGH_Speed=260,LOW_speed=215;
int16 H_ALL_Speed=0,L_ALL_speed=0;
int16 def_speed=0;
int16 Set_Speed=160;
int16 GO_Speed=0;
int16 Last_GO_Speed;
int16 Wan_Speed;
uint8 Wam_Speed_flag=0;
int16 Rush_Speed=240;
int16 UP_Speed;
int16 RING_Speed=260;
int16 RING_ru_Speed=190;
int16 X_Speed=160;
int16 Carport_go_Speed=150;
u8 mode_SP=1;

int16 Speed_Limit=650;


uint8 Track_Line_Num;//直道弯道判断
uint8 Last_Track_Line_Num;

uint8 k_curve,k_curve_in=80,k_curve_out=110;

uint8 curue_count,go_count;



int send_up_speed[30];




int16 vx=0,vy=0;
float vz = 0;


/***摄像头参数***/
uint8 camera_flag=0;
uint8  ALL_flag=0;
int e_Foresight;
uint8 e_Foresight_threshold=0;
uint8 ring_e_F=5;

int set_centry_D=0;

int16 inf_flag=0;
int16 start_flag = 0;

int16 count=0;
uint8 icm_flag=0;
uint8 encode_count=0;
int steer_go=0;

uint8 mpu_flag=0;
uint8 xuanzhuan_en=0;


/*************速度解算****************/
void Speed_caculation(struct resolution_v* wheels, int16 vx, int16 vy, float vz)
{
    wheels->vx = vx;
    wheels->vy = vy;
    wheels->vz = vz;
    wheels->v1 = (int16)(wheels->vy - wheels->vx + wheels->vz*(9 + 9)+0.5);
    wheels->v2 = (int16)(wheels->vy + wheels->vx - wheels->vz*(9 + 9)+0.5);
    wheels->v3 = (int16)(wheels->vy - wheels->vx - wheels->vz*(9 + 9)+0.5);
    wheels->v4 = (int16)(wheels->vy + wheels->vx + wheels->vz*(9 + 9)+0.5);
    wheels->vl = (wheels->v2 + wheels->v3)/2;
    wheels->vr = (wheels->v1 + wheels->v4)/2;
}

uint8 last_dir;
uint8 off_control=0;
uint8 add_carport=0;
uint8 EA_NO_F=0;
uint8 EA_NO_B=0;
uint8 sancha_static=0;


void main_control(void)
{
     if(EA==0)                     sancha_cnt++;
     if(sancha_cnt>=50)
     {
         sancha_cnt=0;
         EA=1;
     }

     if(sancha_static<=4)
     {
         if(ALL_flag==10&&EA  && Car_X == DIR_X_NO && Car_Y== DIR_F)//正入
         {
             EA_NO_F=1;
             EA=0;
             pwm_duty(PWM1_CH3_A10,682);
             Speed_caculation(&wheels,0,0,-10);
             systick_delay_ms(150);
              Car_X=DIR_X_GO;
              Car_Y=DIR_F;
              sancha_static++;
         }
         else if(ALL_flag==10&&EA&&  Car_X== DIR_X_GO&&Car_Y==DIR_F)//出，反走
         {
            mpu_flag=1;
         }
         else if(xuanzhuan_en&&EA&&  Car_X== DIR_X_GO&&Car_Y==DIR_F)//出，反走
         {
             xuanzhuan_en=0;
    //         Speed_caculation(&wheels, -Abs(GO_Speed-50), 0, vz);
    //         systick_delay_ms(100);
             EA=0;
    //         pwm_duty(PWM1_CH3_A10,1013);
    //         Speed_caculation(&wheels,0,0,0);//vz
    //         systick_delay_ms(500);
             pwm_duty(PWM1_CH3_A10,311);
             Speed_caculation(&wheels,0,0,vz/5);//vz
             systick_delay_ms(150);
             Speed_caculation(&wheels,0,0,0);//vz
             systick_delay_ms(300);
             Car_X=DIR_X_NO;
             Car_Y=DIR_B;
             sancha_static++;
         }
         else if(ALL_flag==10&&EA&&Car_X==DIR_X_NO&&Car_Y==DIR_B)//反入
         {
             mpu_flag=2;
         }
         else if(xuanzhuan_en&&EA&&Car_X==DIR_X_NO&&Car_Y==DIR_B)//反入
         {
             xuanzhuan_en=0;
             EA_NO_B=1;
             EA=0;

             pwm_duty(PWM1_CH3_A10,682);//反_横走//5500
    //         Speed_caculation(&wheels,0,0,-6);
    //         systick_delay_ms(200);
              Car_X=DIR_X_GO;
              Car_Y=DIR_B;
              EA_NO_B=0;
              sancha_static++;
         }
         else if(ALL_flag==10&&EA&&Car_X == DIR_X_GO&&Car_Y == DIR_B)//出，正走
         {
             Speed_caculation(&wheels, Abs(GO_Speed-50), 0, vz);
             systick_delay_ms(100);
             EA=0;
             pwm_duty(PWM1_CH3_A10,311);
             Speed_caculation(&wheels,vx,0,0);//vz
             systick_delay_ms(250);
             Speed_caculation(&wheels,0,0,0);//vz
             systick_delay_ms(300);
             Car_X=DIR_X_NO;
             Car_Y=DIR_F;
             sancha_static++;
             sancha_static++;
         }
     }
     else if(sancha_static==5)
     {
         if(ALL_flag==10&&EA  && Car_X == DIR_X_NO && Car_Y== DIR_B)//正入
         {
             EA_NO_F=1;
             EA=0;
             pwm_duty(PWM1_CH3_A10,682);
             Speed_caculation(&wheels,0,0,-10);
             systick_delay_ms(150);
              Car_X=DIR_X_GO;
              Car_Y=DIR_B;
         }
         else if(ALL_flag==10&&EA&&  Car_X== DIR_X_GO&&Car_Y==DIR_B)//出，反走
         {
            mpu_flag=1;
         }
         else if(xuanzhuan_en&&EA&&  Car_X== DIR_X_GO&&Car_Y==DIR_B)//出，反走
         {
             xuanzhuan_en=0;
    //         Speed_caculation(&wheels, -Abs(GO_Speed-50), 0, vz);
    //         systick_delay_ms(100);
             EA=0;
    //         pwm_duty(PWM1_CH3_A10,1013);
    //         Speed_caculation(&wheels,0,0,0);//vz
    //         systick_delay_ms(500);
             pwm_duty(PWM1_CH3_A10,311);
             Speed_caculation(&wheels,0,0,vz/5);//vz
             systick_delay_ms(150);
             Speed_caculation(&wheels,0,0,0);//vz
             systick_delay_ms(300);
             Car_X=DIR_X_NO;
             Car_Y=DIR_F;

         }
         else if(ALL_flag==10&&EA&&Car_X==DIR_X_NO&&Car_Y==DIR_F)//反入
         {
             mpu_flag=2;
         }
         else if(xuanzhuan_en&&EA&&Car_X==DIR_X_NO&&Car_Y==DIR_F)//反入
         {
             xuanzhuan_en=0;
             EA_NO_B=1;
             EA=0;

             pwm_duty(PWM1_CH3_A10,682);//反_横走//5500
    //         Speed_caculation(&wheels,0,0,-6);
    //         systick_delay_ms(200);
              Car_X=DIR_X_GO;
              Car_Y=DIR_F;
              EA_NO_B=0;
         }
         else if(ALL_flag==10&&EA&&Car_X == DIR_X_GO&&Car_Y == DIR_F)//出，正走
         {
             Speed_caculation(&wheels, Abs(GO_Speed-50), 0, vz);
             systick_delay_ms(100);
             EA=0;
             pwm_duty(PWM1_CH3_A10,311);
             Speed_caculation(&wheels,vx,0,0);//vz
             systick_delay_ms(250);
             Speed_caculation(&wheels,0,0,0);//vz
             systick_delay_ms(300);
             Car_X=DIR_X_NO;
             Car_Y=DIR_B;
         }
     }

 //   pwm_duty(PWM1_CH3_A10,273+steer_go);
//     Car_X=DIR_X_NO;
//            Car_Y=DIR_B;
//    if(last_dir!=car_dir)
//    {
//        off_control=1;
//    }
//    last_dir=car_dir; //判断和控制车体方向，舵机

    e_Foresight=ALGO_Abs(Foresight-60);
    last_F_flag++;  //记录历史偏移点，用于判断直道和弯道
    if(last_F_flag==2)
    {
        last_F_flag=0;
        last_Foresight[0]=last_Foresight[1];
        last_Foresight[1]=last_Foresight[2];
        last_Foresight[2]=last_Foresight[3];
        last_Foresight[3]=last_Foresight[4];
        last_Foresight[4]=e_Foresight;
    }

    Last_Track_Line_Num=Track_Line_Num;
      if(last_Foresight[0]>15 && last_Foresight[1]>15 && last_Foresight[2]>15 && last_Foresight[4]<15) //弯道入直道
      {
        Track_Line_Num = 4;
      }
      else if(last_Foresight[0]<15 &&last_Foresight[1]<15 && last_Foresight[2]<15 && last_Foresight[4]<=15) //直道
      {
        Track_Line_Num = 1;
      }
      else if(last_Foresight[0]<15 && last_Foresight[1]<15 && last_Foresight[2]<15  && last_Foresight[4]>=15) //直道入弯道
      {
        Track_Line_Num = 2;
      }
      else             //弯道中
      {
        Track_Line_Num=3;
      }
      if(Last_Track_Line_Num!=Track_Line_Num)//改变情况，计数清零
      {
          go_count=0;
          curue_count=0;

      }



    /* 速度控制 */
    /*------------------匀速控制----------------------------*/
    if(mode_SP==0)
    {
        GO_Speed=Set_Speed;
    }
    /*------------------变速控制----------------------------*/
    else
    {
        /*------------------不同模式的速度掌控----------------------------*/
        if (Car_X == DIR_X_GO)                //三叉中
        {
            GO_Speed=X_Speed;
        }
        else
        {
            if( ALL_flag ==242)  //出车库速度
            {
                GO_Speed=Set_Speed;//Carport_go_Speed;
            }
            else if( ALL_flag ==243)  //入车库速度
            {
                GO_Speed=100;
            }
            else if( ALL_flag ==11)  //三叉减速
            {
                GO_Speed=160;
            }
            else if( ALL_flag ==1||ALL_flag ==2)  //入圆环减速
            {
                GO_Speed=RING_ru_Speed;
            }
            else if (ALL_flag ==3 || ALL_flag ==4)  //圆环中
            {
                GO_Speed=RING_Speed;
            }
            else if( ALL_flag ==31)  //坡道速度
            {
                GO_Speed=Rush_Speed;
            }
            else
            {
                add_carport=0;
                H_ALL_Speed=HIGH_Speed;
                L_ALL_speed=LOW_speed;
                /*---------------------直道弯道变速控制-------------------------------*/
                       if(Track_Line_Num == 1) //直道
                       {
                           GO_Speed+=5;
                           Wam_Speed_flag=0;

                       }
                       else if(Track_Line_Num == 2) //直道入弯道
                       {
                           Wam_Speed_flag=1;
                           if(GO_Speed>=H_ALL_Speed-10)
                          {
                               Wan_Speed=L_ALL_speed-(int16)((k_curve_out/10)*e_Foresight);
                          }
//                          if(GO_Speed>=H_ALL_Speed-40)
//                          {
//                             GO_Speed=L_ALL_speed-(int16)((k_curve/10)*e_Foresight);
//                          }
                          else
                          {
                              Wan_Speed=L_ALL_speed-(int16)((k_curve_in/10)*e_Foresight);
                          }
                           GO_Speed=Wan_Speed;
                       }
                       else //弯道
                       {
                          // GO_Speed=L_ALL_speed+(int16)((k_curve/10)*(60-e_Foresight));

//                           if (e_Foresight >= 30)        //34
//                             {
                               GO_Speed = L_ALL_speed;
//                             }
//                             else if (e_Foresight >= 27)    //31
//                             {
//                               GO_Speed = L_ALL_speed+1;
//                             }
//                             else if (e_Foresight >= 24)       //28
//                             {
//                               GO_Speed = L_ALL_speed+2;
//                             }
//                             else if (e_Foresight >= 21)     //25
//                             {
//                                 GO_Speed = L_ALL_speed+3;
//                             }
//                             else if (e_Foresight >= 18)       //22
//                             {
//                                 GO_Speed = L_ALL_speed+4;
//                             }
//                             else if (e_Foresight >= 15)       //19
//                             {
//                                 GO_Speed = L_ALL_speed+5;
//                             }
//                             else if (e_Foresight >= 12)        //16
//                             {
//                                 GO_Speed = L_ALL_speed+6;
//                             }
//                             else
//                             {
//                                 GO_Speed +=1;  //2
//                             }
                       }


                       if(GO_Speed>H_ALL_Speed)
                          {
                              GO_Speed=H_ALL_Speed;
                          }
                       if(Wam_Speed_flag==1&&Wan_Speed<GO_Speed)
                       {
                           GO_Speed=Wan_Speed+1;
                           Wan_Speed=Wan_Speed+1;

                       }
                       else if(Wam_Speed_flag==1&&Wan_Speed>=GO_Speed)
                       {
                           Wam_Speed_flag=0;
                           Wan_Speed=0;
                       }

                   }

              Last_GO_Speed=GO_Speed;
          }
      }




//
//            if(vy>HIGH_Speed)Set_Speed=HIGH_Speed;
//            if(vy<LOW_speed)Set_Speed=LOW_speed;


//    if(e_Foresight>e_Foresight_threshold && gyro_z>high_icm && ALL_flag==0)
//    {
//
//        set_centry_D=(int) (e_Foresight*K_centre/10+0.5);
//
//        if(set_centry_D>10) set_centry_D=10;
//        if(Foresight>60) set_centry_D= -set_centry_D;
//    }
//    else if(ALL_flag==3)
//    {
//        set_centry_D=ring_e_F;
//    }
//    else if(ALL_flag==4)
//    {
//       set_centry_D=-ring_e_F;
//    }
//    else
//    {
//        set_centry_D=0;
//    }

    if(mpu_flag==0&&Car_X==DIR_X_GO)
    {
        vz = Position_PID(&pid_position_X, 60, Foresight);
        vx=-GO_Speed;
        vy=0;
    }
    else if(mpu_flag==0&&Car_X==DIR_X_NO)
    {
        vz = Position_PID(&pid_position, 60, Foresight);
        vx=0;
        vy=GO_Speed;
    }
    if(mpu_flag==1)
    {
        vx=0;
        vy=0;
        vz=10;
    }
    if(mpu_flag==2)
    {
        vx=0;
        vy=0;
        vz=-10;
    }


    //冲出赛道停车
    if(ALL_flag == 241)
        {
            while(1)
            {
                Speed_caculation(&wheels,0,0,0);
            }
        }
    else
        Speed_caculation(&wheels,vx,vy,vz);//vxsteer_govz


//
//    set_Speet_D_bc=wheels.vr - wheels.vl;
//    act_Speet_D_bc=act_speed_R - act_speed_L;
//    E_Speet_D_bc=set_Speet_D_bc-act_Speet_D_bc;
//    if(E_Speet_D_bc>30||E_Speet_D_bc<-30)
//    {
//        pwm_buchang = (int)(pvlr_p/100*E_Speet_D_bc);
//        if (pwm_buchang > BUCHANG_LIMIT)pwm_buchang = BUCHANG_LIMIT;
//        if (pwm_buchang < -BUCHANG_LIMIT)pwm_buchang = -BUCHANG_LIMIT;
//
//    }
//    else  pwm_buchang=0;

}


void CTRL_PwmCompensateCal(int set_S_bc,int act_S_bc)
{
//    x_buchang_l = minus_l * pvfb;
//    x_buchang_r = minus_r * pvfb;
//    if (x_buchang_l > X_BUCHANG_LIMIT) x_buchang_l = X_BUCHANG_LIMIT;
//    if (x_buchang_l < -X_BUCHANG_LIMIT) x_buchang_l = -X_BUCHANG_LIMIT;
//    if (x_buchang_r > X_BUCHANG_LIMIT) x_buchang_r = X_BUCHANG_LIMIT;
//    if (x_buchang_r < -X_BUCHANG_LIMIT) x_buchang_r = -X_BUCHANG_LIMIT;


}
void CTRL_PwmCompensateClear()
{
//
//        x_buchang_l=0;
//        x_buchang_r=0;
        pwm_buchang=0;
}


