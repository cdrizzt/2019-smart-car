#ifndef _Canny_h
#define _Canny_h

#include "headfile.h"
#define  Track_White 50
int Solve_Prewitt(int i,int j);

static uint8  BlackPoint[4] = {80,90,80,80};
static uint16 Preset_Threshold[4] = {2000,2200,2400,2000};

#endif