/*
 * topicm.h
 *
 *  Created on: 2021��4��1��
 *      Author: csn
 */

#ifndef CODE_TOPICM_H_
#define CODE_TOPICM_H_


void  IcmGetData(void);
float KalmanFilter(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);



#endif /* CODE_TOPICM_H_ */
