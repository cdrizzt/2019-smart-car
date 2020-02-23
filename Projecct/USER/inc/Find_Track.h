#ifndef _FindTrack_h
#define _FindTrack_h
#include "headfile.h"
#define RowMax		140
#define ColumnMax	140
#define FAR		4
#define CLOSE   7
#define TrackArea_Ratio 0.4



#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )         //两位数取最大
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )         //两位数取最小

extern int16   MiddleLine[RowMax+1];   //中线数组
extern uint16   RightEdge[RowMax+1];    //右边线数组
extern uint16   LeftEdge[RowMax+1];     //左边线数组
extern uint16 	 MidPri;
//丢线标志
extern uint16   LeftLose;                 //左丢线行数
extern uint16   RightLose;                //右丢边行数
extern uint16   AllLose;                  //全丢边行数
extern uint16   AllLoseClose;             //近处全丢边行数
//左右起始行 拐点行
extern uint16   LeftStart;                //左第一不丢边行
extern uint16   RightStart;               //右第一不丢边行
//extern uint16	 LeftInfRow,LeftInfCol;		//左边丢线点
//extern uint16	 RightInfRow,RightInfCol;	//右边丢线点
extern uint16 	 LeftEndRow,RightEndRow;
//边线数量
extern uint16	Right_Quantity;
extern uint16	Left_Quantity;
//截止行
extern uint16 DropRow;
extern uint16 DropRow_Straight;
extern uint8   Lose_Line;
extern uint8    Width[RowMax+1];

void Search_CenterBlackline();
void Get_EndLine(uint8 middle);
void Calculation_Middleline();
void Search_CenterBlackline_Meeting();
#endif