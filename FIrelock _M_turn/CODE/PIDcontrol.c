#include "FIRELOCK.h"
#define X_BUCHANG_LIMIT 3000
#define BUCHANG_LIMIT 10000

float fuzzyPID;

uint8 is_fuzzy=2;

int16 SETmotor_kp=3400;
int16 SETmotor_ki=300;
int16 SETmotor_kd=450;

int16 position_zp0=230;//低速p
int16 position_zp1=320;//高速p
int16 position_zi0 = 0;//i
int16 position_zd0=14;// d后两个没用

int16 position_zp0_x=155;//低速p
int16 position_zp1_x=155;//高速p
int16 position_zi0_x = 0;//i
int16 position_zd0_x=0;// d后两个没用

int16 pvlr_d=0,pvlr_p=0;//z差速补偿d，z差速补偿p
float limit_p_out=100,limit_pid_out=100;//p out

#define NB  (-3)
#define NM  (-2)
#define NS  (-1)
#define ZO  (0)
#define PS  (1)
#define PM  (2)
#define PB  (3)
int out_d[5] = {0,1,2,3,4}; //d输出
int out_p[6] = {0,10,20,-15,-35,-55};//p输出
int in_e3[4] = {0,50,100,150};//{0,25,50,75};  //e输入
int in_ec3[4] = {0,25,50,75};  //ec输入
int in_omega[4] = {110,150,250,350};//角速度输入

int p_rule[7][7] =
{
 //  EC -3 -2 -1  0  1  2  3
/*E-3*/  4, 3, 1, 0, 0, 0, 0,
 /*-2*/  4, 4, 2, 0, 0, 0, 0,
 /*-1*/  4, 4, 2, 0, 0, 0, 0,
 /* 0*/  4, 4, 3, 0, 3, 4, 4,
 /* 1*/  0, 0, 0, 0, 2, 4, 4,
 /* 2*/  0, 0, 0, 0, 2, 4, 4,
 /* 3*/  0, 0, 0, 0, 1, 3, 4,
};



float cal_p=0;
float cal_i=0;
float cal_d=0;
float MOTOR_PID(struct MOTORpid* pid,int set_value,int actual_value)
{
    pid->err_2 = pid->err_1;
    pid->err_1 = pid->err;
    pid->err = set_value-actual_value;

    pid->kp = (float)SETmotor_kp*1.0/100;
    pid->ki = (float)SETmotor_ki*1.0/100;
    pid->kd = (float)SETmotor_kd*1.0/100;

    pid->value+=(pid->kp * (pid->err - pid->err_1) + pid->ki *
            pid->err + pid->kd * (pid->err - 2*pid->err_1 + pid->err_2));
    if (pid->value > (float)MOTOR_MAX) pid->value = MOTOR_MAX;
     if (pid->value < (float)MOTOR_MIN) pid->value = MOTOR_MIN;

    return pid->value;
}

float Position_PID(struct Positionpid* pid,int set_value,int actual_value)
{
    float pid_temp;
    int P_pid_p0;
    int       P_pid_p1;
    int           P_pid_i;
    int              P_pid_d;
        //err更新
        pid->err_1 = pid->err;
        pid->err = set_value-actual_value;
        pid->ec = pid->err - pid->err_1;

        /*积分项*/
        if (ALGO_Fabs(pid->err) < 30 && gyro_z < 150)//积分限制
            pid->inter += pid->err;
        if (pid->inter > 200) pid->inter = 200;
        if (pid->inter < -200)pid->inter = -200;

        if(Car_X == DIR_X_NO)
        {
            P_pid_p0=position_zp0;
            P_pid_p1=position_zp1;
            P_pid_i=position_zi0;
            P_pid_d=position_zd0;
        }
        else
        {
            P_pid_p0=position_zp0_x;
            P_pid_p1=position_zp1_x;
            P_pid_i=position_zi0_x;
            P_pid_d=position_zd0_x;

        }
        /*积分项*/
        //得到pid参数值
        if (Track_Line_Num != 3)
        {
            pid->kp = (float)P_pid_p0;//+ FUZZY_P((int)pid->err,(int16)gyro_z);
        }
        else
        {
            pid->kp = (float)P_pid_p1 ;//+ FUZZY_P((int)pid->err,(int16)gyro_z);
        }
        pid->ki = (float)P_pid_i;
//        if (is_fuzzy == 0)
//            pid->kd = (float)position_zd0;
//        else
            pid->kd = (float)P_pid_d+ FUZZY_P((int)pid->err,(int16)gyro_z);


        pid->kp /= 1000;
        pid->ki /= 1000;
        pid->kd /= 1000;

        cal_p = pid->kp * pid->err ;
        cal_d = pid->kd * (-gyro_z);//用陀螺仪的值带入D

        //p限幅
        if (cal_p > limit_p_out) cal_p = limit_p_out;
        if (cal_p < -limit_p_out) cal_p = -limit_p_out;

        pid_temp = cal_p  + cal_d;
        //pid输出限幅

        if (pid_temp > limit_pid_out) pid_temp = limit_pid_out;
        if (pid_temp < -limit_pid_out) pid_temp = -limit_pid_out;

        pid->value = pid_temp;

        return pid->value;
}





