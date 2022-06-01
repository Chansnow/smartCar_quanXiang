/*
 * encode.h
 *
 *  Created on: 2021年3月11日
 *      Author: csn
 */

#ifndef CODE_ENCODE_H_
#define CODE_ENCODE_H_

void encode(void);
void encode_calculation(void);

#define WHEEL_C         192             //车轮周长192mm
#define WHEEL_PULSE    (512*104/50)     //车轮转动一周脉冲数（104车轮齿轮数，50编码器齿轮数）


#endif /* CODE_ENCODE_H_ */
