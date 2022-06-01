#include "FIRELOCK.h"

#define LINE_LEN                11      //���ݳ���
uint8   temp_buff[LINE_LEN];            //�������ڽ������ݵ�BUFF
uint8  uart_flag;                      //�������ݱ�־λ

/*************��ȡ��ֵ*******************/
uint8 camera_buffer[10];
uint8 camera_data_cnt=0;
uint8 camera_head_cnt=0;
uint8 camera_tail_cnt=0;
#define CAMERA_HEAD1    0xd8
#define CAMERA_HEAD2    0xb0
#define CAMERA_TAIL1    0xee


uint8 show_flag;                        //������ʾ��־λ


/*************��ȡ��������*******************/
uint8 Foresight=0;







//��ȡ����
void get_slave_data()
{
    uint8 camera_temp;
      camera_flag = 0;

            uart_getchar(UART_2, &camera_temp);
            if (camera_head_cnt == 0)//�տ�ʼ��⣬����һ��֡ͷ
            {
                camera_data_cnt = camera_tail_cnt = 0;
                if (camera_temp == CAMERA_HEAD1)//�ǵ�һ��֡ͷ
                {
                    camera_head_cnt++;
                }
                else    //�����󣬴�ͷ��ʼ
                {
                    camera_head_cnt=0;
                }
            }
            else if (camera_head_cnt == 1)//��⵽��һ��֡ͷ�����ڶ���
            {
                camera_data_cnt = camera_tail_cnt = 0;
                if (camera_temp == CAMERA_HEAD2)//�ǵڶ���֡ͷ
                {
                    camera_head_cnt++;
                }
                else if (camera_temp == CAMERA_HEAD1) //���ǵ�һ��֡ͷ��
                {
                    camera_head_cnt=1;//��⵽��һ��֡ͷ��head����cnt����
                }
                else    //�����󣬴�ͷ��ʼ
                {
                    camera_head_cnt=0;
                }
            }
            else if (camera_head_cnt == 2)//����֡ͷ��⵽��������ݡ�
            {
                if (camera_data_cnt != 2)      /////!!!!!!!û�����һ������!!!!!!!/////////
                {
                    camera_buffer[camera_data_cnt] = camera_temp;


                    camera_data_cnt++;
                }
                else//�����һ�����ݣ����֡β
                {
                    if (camera_temp == CAMERA_TAIL1)//���ɹ���������¡�
                    {
//                        Foresight = camera_buffer[1];       //�ϳ�
//                        Foresight <<= 8;
//                        Foresight |= camera_buffer[0];
                        Foresight = camera_buffer[0];
                        ALL_flag = camera_buffer[1];



                        camera_head_cnt = 0;
                    }
                    else if (camera_temp == CAMERA_HEAD1)
                    {
                        camera_head_cnt = 1;//��⵽��һ��֡ͷ
                    }
                    else
                    {
                        camera_head_cnt = 0;//����һ��֡ͷ
                    }
                }
            }



}







////-------------------------------------------------------------------------------------------------------------------
////  @brief      ��ȡ�ӻ�����
////  @param      data            ��������
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
//        //���յ��ĵ�һ���ַ���Ϊ0xD8��֡ͷ����
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
//        //���յ����һ���ֽ�Ϊ0xEE
//        if(0xEE == temp_buff[LINE_LEN - 1])
//        {
//            uart_flag = E_OK;
//        }
//        else    //���յ����һ���ֽڲ���0xEE��֡β����
//        {
//            uart_flag = E_FRAME_RTAIL_ERROR;
//        }
//        uart_num = 0;
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      ����Э��Դӻ����͹��������ݣ��������ݽ���
////  @param      *line                           ���ڽ��յ�������BUFF
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
