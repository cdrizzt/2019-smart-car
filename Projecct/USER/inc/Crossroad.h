#ifndef _Crossroads_h
#define _Crossroads_h
#include "headfile.h"

typedef struct
{
	char Start_Flag;		   //开始寻找十字标志位
	char Flag;                //标志位
	char Direction;           //十字方向 Leftside 0左斜 Rightside 1右斜  2直入
	char State;               //十字状态

}crossroad;       //十字结构体

extern uint16 newedge[140];
extern crossroad Crossroad;

void Judge_Crossroad(crossroad *prt);
void ModifyEdge_Crossroad(crossroad *prt);

#endif