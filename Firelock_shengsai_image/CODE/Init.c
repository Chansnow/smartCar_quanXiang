#include "FIRELOCK.h"

extern uint8 sancha_static;

void Init_ALL()
{
    DisableGlobalIRQ();
    board_init();           //务必保留，本函数用于初始化MPU 时钟 调试串口

    systick_delay_ms(300);  //延时300ms，等待主板其他外设上电成功


        //无线转串口模块相关引脚定义在 wireless.h文件中
    seekfree_wireless_init();

    gpio_init(A6, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C5, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C10, GPO, 0, GPIO_PIN_CONFIG);
//    gpio_init(A15, GPO, 1, GPIO_PIN_CONFIG);

    key_init(KEY_MAX);
    init_send_deta();
    oled_init();    //oled初始化
    mt9v03x_init();              //摄像头初始化

    timer_pit_interrupt_ms(TIMER_2, 1000);
    timer_pit_interrupt_ms(TIMER_3, 20);
    start_flag=0; //起跑标志位清零
  //  uart_rx_irq(UART_1, ENABLE);

    EnableGlobalIRQ(0);

//    start_flag=2;
//    sancha_static=4;
}
