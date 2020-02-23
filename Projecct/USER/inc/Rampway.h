#ifndef _rampway_h
#define _rampway_h
#include "headfile.h"
#define  IPHONE 	3
#define uphill 		1
#define peak   		2
#define downhill	3

typedef struct
{       
	uint8	State;
	uint8   Flag;
	uint8 	Start;
}rampway;
extern rampway Rampway;

void Get_Angle();
void Meet_Rampway(rampway *prt);
extern int JKJ_Flag;

extern int16 Out[500];
extern int g_fAccel_y;
#define GYROSCOPE_ANGLE_SIGMA_FREQUENCY  40 //5ms调用一次
#define GRAVITY_ADJUST_TIME_CONSTANT     4   //时间补偿常数         2.0

typedef struct
{
    uint8       Up;
    uint8       Out;
	uint8 		Number;
    uint8       number;
    uint8       Time;
	uint8		Flag;
}bump;
extern bump Bump;
extern uint8 Bump_Long[5];

void Judge_Rampway(rampway *prt);
void Meet_Bump(bump *prt);

void Car_Rampway(rampway *prt);
void Bumpy_Road(bump *prt);
#endif