float FUZZY_P(int e, int ec)
{
    int el=ZO,er=ZO,ecl=ZO,ecr=ZO;      //左右
    float efl,efr,ecfl,ecfr; //隶属度
    float out = 0;
    //ec 为陀螺仪输入的话 信标灯右移 ec为正
    //e大于0时 cal_p算出顺时针 如果ec也大于0 需要抑制p的作用 同号抑制 异号加强（不变?）
    if (e >= -in_e3[ZO] && e <= in_e3[ZO])//zo
    {
        el = ZO;
        er = ZO;
        efl = efr = 0.5;
    }
    else if (e >= in_e3[ZO] && e <= in_e3[PS])//ZO PS
    {
        el = ZO;
        er = PS;
        efl = (in_e3[PS] - e) *1.0 / (in_e3[PS] - in_e3[ZO]);
        efr = (e - in_e3[ZO]) *1.0 / (in_e3[PS] - in_e3[ZO]);
    }
    else if (e >= in_e3[PS] && e <= in_e3[PM])//PS PM
    {
        el = PS;
        er = PM;
        efl = (in_e3[PM] - e) *1.0 / (in_e3[PM] - in_e3[PS]);
        efr = (e - in_e3[PS]) *1.0 / (in_e3[PM] - in_e3[PS]);
    }
    else if (e >= in_e3[PM] && e <=in_e3[PB])//PM PB
    {
        el = PM;
        er = PB;
        efl = (in_e3[PB] - e) *1.0 / (in_e3[PB] - in_e3[PM]);
        efr = (e - in_e3[PM]) *1.0 / (in_e3[PB] - in_e3[PM]);
    }
    else if (e >= in_e3[PB]) //PB PB
    {
        el = PB;
        er = PB;
        efl = efr = 0.5;
    }
    else if (e <= -in_e3[ZO] && e >= -in_e3[PS])//NS ZO//负 有点变化
    {
        el = NS;
        er = ZO;
        efr = (in_e3[PS] + e) *1.0 / (in_e3[PS] - in_e3[ZO]);
        efl = (-e - in_e3[ZO]) *1.0 / (in_e3[PS] - in_e3[ZO]);
    }
    else if (e <= -in_e3[PS] && e >= -in_e3[PM])//NM NS
    {
        el = NM;
        er = NS;
        efr = (in_e3[PM] + e) *1.0 / (in_e3[PM] - in_e3[PS]);
        efl = (-e - in_e3[PS]) *1.0 / (in_e3[PM] - in_e3[PS]);
    }
    else if (e <= -in_e3[PM] && e >= -in_e3[PB])//NB NM
    {
        el = NB;
        er = NM;
        efr = (in_e3[PB] + e) *1.0 / (in_e3[PB] - in_e3[PM]);
        efl = (-e - in_e3[PM]) *1.0 / (in_e3[PB] - in_e3[PM]);
    }
    else if (e <= -in_e3[PB])
    {
        el = NB;
        er = NB;
        efr = efl = 0.5;
    }

    //ec
    if (ec >= -in_omega[ZO] && ec <= in_omega[ZO])//zo
    {
        ecl = ZO;
        ecr = ZO;
        ecfl = ecfr = 0.5;
    }
    else if (ec >= in_omega[ZO] && ec <= in_omega[PS])//ZO PS
    {
        ecl = ZO;
        ecr = PS;
        ecfl = (in_omega[PS] - ec) *1.0 / (in_omega[PS] - in_omega[ZO]);
        ecfr = (ec - in_omega[ZO]) *1.0 / (in_omega[PS] - in_omega[ZO]);
    }
    else if (ec >= in_omega[PS] && ec <= in_omega[PM])//PS PM
    {
        ecl = PS;
        ecr = PM;
        ecfl = (in_omega[PM] - ec) *1.0 / (in_omega[PM] - in_omega[PS]);
        ecfr = (ec - in_omega[PS]) *1.0 / (in_omega[PM] - in_omega[PS]);
    }
    else if (ec >= in_omega[PM] && ec <=in_omega[PB])//PM PB
    {
        ecl = PM;
        ecr = PB;
        ecfl = (in_omega[PB] - ec) *1.0 / (in_omega[PB] - in_omega[PM]);
        ecfr = (ec - in_omega[PM]) *1.0 / (in_omega[PB] - in_omega[PM]);
    }
    else if (ec >= in_omega[PB]) //PB PB
    {
        ecl = PB;
        ecr = PB;
        ecfl = ecfr = 0.5;
    }
    else if (ec <= -in_omega[ZO] && ec >= -in_omega[PS])//NS ZO//负 有点变化
    {
        ecl = NS;
        ecr = ZO;
        ecfr = (in_omega[PS] + ec) *1.0 / (in_omega[PS] - in_omega[ZO]);
        ecfl = (-ec - in_omega[ZO]) *1.0 / (in_omega[PS] - in_omega[ZO]);
    }
    else if (ec <= -in_omega[PS] && ec >= -in_omega[PM])//NM NS
    {
        ecl = NM;
        ecr = NS;
        ecfr = (in_omega[PM] + ec) *1.0 / (in_omega[PM] - in_omega[PS]);
        ecfl = (-ec - in_omega[PS]) *1.0 / (in_omega[PM] - in_omega[PS]);
    }
    else if (ec <= -in_omega[PM] && ec >= -in_omega[PB])//NB NM
    {
        ecl = NB;
        ecr = NM;
        ecfr = (in_omega[PB] + ec) *1.0 / (in_omega[PB] - in_omega[PM]);
        ecfl = (-ec - in_omega[PM]) *1.0 / (in_omega[PB] - in_omega[PM]);
    }
    else if (ec <= -in_omega[PB])
    {
        ecl = NB;
        ecr = NB;
        ecfr = ecfl = 0.5;
    }

    out = out_d[p_rule[el+3][ecl+3]]*is_fuzzy * efl * ecfl
        + out_d[p_rule[el+3][ecr+3]]*is_fuzzy * efl * ecfr
        + out_d[p_rule[er+3][ecl+3]]*is_fuzzy * efr * ecfl
        + out_d[p_rule[er+3][ecr+3]]*is_fuzzy * efr * ecfr;
    return out;
}





void PID_PositionClear(struct Positionpid* pid)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->err = 0;
    pid->err_1 = 0;
    pid->inter = 0;
    pid->value = 0;
}

void PID_MotorClear(struct MOTORpid *pid)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->err = 0;
    pid->err_1 = 0;
    pid->err_2 = 0;
    pid->value = 0;
}

void PID_TurnClear(struct Turnpid *pid)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->err = 0;
    pid->err_1 = 0;
    pid->err_2 = 0;
    pid->inter = 0;
    pid->value = 0;
}
float ALGO_Fabs(float num)
{
    if (num < 0) return -num;
    return num;
}

int ALGO_Abs(int num)
{
    if (num < 0) return -num;
    return num;
}
