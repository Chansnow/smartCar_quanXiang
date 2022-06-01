
#ifndef CODE_PIDCONTROL_H_
#define CODE_PIDCONTROL_H_
#include "FIRELOCK.h"

struct MOTORpid
{
   float kp;
   float ki;
   float kd;

   float err;
   float err_1;
   float err_2;

   float value;
};

struct Positionpid
{
   float kp;
   float ki;
   float kd;

   float inter;
   float err;
   float err_1;
   float err_2;
   float ec;

   float value;
};

struct Turnpid
{
   float kp;
   float ki;
   float kd;

   float inter;
   float err;
   float err_1;
   float err_2;

   float value;
};

float Position_PID(struct Positionpid* pid,int set_value,int actual_value);
float MOTOR_PID(struct MOTORpid* pid,int set_value,int actual_value);
float Turn_PID(struct Turnpid* pid, float set, int act);
void PID_PositionClear(struct Positionpid* pid);
void PID_MotorClear(struct MOTORpid *pid);
void PID_TurnClear(struct Turnpid *pid);
float ALGO_Fabs(float num);
int ALGO_Abs(int num);
float FUZZY_P(int e, int ec);
#endif /* CODE_PIDCONTROL_H_ */
