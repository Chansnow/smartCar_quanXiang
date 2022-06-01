#include "FIRELOCK.h"


uint8 Skey_flag;
int16 run_mode=2;



void Init_ALL()
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    systick_delay_ms(300);
    key_init(KEY_MAX);
    oled_init();
    gpio_init(C0, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C2, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C10, GPO, 0, GPIO_PIN_CONFIG);
    simiic_init();
    mpu6050_init();

  //  seekfree_wireless_init();

    encoder_init_spi(ABS_ENCODER_SPI_PC1_PIN);      //编码器1初始化。
    encoder_init_spi(ABS_ENCODER_SPI_PC2_PIN);      //编码器2初始化。
    encoder_init_spi(ABS_ENCODER_SPI_PC3_PIN);      //编码器3初始化。
    encoder_init_spi(ABS_ENCODER_SPI_PC4_PIN);      //编码器4初始化。
    pwm_init(PWM2_CH2_B3,  18000, 0);      //RB  前
    pwm_init(PWM2_CH1_A15, 18000, 0);      //RB  后
    pwm_init(PWM2_CH3_B10, 18000, 0);      //LB  前
    pwm_init(PWM2_CH4_B11, 18000, 0);     //LB  后
    pwm_init(PWM4_CH2_B7,  18000, 0);     //RF  前
    pwm_init(PWM4_CH1_B6,  18000, 0);     //RF  后
    pwm_init(PWM4_CH4_B9,  18000, 0);     //LF  前
    pwm_init(PWM4_CH3_B8,  18000, 0);     //LF  后
    pwm_init(PWM1_CH3_A10, 50,   0); //舵机


    timer_pit_interrupt_ms(TIMER_3, 7);

    pwm_duty(PWM1_CH3_A10,311);
    Car_X= DIR_X_NO;
    Car_Y=DIR_F;

   FLASH_ReadALL();

    uart_init(UART_2, 460800, UART2_TX_A2, UART2_RX_A3);  //串口2初始化，波特率460800
    uart_rx_irq(UART_2, ENABLE);                            //默认抢占优先级0 次优先级0。
    EnableGlobalIRQ(0);

}


void running(void)
{
    Menu_player();
    //Menu_Main();
    IcmGetData();
  if(Skey_flag)
  {
      main_control();                                            //主控
  }
  else if(cwheels == 0)
  {
     Speed_caculation(&wheels,0,0,0);
  }
}


void ccwheels()//洗车轮
{
//  if(cwheels==1)
//  {
//    wheels.v3 = 0;
//    wheels.v1 = 0;
//    wheels.v2 = 150;
//    wheels.v4 = 0;
//
//  }
//  if(cwheels==2)
//  {
//    wheels.v3 = 0;
//    wheels.v1 = 0;
//    wheels.v2 = -150;
//    wheels.v4 = 0;
//
//  }
//  else if(cwheels==3)
//  {
//    wheels.v4 = 0;
//    wheels.v1 = 150;
//    wheels.v2 = 0;
//    wheels.v3 = 0;
//  }
//  else if(cwheels==4)
//  {
//    wheels.v4 = 0;
//    wheels.v1 = -150;
//    wheels.v2 = 0;
//    wheels.v3 = 0;
//  }
//  else if(cwheels==5)
//  {
//    wheels.v1 = 0;
//    wheels.v4 = 0;
//    wheels.v2 = 0;
//    wheels.v3 = 150;
//  }
//  else if(cwheels==6)
//  {
//    wheels.v1 = 0;
//    wheels.v4 = 0;
//    wheels.v2 = 0;
//    wheels.v3 = -150;
//  }
//  else if(cwheels==7)
//  {
//    wheels.v2 = 0;
//    wheels.v1 = 0;
//    wheels.v3 = 0;
//    wheels.v4 = 150;
//  }
//  else if(cwheels==8)
//  {
//    wheels.v2 = 0;
//    wheels.v1 = 0;
//    wheels.v3 = 0;
//    wheels.v4 = -150;
//  }
   if(cwheels==9)
  {
    wheels.v2 = 100;
    wheels.v1 = 100;
    wheels.v3 = 100;
    wheels.v4 = 100;
  }
  else if(cwheels==10)
  {
    wheels.v2 = -100;
    wheels.v1 = -100;
    wheels.v3 = -100;
    wheels.v4 = -100;
  }
  else if(cwheels==0)
  {
    wheels.v4 = 0;
    wheels.v1 = 0;
    wheels.v2 = 0;
    wheels.v3 = 0;
  }
//  else if(cwheels==11)
//  {//vx,vy,vz
//    Speed_caculation(&wheels,20,20,0);
//  }
}












