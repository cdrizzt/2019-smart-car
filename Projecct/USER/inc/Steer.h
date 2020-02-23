#ifndef _Steer_h
#define _Steer_h

#include "headfile.h"

#define Steer_ftm       ftm3
#define Steer_CH        ftm_ch1
#define Steer_HZ        50
#if (CarMode==AE86)

#define SteerMiddle		686
#define SteerMax		756
#define SteerMin		602

#else 
#define SteerMiddle		913
#define SteerMax		992    //×ó
#define SteerMin		830   //ÓÒ

#endif
extern uint32  SteerPwm;
extern float  Error;
extern float  LastError;


void Steer_Init(void);
void Steer_Ctrl(); 

#endif