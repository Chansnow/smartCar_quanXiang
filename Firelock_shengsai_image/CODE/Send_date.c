

#include "FIRELOCK.h"

#define LINE_LEN                5            //���ݳ���11
uint8 temp_buff[LINE_LEN];                      //�ӻ���������������BUFF


void process_data(void)
{
    temp_buff[0]=0Xd8;  //֡ͷ
    temp_buff[1]=0Xb0;  //������
    temp_buff[2]=Foresight; //��8λ

    temp_buff[3]=ALL_flag;


    temp_buff[4]=0Xee;  //֡β

}
void upper_send_data(int *upper_buf_data, int send_len)   //����λ����������
{
    u8 upper_data_buff[20]={0};
    u8 _cnt=0;
    u8 sumcheck = 0;
    u8 addcheck = 0;
    u8 upper_i=0;
    upper_data_buff[_cnt++] = 0xAA;
    upper_data_buff[_cnt++] = 0xFF;
    upper_data_buff[_cnt++] = 0xF1;
    upper_data_buff[_cnt++] = send_len+send_len;

    for(upper_i=0 ; upper_i <send_len ; upper_i++)  //С����ģʽ�����ֽ���ǰ
    {
       upper_data_buff[_cnt++]= upper_buf_data[upper_i] & 0xFF;  //�Ͱ�λ
       upper_data_buff[_cnt++]= upper_buf_data[upper_i] >>8 ;  //�߰�λ
    }
    for(uint8 i =0;i<(upper_data_buff[3]+4);i++){
       sumcheck += upper_data_buff[i];
       addcheck += sumcheck;
    }
    upper_data_buff[_cnt++] = sumcheck;
    upper_data_buff[_cnt++] = addcheck;
    seekfree_wireless_send_buff(&upper_data_buff[0],_cnt);

}

void send_date()
{
    GPIO_PIN_SET(A0);                           //A0��������

    uart_send(UART_3,temp_buff,LINE_LEN);

    GPIO_PIN_RESET(A0);                         //A0��������
}

void init_send_deta()
{
    gpio_init(A0, GPO, 0, GPIO_PIN_CONFIG);                 //ͬ�����ų�ʼ��
    uart_init(UART_3, 460800, UART3_TX_B10, UART3_RX_B11);  //����3��ʼ����������460800
}


