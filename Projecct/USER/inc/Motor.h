#ifndef _Motor_h
#define _Motor_h
#include "headfile.h"

typedef struct
{
    uint8  Flag;	//标志位
	uint8  State;	//0弱 1中 2强 3停下来
}brake;       	//刹车

#if (CarMode==AE86)
#define   Motor_ftm       ftm0
#define   Left_DR         B9
#define   Right_CH        ftm_ch1
#define   Right_DR        B16
#define   Left_CH         ftm_ch0
#define	  RightForward		  0
#define	  RightBackward		  1
#define	  LeftForward		  0
#define	  LeftBackward		  1
#else
#define   Motor_ftm       ftm0
#define   Left_DR         B16
#define   Right_CH        ftm_ch0
#define   Right_DR        B9
#define   Left_CH         ftm_ch1
#define	  RightForward		  1
#define	  RightBackward		  0
#define	  LeftForward		  1
#define	  LeftBackward		  0
#endif

#define   Motor_HZ        15000


extern int32 LSpeedSet;//左轮预设值
extern int32 RSpeedSet;//右轮预设值
extern uint8  Reduce_ADD;
extern brake Brake;
extern int MotorPwmRight;
extern int MotorPwmLeft;
extern int Stright_Flag;
void Motor_Pwm_Out(int speed_left, int speed_right);
void Motor_Init();
void Speed_Set();
void Fast_Set();
void Stright_Judge();
void FastFast_Set();
void Low_Set();
void PIT0_IRQHandler(void);

#endif