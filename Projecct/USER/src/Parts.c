#include "Parts.h"
  int Level=0;
PTX_n  LED[LED_MAX] = {Led0,Led1,Led2,Led3,Led4,Led5,Led6,Led7};
//-------------------------------------------------------------------------------------------------------------------
//  @brief      单个LED初始化
//  @return     void   
//  @since      v1.0
//  Sample usage:               led_init(LED1);
//-------------------------------------------------------------------------------------------------------------------
void led_init(LED_e ledn)
{
    if(ledn < LED_MAX)
    {
        gpio_init(LED[ledn],GPO,LED_OFF);
    }
    else
    {
        ledn = LED_MAX;
        while(ledn--)
        {
          if(ledn<=LED3)
            gpio_init(LED[ledn],GPO,LED_OFF);
          else
            gpio_init(LED[ledn],GPO,LED_ON);
        }

    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      点亮LED
//  @return     void   
//  @since      v1.0
//  Sample usage:               LED_init();
//-------------------------------------------------------------------------------------------------------------------
void led(LED_e ledn,LED_status status)
{
    if(ledn < LED_MAX)
    {
        if(ledn<LED4)
            gpio_set(LED[ledn],status);
          else
            gpio_set(LED[ledn],!status);
    }
    else
    {
        ledn = LED_MAX;
        while(ledn--)
        {
          if(ledn<LED4)
            gpio_set(LED[ledn],status);
          else
            gpio_set(LED[ledn],!status);
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      拨码开关初始化
//  @return     void   
//  @since      v1.0
//  Sample usage:               由D8-D15 高电平出发
//-------------------------------------------------------------------------------------------------------------------
void Switch_Init(void)
{
        gpio_init(K1, GPI,0);
        gpio_init(K2, GPI,0);
        gpio_init(K3, GPI,0);
        gpio_init(K4, GPI,0);
        gpio_init(K5, GPI,0);
		gpio_init(K6, GPI,0);
		gpio_init(K7, GPI,0);
		gpio_init(K8, GPI,0);
		gpio_init(K9, GPI,0);
		gpio_init(K10, GPI,0);
		gpio_init(K11, GPI,0);
		gpio_init(K12, GPI,0);
			
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      按键初始化
//  @return     void   
//  @since      v1.0
//  Sample usage:        Button1
//-------------------------------------------------------------------------------------------------------------------
void  Button_Init()
{
	gpio_init(button_1,GPI,0);
	gpio_init(button_2,GPI,0);
	gpio_init(button_3,GPI,0);
	gpio_init(button_4,GPI,0);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      蜂鸣器初始换
//  @return     void   
//  @since      v1.0
//  Sample usage:               Beep_ON/Beep_OFF 高电平触发
//-------------------------------------------------------------------------------------------------------------------
void Buzzer_Init()
{
    gpio_init(Beep,GPO,0);
}

void Speed_Level()
{
	if(!Switch_12&&!Switch_11)
	{
		Level=Nor_Level;
		led(LED0,LED_ON);	
	}
	else  
		if(Switch_12&&!Switch_11)
	{
		Level=Fast_Level;
		//led(LED1,LED_ON);	
	}	
	else
			if(Switch_12&&Switch_11)
			{
			Level=Low_Level;
			}
else
	if(!Switch_12&&Switch_11)
	{
	Level=FastFast_Level;
	}

}
