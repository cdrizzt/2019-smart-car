#ifndef Electromagnetism_h
#define Electromagnetism_h
#if (CarMode==AE86)
#define AD_Left 	 	ADC0_SE10//
#define AD_Right	 	ADC0_SE14//	
//#define AD_Right		ADC1_SE17	//C0	
#else
#define AD_Left 	 	ADC0_SE10//
#define AD_Right	 	ADC0_SE14//	
#endif

#include "headfile.h"

extern uint8 AD_Normalization_Flag;
extern uint16 Left_AD,Right_AD;
extern int16 AD_left,AD_right;
extern uint16 ad_max_left,ad_min_left;
extern uint16 ad_max_right,ad_min_right;
extern float Error_AD;
extern uint8 Fail;
void ADC_init();
void AD_Normalization();
void Read_ADC();

#endif