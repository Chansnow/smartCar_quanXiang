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
   gyro_z=mpu_gyro_z+mpu_offset;//陀螺仪偏差初始值，每更换一颗陀螺仪都要更改
   gyro_z=((gyro_z)/16.38);
   gyro_z = KalmanFilter(gyro_z,gyro_kalman_q*1.0/1000,gyro_kalman_r*1.0/1000);
}

#define KALMAN_Q 0.08   //过程噪声0.01  0.01
#define KALMAN_R 0.32   //测量噪声0.5   0.3

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
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声

    /*
     *  卡尔曼滤波的五个重要公式
     */
    kg=p_mid/(p_mid+R);                 //kg为kalman filter，R 为噪声
    x_now= (1-kg) * x_mid+kg * ResrcData;   //估计出的最优值
    p_now= (1-kg) * p_mid;                 //最优值对应的covariance
    p_last = p_now;                     //更新covariance 值
    x_last = x_now;                     //更新系统状态值

    return x_now;

}


