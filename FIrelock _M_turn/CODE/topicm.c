#include "FIRELOCK.h"

float gyro_z=0,gyro_c=0;
int16 gyro_kalman_q=80;
int16 gyro_kalman_r=320;
int16 mpu_set=1;
int16 mpu_offset=-37;


void IcmGetData(void)
{
   icm_flag=0;
   mpu6050_get_gyro();
   gyro_z=mpu_gyro_z+mpu_offset;//������ƫ���ʼֵ��ÿ����һ�������Ƕ�Ҫ����
   gyro_z=((gyro_z)/16.38);
   gyro_z = KalmanFilter(gyro_z,gyro_kalman_q*1.0/1000,gyro_kalman_r*1.0/1000);
}

#define KALMAN_Q 0.08   //��������0.01  0.01
#define KALMAN_R 0.32   //��������0.5   0.3

float KalmanFilter(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{

    float R = MeasureNoise_R;
    float Q = ProcessNiose_Q;

    static float x_last;
    float x_mid = x_last;
    float x_now;

    static float p_last;
    float p_mid ;
    float p_now;

    float kg;

    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����

    /*
     *  �������˲��������Ҫ��ʽ
     */
    kg=p_mid/(p_mid+R);                 //kgΪkalman filter��R Ϊ����
    x_now= (1-kg) * x_mid+kg * ResrcData;   //���Ƴ�������ֵ
    p_now= (1-kg) * p_mid;                 //����ֵ��Ӧ��covariance
    p_last = p_now;                     //����covariance ֵ
    x_last = x_now;                     //����ϵͳ״ֵ̬

    return x_now;

}


