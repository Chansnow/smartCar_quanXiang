#include "FIRELOCK.h"

extern uint8 sancha_static;

void Init_ALL()
{
    DisableGlobalIRQ();
    board_init();           //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    systick_delay_ms(300);  //��ʱ300ms���ȴ��������������ϵ�ɹ�


        //����ת����ģ��������Ŷ����� wireless.h�ļ���
    seekfree_wireless_init();

    gpio_init(A6, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C5, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(C10, GPO, 0, GPIO_PIN_CONFIG);
//    gpio_init(A15, GPO, 1, GPIO_PIN_CONFIG);

    key_init(KEY_MAX);
    init_send_deta();
    oled_init();    //oled��ʼ��
    mt9v03x_init();              //����ͷ��ʼ��

    timer_pit_interrupt_ms(TIMER_2, 1000);
    timer_pit_interrupt_ms(TIMER_3, 20);
    start_flag=0; //���ܱ�־λ����
  //  uart_rx_irq(UART_1, ENABLE);

    EnableGlobalIRQ(0);

//    start_flag=2;
//    sancha_static=4;
}
