#ifndef _Roundabout_h
#define _Roundabout_h

#include "headfile.h"

#define Rightside               1
#define Leftside                0
#define Straight                2

#define Entrance_Initial        7		//初值
#define Entrance_BaseRow        65		//标准行
#define Entrance_Coefficient    0.3	//变化范围
#define Min_Initial				2		//最小值

typedef struct
{
    uint8  Flag;			//标志位
	uint8  Direction;		//方向
	uint8  State;			//环岛状态
	uint8  Last_Time;		//上一次是否寻找到
	uint16 Col;				//补线点列
	uint16 Row;				//补线点行
	uint16 Wait;			//等待时间
	int16  Distance;		//环岛路程
	uint8  Size;			//大环 1 
	uint8  Number;			//环岛数量
	uint8  Mode;			//1电感 0摄像头
	
}roundabout;       	//环岛结构体

extern roundabout Roundabout;            //建立环岛结构体变量
extern uint8 Roundabout_Direction[6];

void Judge_Roundabout(roundabout *prt);			//环岛判断程序
void ModifyEdge_Roundabout(roundabout *prt);	//环岛补线

#endif