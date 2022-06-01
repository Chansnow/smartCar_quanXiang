

#ifndef CODE_CONTROL_H_
#define CODE_CONTROL_H_

#include "FIRELOCK.h"


enum car_dir_go
{
    DIR_F,
    DIR_B,
};

enum car_dir_x
{
    DIR_X_NO,
    DIR_X_GO,
};


#define Abs(a)               ((a)<(0)?(-a):(a))

struct resolution_v
{
    int16 v1,v2,v3,v4;
    int16 vx,vy;
    float vz;
    int16 vl,vr;
};

void Speed_caculation(struct resolution_v* wheels, int16 vx, int16 vy, float vz);
void main_control(void);
void CTRL_PwmCompensateCal(int set_S_bc,int act_S_bc);
void CTRL_PwmCompensateClear(void);
#endif /* CODE_CONTROL_H_ */
