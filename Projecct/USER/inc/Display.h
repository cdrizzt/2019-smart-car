#ifndef _DISPLAY_h
#define _DISPLAY_h

#include "headfile.h"


typedef struct
{
    uint16 x;
    uint16 y;
} Site_t;       //坐标结构体


typedef struct
{
    uint16 W;       //宽
    uint16 H;       //高
} Size_t;       //矩阵大小结构体



void Display();
void Display_image(uint8 *prt,Site_t site, Size_t size);
void Display_cross(Site_t *prt,uint8 size,uint16 color);

void LCD_point(uint16 x,uint16 y, uint16 rgb565);
void lcd_showuint16(uint16 x,uint16 y,uint16 dat,int color);
void lcd_showint16(uint16 x,uint16 y,int16 dat,int color);
void lcd_showuint8(uint16 x,uint16 y,uint8 dat,int color);
void lcd_showuint8_3(uint16 x,uint16 y,uint16 dat,int color);
void lcd_showint8(uint16 x,uint16 y,int8 dat,int color);
void lcd_showstr(uint16 x,uint16 y,uint8 dat[],int color);
void lcd_showchar(uint16 x,uint16 y,uint8 dat,int color);
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end);
void Display_Information(uint8 i,uint8 Number,uint8 Long);

#endif