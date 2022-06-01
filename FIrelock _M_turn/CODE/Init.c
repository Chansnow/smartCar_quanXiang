#include "FIRELOCK.h"


uint8 Skey_flag;
int16 run_mode=2;



void Init_ALL()
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    systick_delay_ms(300);
    key_init(KEY_MAX);
    oled_init();
    gpio_init(C0, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C2, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C10, GPO, 0, GPIO_PIN_CONFIG);
    simiic_init();
    mpu6050_init();

  //  seekfree_wireless_init();

    encoder_init_spi(ABS_ENCODER_SPI_PC1_PIN);      //������1��ʼ����
    encoder_init_spi(ABS_ENCODER_SPI_PC2_PIN);      //������2��ʼ����
    encoder_init_spi(ABS_ENCODER_SPI_PC3_PIN);      //������3��ʼ����
    encoder_init_spi(ABS_ENCODER_SPI_PC4_PIN);      //������4��ʼ����
    pwm_init(PWM2_CH2_B3,  18000, 0);      //RB  ǰ
    pwm_init(PWM2_CH1_A15, 18000, 0);      //RB  ��
    pwm_init(PWM2_CH3_B10, 18000, 0);      //LB  ǰ
    pwm_init(PWM2_CH4_B11, 18000, 0);     //LB  ��
    pwm_init(PWM4_CH2_B7,  18000, 0);     //RF  ǰ
    pwm_init(PWM4_CH1_B6,  18000, 0);     //RF  ��
    pwm_init(PWM4_CH4_B9,  18000, 0);     //LF  ǰ
    pwm_init(PWM4_CH3_B8,  18000, 0);     //LF  ��
    pwm_init(PWM1_CH3_A10, 50,   0); //���


    timer_pit_interrupt_ms(TIMER_3, 7);

    pwm_duty(PWM1_CH3_A10,311);
    Car_X= DIR_X_NO;
    Car_Y=DIR_F;

   FLASH_ReadALL();

    uart_init(UART_2, 460800, UART2_TX_A2, UART2_RX_A3);  //����2��ʼ����������460800
    uart_rx_irq(UART_2, ENABLE);                            //Ĭ����ռ���ȼ�0 �����ȼ�0��
    EnableGlobalIRQ(0);

}


void running(void)
{
    Menu_player();
    //Menu_Main();
    IcmGetData();
  if(Skey_flag)
  {
      main_control();                                            //����
  }
  else if(cwheels == 0)
  {
     Speed_caculation(&wheels,0,0,0);
  }
}


void ccwheels()//ϴ����
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












