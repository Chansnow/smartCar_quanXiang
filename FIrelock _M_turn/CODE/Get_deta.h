/*
 * Ger_data.h
 *
 *  Created on: 2021年2月28日
 *      Author: plute
 */

#ifndef CODE_GET_DETA_H_
#define CODE_GET_DETA_H_

#define E_START                 0       //准备状态
#define E_OK                    1       //成功
#define E_FRAME_HEADER_ERROR    2       //帧头错误
#define E_FRAME_RTAIL_ERROR     3       //帧尾错误

extern uint8 show_flag;
extern int16 slave_a;
extern int16 slave_b;
extern int16 slave_c;

//void get_slave_data(uint8 data);
//void data_analysis(uint8 *line);
void get_slave_data(void);


#endif /* CODE_GET_DETA_H_ */
