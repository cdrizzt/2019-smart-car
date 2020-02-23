#include "Track_Information.h"


void Input_Information()
{
	int8 number=0;
	uint8 i=0,j=0,a=0;
	uint8 number1;
	Site_t site_point={0,0};
	if(Switch_8)
	{
		while(FLASH_EraseSector(255));	//擦除扇区
		systick_delay_ms(10);
		while(FLASH_EraseSector(254));	//擦除扇区
		systick_delay_ms(10);
		while(FLASH_EraseSector(253));	//擦除扇区
		systick_delay_ms(10);
		while(FLASH_EraseSector(252));	//擦除扇区
		systick_delay_ms(10);
		//环岛
		while(1)
		{
			if(Button_1==0)
			{
				while(Button_1==0);
				systick_delay_ms(5);
				number++;
			}
			if(Button_2==0)
			{
				while(Button_2==0);
				systick_delay_ms(5);
				number--;
			}
			if(Button_3==0)
			{
				systick_delay_ms(10);
				while(Button_3==0);
				systick_delay_ms(10);
				FLASH_WriteSector(255,(const uint8 *)&number,8,0);
				systick_delay_ms(5);
				Roundabout.Number=number;
				break;
			}
			site_point.x=128-i*15;//变量显示行地址
			site_point.y=0;
			lcd_showstr(site_point.x,site_point.y,"Ronud:",YELLOW);
			
			site_point.y=40;
			a=number;
			lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		}
		if(number>0)
		{
			j=1;
			number1=0;
			if(j==1)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(5);
						while(Button_3==0);
						systick_delay_ms(5);
						FLASH_WriteSector(255,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Roundabout_Direction[j]=number1;
						j++;
						
						break;
					}
					site_point.y=60;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
			}
			number1=0;
			if(j>number)
				goto Bump;
			if(j==2)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(5);
						while(Button_3==0);
						systick_delay_ms(5);
						FLASH_WriteSector(255,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Roundabout_Direction[j]=number1;
						j++;
						break;
					}
					site_point.y=78;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Bump;
			if(j==3)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(5);
						while(Button_3==0);
						systick_delay_ms(5);
						FLASH_WriteSector(255,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Roundabout_Direction[j]=number1;
						j++;
						break;
					}
					site_point.y=96;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Bump;
			if(j==4)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(5);
						while(Button_3==0);
						systick_delay_ms(5);
						FLASH_WriteSector(255,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Roundabout_Direction[j]=number1;
						j++;
						break;
					}
					site_point.y=114;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Bump;
			if(j==5)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(5);
						while(Button_3==0);
						systick_delay_ms(5);
						FLASH_WriteSector(255,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Roundabout_Direction[j]=number1;
						j++;
						break;
					}
					site_point.y=130;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Bump;
		}
	Bump:
		i++;
		number=0;
		number1=0;
		//颠簸路面
		while(1)
		{
			if(Button_1==0)
			{
				while(Button_1==0);
				systick_delay_ms(5);
				number++;
			}
			if(Button_2==0)
			{
				while(Button_2==0);
				systick_delay_ms(5);
				number--;
			}
			if(Button_3==0)
			{
				systick_delay_ms(10);
				while(Button_3==0);
				systick_delay_ms(10);
				FLASH_WriteSector(254,(const uint8 *)&number,8,0);
				systick_delay_ms(5);
				Bump.Number=number;
				break;
			}
			site_point.x=128-i*15;//变量显示行地址
			site_point.y=0;
			lcd_showstr(site_point.x,site_point.y,"Bump:",YELLOW);
			
			site_point.y=40;
			a=number;
			lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		}
		if(number>0)
		{
			j=1;
			number1=0;
			if(j==1)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(10);
						while(Button_3==0);
						systick_delay_ms(10);
						FLASH_WriteSector(254,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Bump_Long[j]=number1;
						j++;
						break;
					}
					site_point.y=60;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
			}
			number1=0;
			if(j>number)
				goto Rampway;
			if(j==2)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(10);
						while(Button_3==0);
						systick_delay_ms(10);
						FLASH_WriteSector(254,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Bump_Long[j]=number1;
						j++;
						break;
					}
					site_point.y=78;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Rampway;
			if(j==3)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(10);
						while(Button_3==0);
						systick_delay_ms(10);
						FLASH_WriteSector(254,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Bump_Long[j]=number1;
						j++;
						break;
					}
					site_point.y=96;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Rampway;
			if(j==4)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(10);
						while(Button_3==0);	
						systick_delay_ms(10);
						FLASH_WriteSector(254,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Bump_Long[j]=number1;
						j++;
						break;
					}
					site_point.y=114;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Rampway;
			if(j==5)
			{
				while(1)
				{
					if(Button_1==0)
					{
						while(Button_1==0);
						systick_delay_ms(5);
						number1++;
					}
					if(Button_2==0)
					{
						while(Button_2==0);
						systick_delay_ms(5);
						number1--;
					}
					if(Button_3==0)
					{
						systick_delay_ms(10);
						while(Button_3==0);	
						systick_delay_ms(10);
						FLASH_WriteSector(254,(const uint8 *)&number1,8,j*8);
						systick_delay_ms(5);
						Bump_Long[j]=number1;
						j++;
						break;
					}
					site_point.y=130;
					a=number1;
					lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
				}
				
			}
			number1=0;
			if(j>number)
				goto Rampway;
		}
	Rampway:
		i++;
		number=0;
		number1=0;
		while(1)
		{
			if(Button_1==0)
			{
				while(Button_1==0);
				systick_delay_ms(5);
				number++;
			}
			if(Button_2==0)
			{
				while(Button_2==0);
				systick_delay_ms(5);
				number--;
			}
			if(Button_3==0)
			{
				systick_delay_ms(10);
				while(Button_3==0);
				systick_delay_ms(10);
				FLASH_WriteSector(253,(const uint8 *)&number,8,0);
				systick_delay_ms(5);
	//			Rampway.Number=number;
				break;
			}
			site_point.x=128-i*15;//变量显示行地址
			site_point.y=0;
			lcd_showstr(site_point.x,site_point.y,"Rampway:",YELLOW);
			
			site_point.y=60;
			a=number;
			lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		}
	Meet:
		i++;
		number=0;
		number1=0;
		while(1)
		{
			if(Button_1==0)
			{
				while(Button_1==0);
				systick_delay_ms(5);
				number++;
			}
			if(Button_2==0)
			{
				while(Button_2==0);
				systick_delay_ms(5);
				number--;
			}
			if(Button_3==0)
			{
				systick_delay_ms(10);
				while(Button_3==0);
				systick_delay_ms(10);
				FLASH_WriteSector(252,(const uint8 *)&number,8,0);
				systick_delay_ms(5);
				Meeting_Area.Direction=number;
				break;
			}
			site_point.x=128-i*15;//变量显示行地址
			site_point.y=0;
			lcd_showstr(site_point.x,site_point.y,"Meet:",YELLOW);
			
			site_point.y=60;
			a=number;
			lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		}
		
	}	
	else
	{
		Roundabout.Number=flash_read(255,0,uint8);	
		systick_delay_ms(5);
		
		if(Roundabout.Number>0)
		{
			i=1;
			while(i<=Roundabout.Number)
			{
				Roundabout_Direction[i]=flash_read(255,i*8,uint8);	
				systick_delay_ms(5);
				i++;
			}
		}
		Bump.Number=flash_read(254,0,uint8);
		systick_delay_ms(5);systick_delay_ms(5);
		if(Bump.Number>0)
		{
			i=1;
			while(i<=Bump.Number)
			{
				Bump_Long[i]=flash_read(254,i*8,uint8);
				systick_delay_ms(5);
				i++;
			}
		}
	//	Rampway.Number=flash_read(253,0,uint8);
		systick_delay_ms(5);
		Meeting_Area.Direction=flash_read(252,0,uint8);
		systick_delay_ms(5);
		site_point.x=128-0;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Ronud:",YELLOW);
		
		site_point.y=40;
		a=Roundabout.Number;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		if(Roundabout.Number>0)
		{
			for(i=1;i<=Roundabout.Number;i++)
			{
				site_point.y=40+i*18;
				a=Roundabout_Direction[i];
				lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
			}
		}
		
		site_point.x=128-15*1;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Bump:",YELLOW);
		
		site_point.y=40;
		a=Bump.Number;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		if(Bump.Number>0)
		{
			for(i=1;i<=Bump.Number;i++)
			{
				site_point.y=40+i*18;
				a=Bump_Long[i];
				lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
			}
		}
		
		site_point.x=128-15*2;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Rampway:",YELLOW);
		
	//	site_point.y=40;
	//	a=Rampway.Number;
		//lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=128-15*3;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Meeting:",YELLOW);
		
		site_point.y=40;
		a=Meeting_Area.Direction;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		while(1)
		{			
			if(Button_3==0)
			{
				systick_delay_ms(5);
				while(Button_3==0);
				systick_delay_ms(5);
				break;
			}
		}
		
	}
}
