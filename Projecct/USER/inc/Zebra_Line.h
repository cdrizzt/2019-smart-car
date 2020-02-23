#ifndef _Zebra_Line_h
#define _Zebra_Line_h

#include "headfile.h"

typedef struct
{
    uint8  Flag;      //标志位
	uint8  Start_Flag;//起始寻找标志位
    uint16 StartRow;  //起始行
    uint16 EndRow;    //结束行
	uint16 Second_Flag;
	
}zebracrossing;       //斑马线
extern zebracrossing ZebraCrossing;
void Judge_ZebraCrossing(zebracrossing *prt);
void Judge_MiddleZebraCrossing(zebracrossing *prt);
void ModifyEdge_ZebraCrossing(zebracrossing *prt);
#endif
