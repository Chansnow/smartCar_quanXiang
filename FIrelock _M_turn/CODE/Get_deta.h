/*
 * Ger_data.h
 *
 *  Created on: 2021��2��28��
 *      Author: plute
 */

#ifndef CODE_GET_DETA_H_
#define CODE_GET_DETA_H_

#define E_START                 0       //׼��״̬
#define E_OK                    1       //�ɹ�
#define E_FRAME_HEADER_ERROR    2       //֡ͷ����
#define E_FRAME_RTAIL_ERROR     3       //֡β����

extern uint8 show_flag;
extern int16 slave_a;
extern int16 slave_b;
extern int16 slave_c;

//void get_slave_data(uint8 data);
//void data_analysis(uint8 *line);
void get_slave_data(void);


#endif /* CODE_GET_DETA_H_ */
