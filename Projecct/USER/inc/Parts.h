#ifndef _Parts_h
#define _Parts_h


#include "headfile.h"

#define Led0 A14
#define Led1 A15
#define Led2 A16
#define Led3 A17
#define Led4 A25
#define Led5 A27
#define Led6 E25
#define Led7 E27

#define K1	C16
#define K2	C13
#define K3	C12
#define K4	C11
#define K5	C10
#define K6	C9
#define K7	C8
#define K8	C7
#define K9	C6
#define K10	C5
#define K11	C4
#define K12	C3
//xin

#define Fast_Level   0
#define Nor_Level    1
#define FastFast_Level   2
#define Low_Level      3
  extern int Level;
  void Speed_Level();
#define Beep	D10

#define button_1	B21
#define button_2	B20
#define button_3	B19
#define button_4	B18

#define  Button_1    gpio_get(button_1)
#define  Button_2    gpio_get(button_2)
#define  Button_3    gpio_get(button_3)
#define  Button_4    gpio_get(button_4)

#define  Switch_12	 gpio_get(K12)
#define  Switch_11	 gpio_get(K11)
#define  Switch_10	 gpio_get(K10)
#define  Switch_9	 gpio_get(K9)
#define  Switch_8    gpio_get(K8)
#define  Switch_7    gpio_get(K7)
#define  Switch_6    gpio_get(K6)
#define  Switch_5    gpio_get(K5)
#define  Switch_4    gpio_get(K4)
#define  Switch_3    gpio_get(K3)
#define  Switch_2    gpio_get(K2)
#define  Switch_1    gpio_get(K1)
#define  Beep_ON	 gpio_set(Beep,1)
#define  Beep_OFF	 gpio_set(Beep,0)


typedef enum
{
  LED0,
  LED1,
  LED2,
  LED3,
  LED4,
  LED5,
  LED6,
  LED7,
  LED_MAX,
}LED_e;

typedef enum LED_status
{
  LED_ON  =   0,            //灯亮(对应低电平)
  LED_OFF =   1             //灯暗(对应高电平)
}LED_status; 

void led_init(LED_e ledn);
void led(LED_e ledn,LED_status status);
void Switch_Init(void);
void Buzzer_Init(void);
void Button_Init(void);

#endif