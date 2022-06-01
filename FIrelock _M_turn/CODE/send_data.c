

#include "FIRELOCK.h"


#define LINE_LEN               11             //���ݳ���
uint8 temp_buff[LINE_LEN];

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
void send_data(int *buf_data)   //����λ����������
{
   temp_buff[0] = 0xD8;                         //֡ͷ
   temp_buff[1] = 0xB0;                         //������
   temp_buff[2] = buf_data[0]>>8;        //���ݸ�8λ
   temp_buff[3] = buf_data[0]&0xFF;      //���ݵ�8λ

   temp_buff[4] = 0xB1;                         //������
   temp_buff[5] = buf_data[1]>>8;       //���ݸ�8λ
   temp_buff[6] = buf_data[1]&0xFF;     //���ݵ�8λ

   temp_buff[7] = 0xB2;                         //������
   temp_buff[8] = buf_data[2]>>8;            //���ݸ�8λ
   temp_buff[9] = buf_data[2]&0xFF;          //���ݵ�8λ

   temp_buff[10] = 0xEE;                        //֡β



   uart_putbuff(UART_2, temp_buff, 11);  //ͨ������2�����ݷ��ͳ�ȥ��

}


//
//void upper_send_check(u8 data_ID,u8 data_sumcheck,u8 data_addcheck) //��������У��֡
//{
//    u8 upper_i=0;
//    u8 sumcheck = 0;
//    u8 addcheck = 0;
//    upper_send_check_buf[0]=0xAA;//0~3Ϊ�̶���ʽ
//    upper_send_check_buf[1]=0xFF;
//    upper_send_check_buf[2]=0x00;
//    upper_send_check_buf[3]=0x03;
//
//    upper_send_check_buf[4]=data_ID;
//    upper_send_check_buf[5]=data_sumcheck;
//    upper_send_check_buf[6]=data_addcheck;
//
//    for(upper_i=0; upper_i < 7; upper_i++)
//    {
//        sumcheck += upper_send_check_buf[upper_i];
//        addcheck += sumcheck;
//    }
//    seekfree_wireless_send_buff(upper_send_check_buf, 9);
//}



//void data_check()           //�����λ�����ص�֡
//{
//    uint8 upper_temp;
//
//    uart_getchar(UART_1, &upper_temp);
//    if (upper_head_cnt == 0)//�տ�ʼ��⣬����һ��֡ͷ
//    {
//        upper_data_cnt = upper_tail_cnt = 0;
//        if (upper_temp == UPPER_HEAD1)//�ǵ�һ��֡ͷ
//        {
//            upper_head_cnt++;
//        }
//        else    //�����󣬴�ͷ��ʼ
//        {
//            upper_head_cnt=0;
//        }
//    }
//    else if (upper_head_cnt == 1)//��⵽��һ��֡ͷ�����ڶ���
//    {
//        upper_data_cnt = upper_tail_cnt = 0;
//        if (upper_temp == UPPER_HEAD2)//�ǵڶ���֡ͷ
//        {
//            upper_head_cnt++;
//        }
//        else if (upper_temp == UPPER_HEAD1) //���ǵ�һ��֡ͷ��
//        {
//            upper_head_cnt=1;//��⵽��һ��֡ͷ��head����cnt����
//        }
//        else    //�����󣬴�ͷ��ʼ
//        {
//            upper_head_cnt=0;
//        }
//    }
//    else if (upper_head_cnt == 2)//����֡ͷ��⵽����������
//    {
//        upper_data_cnt = upper_tail_cnt = 0;
//        if (upper_temp == UPPER_HEAD3)//�ǵڶ���֡ͷ
//        {
//            upper_head_cnt++;
//        }
//        else    //�����󣬴�ͷ��ʼ
//        {
//            upper_head_cnt=0;
//        }
//    }
//    else if (upper_head_cnt == 3)
//    {
//        if (upper_data_cnt != 4)
//        {
//            upper_get_buf[upper_data_cnt] = upper_temp;
//            upper_data_cnt++;
//        }
//        else
//        {
//
//            upper_check_flag=1;
//            upper_head_cnt = 0;
//
//        }
//    }
//}






