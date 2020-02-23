#ifndef _headfile_h
#define _headfile_h




#define AE86 0
#define AE87 1
#define CarMode  AE86//选择车模 CarA 或 CarB


#define chronography 0	//计时
#define sendout		 0	//发送上位机
#define display      0  //黑白图像


#include "MK60_port_cfg.h"
#include "common.h"
#include "misc.h"
#include "stdio.h"


#include "MK60_rtc.h"
#include "MK60_gpio.h"
#include "MK60_systick.h"
#include "MK60_port.h"
#include "MK60_uart.h"
#include "MK60_pit.h"
#include "MK60_lptmr.h"
#include "MK60_ftm.h"
#include "MK60_adc.h"
#include "MK60_dac.h"
#include "MK60_flash.h"
#include "MK60_spi.h"
#include "MK60_i2c.h"
#include "MK60_wdog.h"
#include "MK60_dma.h"
#include "MK60_cmt.h"
#include "MK60_sdhc.h"

#include "isr.h"


#include "ff.h"


#include "SEEKFREE_MT9V032.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_NRF24L01.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_MPU6050.h"
//#include "SEEKFREE_28LCD.h"


#include "Steer.h"
#include "Motor.h"
#include "all_sturct.h"
#include "Parts.h"
#include "Find_Track.h"
#include "Canny.h"
#include "Tracktype.h"
#include "Roundabout.h"
#include "Crossroad.h"
#include "Out_PutData.h"
#include "Display.h"
#include "string.h"
#include "Meeting_Aera.h"
#include "Communicate.h"
#include "Zebra_Line.h"
#include "Rampway.h"
#include "math.h"
#include "Track_Information.h"
#include "swm1000.h"
#include "Electromagnetism.h"
/****************************************************/

#endif
