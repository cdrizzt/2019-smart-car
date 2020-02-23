#ifndef _Meeting_Aeras_h
#define _Meeting_Aeras_h

#include "headfile.h"
#define First 1
#define Second 2


extern meeting_area Meeting_Area;
extern meeting Meeting_My;
extern meeting	Meeting_Other;

void Judge_Meetingarea(meeting_area *prt);
void Judge_Meeting(meeting *my,meeting *other,meeting_area * area);

#endif