#ifndef _Tracktype_h
#define _Tracktype_h

#include "headfile.h"

typedef struct
{
    uint16 Row;//拐点的行坐标
    uint16 Col;//拐点的列坐标
    uint8  Flag;//拐点的标志位
    uint8  Number;//拐点的个数
} InflectionPoint; //建立拐点结构体

extern InflectionPoint  InflectionPointL;//建立左边拐点结构体变量
extern InflectionPoint  InflectionPointR;//建立左边拐点结构体变量

void FindInflectionPointR(InflectionPoint *inf ,unsigned char Start ,unsigned char End );
void FindInflectionPointL(InflectionPoint *inf ,unsigned char Start ,unsigned char End );
double EdgeSlope(uint8 LineMode,int16 ScanStart,int16 ScanEnd);
void EdgeSlopeIntercept(uint8 LineMode,int16 ScanStart,int16 ScanEnd,double *Slope,double *Intercept);
#endif