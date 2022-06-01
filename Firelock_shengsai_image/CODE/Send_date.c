

#include "FIRELOCK.h"

#define LINE_LEN                5            //数据长度11
uint8 temp_buff[LINE_LEN];                      //从机向主机发送数据BUFF


void process_data(void)
{
    temp_buff[0]=0Xd8;  //帧头
    temp_buff[1]=0Xb0;  //功能字
    temp_buff[2]=Foresight; //低8位

    temp_buff[3]=ALL_flag;


    temp_buff[4]=0Xee;  //帧尾

}
void upper_send_data(int *upper_buf_data, int send_len)   //向上位机发送数据
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

    for(upper_i=0 ; upper_i <send_len ; upper_i++)  //小数据模式，低字节在前
    {
       upper_data_buff[_cnt++]= upper_buf_data[upper_i] & 0xFF;  //低八位
       upper_data_buff[_cnt++]= upper_buf_data[upper_i] >>8 ;  //高八位
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
    GPIO_PIN_SET(A0);                           //A0引脚拉高

    uart_send(UART_3,temp_buff,LINE_LEN);

    GPIO_PIN_RESET(A0);                         //A0引脚拉低
}

void init_send_deta()
{
    gpio_init(A0, GPO, 0, GPIO_PIN_CONFIG);                 //同步引脚初始化
    uart_init(UART_3, 460800, UART3_TX_B10, UART3_RX_B11);  //串口3初始化，波特率460800
}


