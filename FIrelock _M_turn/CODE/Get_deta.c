#include "FIRELOCK.h"

#define LINE_LEN                11      //数据长度
uint8   temp_buff[LINE_LEN];            //主机用于接收数据的BUFF
uint8  uart_flag;                      //接收数据标志位

/*************读取用值*******************/
uint8 camera_buffer[10];
uint8 camera_data_cnt=0;
uint8 camera_head_cnt=0;
uint8 camera_tail_cnt=0;
#define CAMERA_HEAD1    0xd8
#define CAMERA_HEAD2    0xb0
#define CAMERA_TAIL1    0xee


uint8 show_flag;                        //数据显示标志位


/*************所取出的数据*******************/
uint8 Foresight=0;







//获取数据
void get_slave_data()
{
    uint8 camera_temp;
      camera_flag = 0;

            uart_getchar(UART_2, &camera_temp);
            if (camera_head_cnt == 0)//刚开始检测，检测第一个帧头
            {
                camera_data_cnt = camera_tail_cnt = 0;
                if (camera_temp == CAMERA_HEAD1)//是第一个帧头
                {
                    camera_head_cnt++;
                }
                else    //检测错误，从头开始
                {
                    camera_head_cnt=0;
                }
            }
            else if (camera_head_cnt == 1)//检测到第一个帧头，检测第二个
            {
                camera_data_cnt = camera_tail_cnt = 0;
                if (camera_temp == CAMERA_HEAD2)//是第二个帧头
                {
                    camera_head_cnt++;
                }
                else if (camera_temp == CAMERA_HEAD1) //又是第一个帧头，
                {
                    camera_head_cnt=1;//检测到第一个帧头，head——cnt不变
                }
                else    //检测错误，从头开始
                {
                    camera_head_cnt=0;
                }
            }
            else if (camera_head_cnt == 2)//两个帧头检测到，检测数据。
            {
                if (camera_data_cnt != 2)      /////!!!!!!!没检测完一个数据!!!!!!!/////////
                {
                    camera_buffer[camera_data_cnt] = camera_temp;


                    camera_data_cnt++;
                }
                else//检测完一个数据，检测帧尾
                {
                    if (camera_temp == CAMERA_TAIL1)//检测成功，坐标更新。
                    {
//                        Foresight = camera_buffer[1];       //合成
//                        Foresight <<= 8;
//                        Foresight |= camera_buffer[0];
                        Foresight = camera_buffer[0];
                        ALL_flag = camera_buffer[1];



                        camera_head_cnt = 0;
                    }
                    else if (camera_temp == CAMERA_HEAD1)
                    {
                        camera_head_cnt = 1;//检测到第一个帧头
                    }
                    else
                    {
                        camera_head_cnt = 0;//检测第一个帧头
                    }
                }
            }



}







////-------------------------------------------------------------------------------------------------------------------
////  @brief      获取从机数据
////  @param      data            串口数据
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void get_slave_data(uint8 data)
//{
//    static uint8 uart_num = 0;
//    temp_buff[uart_num++] = data;
//
//    if(1 == uart_num)
//    {
//        //接收到的第一个字符不为0xD8，帧头错误
//        if(0xD8 != temp_buff[0])
//        {
//            uart_num = 0;
//            uart_flag = E_FRAME_HEADER_ERROR;
//        }
//    }
//
//    if(LINE_LEN == uart_num)
//    {
//        uart_flag = E_OK;
//        //接收到最后一个字节为0xEE
//        if(0xEE == temp_buff[LINE_LEN - 1])
//        {
//            uart_flag = E_OK;
//        }
//        else    //接收到最后一个字节不是0xEE，帧尾错误
//        {
//            uart_flag = E_FRAME_RTAIL_ERROR;
//        }
//        uart_num = 0;
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      根据协议对从机发送过来的数据，进行数据解析
////  @param      *line                           串口接收到的数据BUFF
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void data_analysis(uint8 *line)
//{
//    if(line[1] == 0xB0)    slave_a  = ((int16)line[2] << 8) | line[3];
//    if(line[4] == 0xB1)    slave_b = ((int16)line[5] << 8) | line[6];
//    if(line[7] == 0xB2)    slave_c      = ((int16)line[8] << 8) | line[9];
//}
