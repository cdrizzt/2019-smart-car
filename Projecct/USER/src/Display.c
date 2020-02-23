#include "Display.h"

/*******************************************
TFT液晶
分辨率              128*160    
*********************************************/

Site_t site={80,0};
Size_t size={80,80};
uint8 flag=0;
uint8 mode=0;

/*	
#if display
	for(int i=140;i>0;i--)
		for(int j=0;j<140;j++)
			image_canny[i][j]=0;
	
	for(int i=140;i>DropRow;i--)
		for(int j=0;j<138;j++)
		{
			if(j<LeftEdge[i]||j>RightEdge[i])
			{
				image_canny[i][j]=0;
			}
			else
			{
				image_canny[i][j]=255;
			}
		}
	Display_image(image_canny[0],site,size);    //图像显示函数
#else
	Display_image(image[0],site,size);    //图像显示函数
#endif
	*/

void Display0()
{
	int i;
	int32 a;
	Site_t site_point={0,0};
	site.x=80;	site.y=0;  //显示图像左上角位置    {x,y}
	size.W=80;	size.H=80;	//显示区域图像大小      {W,H}
	
	
	Display_image(image[0],site,size);    //图像显示函数
	for(i=ROW;i>=50;i--)                 //画线程序  按图像行数
	{
		site_point.x=site.x-i*size.H/ROW;
		//左线
		
		site_point.y=LeftEdge[i]*size.W/COL+2+site.y;    //计算X轴坐标  图像列数*（图像显示大小/图像原大小）
		LCD_point(site_point.x,site_point.y,GREEN);
		
		//右线
		site_point.y=RightEdge[i]*size.W/COL-2+site.y;
		LCD_point(site_point.x,site_point.y,YELLOW);
		
		//中线
		site_point.y=MiddleLine[i]*size.W/COL+site.y;
		LCD_point(site_point.x,site_point.y,RED);
		
		//偏差
		site_point.y=(int)(70-Error)*size.W/COL+site.y;
		LCD_point(site_point.x,site_point.y,BLACK);
		
	}
	for(i=50;i>=40;i--)
	{
		site_point.y=70*size.W/COL+site.y;
		LCD_point(site_point.x,site_point.y,RED);
	}
	//显示拐点
	if(InflectionPointR.Flag==1||InflectionPointL.Flag==1||Roundabout.State==2)
	{
		if(InflectionPointR.Flag==1)
		{
			site_point.y=InflectionPointR.Col*size.W/COL-2+site.y;
			site_point.x=site.x-InflectionPointR.Row*size.H/ROW;
			Display_cross(&site_point,3,BLUE);
		}
		
		if(InflectionPointL.Flag==1)
		{
			site_point.y=InflectionPointL.Col*size.W/COL-2+site.y;
			site_point.x=site.x-InflectionPointL.Row*size.H/ROW;
			Display_cross(&site_point,3,BLUE);
		}
		
		if(Roundabout.State==2)
		{
			site_point.y=Roundabout.Col*size.W/COL-2+site.y;
			site_point.x=site.x-Roundabout.Row*size.H/ROW;
			Display_cross(&site_point,4,WHITE);
		}
	}
	//
	if(Crossroad.State==2)
	{
		site_point.y=RightEdge[RightStart]*size.W/COL-2+site.y;
		site_point.x=site.x-RightStart*size.H/ROW;
		Display_cross(&site_point,3,GREEN);
		
		site_point.y=LeftEdge[LeftStart]*size.W/COL-2+site.y;
		site_point.x=site.x-LeftStart*size.H/ROW;
		Display_cross(&site_point,3,YELLOW);
	}
	
	site_point.x=128;//变量显示行地址
	site_point.y=0;
	lcd_showstr(site_point.x,site_point.y,"Le:",YELLOW);
	
	//显示参数
	{
		site_point.x=128;//变量显示行地址
		site_point.y=25;
		a=DropRow;
		lcd_showint8(site_point.x,site_point.y,a,YELLOW);
		
		
		site_point.x=113;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Ls:",YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=25;
		a=(int)DropRow_Straight;
		lcd_showint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Er:",YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=25;
		a=(int)Error;
		lcd_showint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=128;//变量显示行地址
		site_point.y=68;
		lcd_showstr(site_point.x,site_point.y,"A:",YELLOW);
		
		site_point.x=128;//变量显示行地址
		site_point.y=75;
		a=AllLose;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=68;
		lcd_showstr(site_point.x,site_point.y,"R:",YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=75;
		a=RightLose;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=68;
		lcd_showstr(site_point.x,site_point.y,"L:",YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=75;
		a=LeftLose;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=128;//变量显示行地址
		site_point.y=112;
		lcd_showstr(site_point.x,site_point.y,"AC:",YELLOW);
		
		site_point.x=128;//变量显示行地址
		site_point.y=128;
		a=AllLoseClose;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=112;
		lcd_showstr(site_point.x,site_point.y,"RS:",YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=128;
		a=Right_Quantity;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=112;
		lcd_showstr(site_point.x,site_point.y,"LS:",YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=128;
		a=Left_Quantity;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=80;//变量显示行地址
		site_point.y=80;
		lcd_showstr(site_point.x,site_point.y,"R:",YELLOW);
		
		site_point.x=80;//变量显示行地址
		site_point.y=97;
		if(InflectionPointR.Flag)
			a=InflectionPointR.Row;
		else
			a=0;
		lcd_showuint8_3(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=80;//变量显示行地址
		site_point.y=129;
		if(InflectionPointR.Flag)
			a=InflectionPointR.Col;
		else
			a=0;
		lcd_showuint8_3(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=64;//变量显示行地址
		site_point.y=80;
		lcd_showstr(site_point.x,site_point.y,"L:",YELLOW);
		
		site_point.x=64;//变量显示行地址
		site_point.y=97;
		if(InflectionPointL.Flag)
			a=InflectionPointL.Row;
		else
			a=0;
		lcd_showuint8_3(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=64;//变量显示行地址
		site_point.y=129;
		if(InflectionPointL.Flag)
			a=InflectionPointL.Col;
		else
			a=0;
		lcd_showuint8_3(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=48;//变量显示行地址
		site_point.y=80;
		lcd_showstr(site_point.x,site_point.y,"S:",YELLOW);
		
		site_point.x=48;//变量显示行地址
		site_point.y=97;
		a=Right_AD+Left_AD;
		lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
//		site_point.x=48;//变量显示行地址
//		site_point.y=105;
//		if(InflectionPointR.Flag)
//			a=InflectionPointR.Number;
//		else
//			a=0;
//		lcd_showchar(site_point.x,site_point.y,'0' + a,YELLOW);
//		
//		site_point.x=48;//变量显示行地址
//		site_point.y=120;
//		lcd_showstr(site_point.x,site_point.y,"LN:",YELLOW);
//		
//		site_point.x=48;//变量显示行地址
//		site_point.y=145;
////		if(InflectionPointL.Flag)
////			a=InflectionPointL.Number;
////		else
////			a=0;
//		a=Left_AD+Right_AD;
//		lcd_showchar(site_point.x,site_point.y,'0' + a,YELLOW);
		
		site_point.x=32;//变量显示行地址
		site_point.y=80;
		lcd_showstr(site_point.x,site_point.y,"L:",YELLOW);
		
		site_point.x=32;//变量显示行地址
		site_point.y=97;
		a=(uint16)(Left_AD);
		lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=16;//变量显示行地址
		site_point.y=80;
		lcd_showstr(site_point.x,site_point.y,"R:",YELLOW);
		
		site_point.x=16;//变量显示行地址
		site_point.y=97;
		a=Right_AD;
		lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
		
		site_point.y=129;
		
	}
}

void Display1()
{
	int i;
	int32 a;
	Site_t site_point={0,0};
	site.x=111;	site.y=0;  //显示图像左上角位置    {x,y}
	size.W=111;	size.H=111;	//显示区域图像大小阿      {W,H}
	
	Display_image(image[0],site,size);    //图像显示函数
	
	for(i=ROW;i>=50;i--)                 //画线程序  按图像行数
	{
		site_point.x=site.x-i*size.H/ROW;
		//左线
		
		site_point.y=LeftEdge[i]*size.W/COL+2+site.y;    //计算X轴坐标  图像列数*（图像显示大小/图像原大小）
		LCD_point(site_point.x,site_point.y,GREEN);
		
		//右线
		site_point.y=RightEdge[i]*size.W/COL-2+site.y;
		LCD_point(site_point.x,site_point.y,YELLOW);
		
		//中线
		site_point.y=MiddleLine[i]*size.W/COL+site.y;
		LCD_point(site_point.x,site_point.y,RED);
		
		//偏差
		site_point.y=(int)(70-Error)*size.W/COL+site.y;
		LCD_point(site_point.x,site_point.y,BLACK);
		
	}
	for(i=50;i>=40;i--)
	{
		site_point.y=70*size.W/COL+site.y;
		LCD_point(site_point.x,site_point.y,RED);
	}
	//显示拐点
	if(InflectionPointR.Flag==1||InflectionPointL.Flag==1||Roundabout.State==2)
	{
		if(InflectionPointR.Flag==1)
		{
			site_point.y=InflectionPointR.Col*size.W/COL-2+site.y;
			site_point.x=site.x-InflectionPointR.Row*size.H/ROW;
			Display_cross(&site_point,3,BLUE);
		}
		
		if(InflectionPointL.Flag==1)
		{
			site_point.y=InflectionPointL.Col*size.W/COL-2+site.y;
			site_point.x=site.x-InflectionPointL.Row*size.H/ROW;
			Display_cross(&site_point,3,BLUE);
		}
		
		if(Roundabout.State==2)
		{
			site_point.y=Roundabout.Col*size.W/COL-2+site.y;
			site_point.x=site.x-Roundabout.Row*size.H/ROW;
			Display_cross(&site_point,4,WHITE);
		}
	}
	//
	if(Crossroad.State==2)
	{
		site_point.y=RightEdge[RightStart]*size.W/COL-2+site.y;
		site_point.x=site.x-RightStart*size.H/ROW;
		Display_cross(&site_point,3,GREEN);
		
		site_point.y=LeftEdge[LeftStart]*size.W/COL-2+site.y;
		site_point.x=site.x-LeftStart*size.H/ROW;
		Display_cross(&site_point,3,YELLOW);
	}
	
	{
		
		site_point.x=128;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"Le:",YELLOW);
		
		
		site_point.x=128;//变量显示行地址
		site_point.y=25;
		a=DropRow;
		lcd_showint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=128;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"A:",YELLOW);
		
		site_point.x=128;//变量显示行地址
		site_point.y=120;
		a=AllLose;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"oo:",YELLOW);
		
		site_point.x=113;//变量显示行地址
		site_point.y=120;
		a=Meeting_Other.Oder;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"mo",YELLOW);
		
		site_point.x=98;//变量显示行地址
		site_point.y=120;
		a=Meeting_My.Oder;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=83;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"of:",YELLOW);
		
		site_point.x=83;//变量显示行地址
		site_point.y=130;
		a=Meeting_Other.Flag;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=68;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"os:",YELLOW);
		
		site_point.x=68;//变量显示行地址
		site_point.y=130;
		a=Meeting_Other.State;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=53;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"Mf:",YELLOW);
		
		site_point.x=53;//变量显示行地址
		site_point.y=130;
		a=Meeting_My.Flag;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=38;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"ms:",YELLOW);
		
		site_point.x=38;//变量显示行地址
		site_point.y=130;//site_point.y=123;
		a=Meeting_My.State;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
		
		site_point.x=23;//变量显示行地址
		site_point.y=113;
		lcd_showstr(site_point.x,site_point.y,"me",YELLOW);
		
		site_point.x=23;//变量显示行地址
		site_point.y=130;//site_point.y=123;
		a=Meeting_My.End;
		lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
	}
	
}

void Display2()
{
	int32 a;
	flag=1;
	Site_t site_point={0,0};
/**************************************************/
	site_point.x=128;//变量显示行地址
	site_point.y=0;
	lcd_showstr(site_point.x,site_point.y,"R:",YELLOW);
	
	
	site_point.x=128;//变量显示行地址
	site_point.y=17;
	a=Right_AD;
	lcd_showint8(site_point.x,site_point.y,a,YELLOW);
	
	site_point.x=113;//变量显示行地址
	site_point.y=0;
	lcd_showstr(site_point.x,site_point.y,"L:",YELLOW);
		
	site_point.x=113;//变量显示行地址
	site_point.y=17;
	a=Left_AD;
	lcd_showint8(site_point.x,site_point.y,a,YELLOW);
	
	site_point.x=98;//变量显示行地址
	site_point.y=0;
	lcd_showstr(site_point.x,site_point.y,"S:",YELLOW);
	
	
	site_point.x=98;//变量显示行地址
	site_point.y=17;
	a=(int16)Left_AD+Right_AD;
	lcd_showint8(site_point.x,site_point.y,a,YELLOW);
	
	site_point.x=128;//变量显示行地址
	site_point.y=70;
	lcd_showstr(site_point.x,site_point.y,"TR:",YELLOW);
	
	
	site_point.x=128;//变量显示行地址
	site_point.y=95;
	a=AD_right;
	lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
	
	site_point.x=113;//变量显示行地址
	site_point.y=70;
	lcd_showstr(site_point.x,site_point.y,"TL:",YELLOW);
	
	
	site_point.x=113;//变量显示行地址
	site_point.y=95;
	a=AD_left;
	lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
	
	site_point.x=93;//变量显示行地址
	site_point.y=70;
	lcd_showstr(site_point.x,site_point.y,"ML:",YELLOW);
	
	
	site_point.x=93;//变量显示行地址
	site_point.y=95;
	a=ad_max_left;
	lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
	
	site_point.x=78;//变量显示行地址
	site_point.y=70;
	lcd_showstr(site_point.x,site_point.y,"MR:",YELLOW);
	
	
	site_point.x=78;//变量显示行地址
	site_point.y=95;
	a=ad_max_right;
	lcd_showuint16(site_point.x,site_point.y,a,YELLOW);
/****************************************************/
	
	if(Button_2==0)
	{
		while(Button_2==0);	//按键消抖
		systick_delay_ms(5);
		AD_Normalization_Flag=1;
		AD_Normalization();		//归一化
		flag=0;					//退出模式
		mode=0;
		dsp_single_colour(RED);	//切换模式时先清屏
		
	}
	if(Button_1==0)			
	{
		while(Button_1==0);	//按键消抖
		systick_delay_ms(5);
		flag=0;					//退出模式
		mode=0;
		dsp_single_colour(RED);	//切换模式时先清屏
	}
}

void Display3()
{
	
	int i;
	int32 a;
	Site_t site_point={0,0};
	
	//显示出图像
	{
		
		site.x=111;	site.y=0;  //显示图像左上角位置    {x,y}
		size.W=111;	size.H=111;	//显示区域图像大小阿      {W,H}
		
		Display_image(image[0],site,size);    //图像显示函数
		
		for(i=ROW;i>=50;i--)                 //画线程序  按图像行数
		{
			site_point.x=site.x-i*size.H/ROW;
			//左线
			
			site_point.y=LeftEdge[i]*size.W/COL+2+site.y;    //计算X轴坐标  图像列数*（图像显示大小/图像原大小）
			LCD_point(site_point.x,site_point.y,GREEN);
			
			//右线
			site_point.y=RightEdge[i]*size.W/COL-2+site.y;
			LCD_point(site_point.x,site_point.y,YELLOW);
			
			//中线
			site_point.y=MiddleLine[i]*size.W/COL+site.y;
			LCD_point(site_point.x,site_point.y,RED);
			
			
			site_point.y=(int)(70-Error)*size.W/COL+site.y;
			LCD_point(site_point.x,site_point.y,BLACK);
		}
		
		if(InflectionPointR.Flag==1||InflectionPointL.Flag==1||Roundabout.State==2)
		{
			if(InflectionPointR.Flag==1)
			{
				site_point.y=InflectionPointR.Col*size.W/COL-2+site.y;
				site_point.x=site.x-InflectionPointR.Row*size.H/ROW;
				Display_cross(&site_point,3,BLUE);
			}
			
			if(InflectionPointL.Flag==1)
			{
				site_point.y=InflectionPointL.Col*size.W/COL-2+site.y;
				site_point.x=site.x-InflectionPointL.Row*size.H/ROW;
				Display_cross(&site_point,3,BLUE);
			}
			
			if(Roundabout.State==2)
			{
				site_point.y=Roundabout.Col*size.W/COL-2+site.y;
				site_point.x=site.x-Roundabout.Row*size.H/ROW;
				Display_cross(&site_point,4,WHITE);
			}
		}
		
		if(Crossroad.State==2)
		{
			site_point.y=RightEdge[RightStart]*size.W/COL-2+site.y;
			site_point.x=site.x-RightStart*size.H/ROW;
			Display_cross(&site_point,3,GREEN);
			
			site_point.y=LeftEdge[LeftStart]*size.W/COL-2+site.y;
			site_point.x=site.x-LeftStart*size.H/ROW;
			Display_cross(&site_point,3,YELLOW);
		}
	}
	
	//显示参数
	{
		site_point.x=128;//变量显示行地址
		site_point.y=0;
		lcd_showstr(site_point.x,site_point.y,"exp_time:",YELLOW);
		
		
		site_point.x=128;//变量显示行地址
		site_point.y=25;
		a=EXP_Time;;
		lcd_showuint8_3(site_point.x,site_point.y,a,YELLOW);
	}
	//修改参数
	{
		if(Button_3==0)
		{
			while(Button_3==0);
			systick_delay_ms(5);
			EXP_Time=EXP_Time+5;
			EXP_Time=EXP_Time>209?209:EXP_Time;
			EXP_Time=EXP_Time<10?10:EXP_Time;
			while(EXP_Time!=set_exposure_time(EXP_Time));
		}
		if(Button_4==0)
		{
			while(Button_4==0);
			systick_delay_ms(5);
			EXP_Time=EXP_Time-7;
			EXP_Time=EXP_Time>209?209:EXP_Time;
			EXP_Time=EXP_Time<10?10:EXP_Time;
			while(EXP_Time!=set_exposure_time(EXP_Time));
		}
		
		if(Button_2==0)
		{
			systick_delay_ms(10);
			while(Button_2==0);
			Beep_ON;	
			systick_delay_ms(10);
			
			while(FLASH_EraseSector(252));	//擦除扇区
			systick_delay_ms(10);
			FLASH_WriteSector(252,(const uint8 *)&EXP_Time,16,0);//确认输入flash	255 254扇区用于电感 253扇区用于摄像头
			systick_delay_ms(5);
			flag=0;
			Beep_OFF;
			mode=0;
			dsp_single_colour(RED);	//切换模式时先清屏
		}
		if(Button_1==0)
		{
			flag=0;
			mode=0;
			dsp_single_colour(RED);	//切换模式时先清屏
		}
	
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      LCD显示函数 //调试函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:		显示图像 划线 数值
//	@Mode:		 0 正常显示（取消） 1 放大显示（会车区数据 确认） 2电感（- //不采集图像） 3 改曝光（+）
//	@Mode:		flag(锁位)//2 3锁位
//-------------------------------------------------------------------------------------------------------------------

void Display()
{
	
	//显示图像时程序运行时间100ms 在此时关闭图像采集
	
	if(flag==0)//不锁位是可以随意切换模式
	{
		if(Button_1==0)
		{
			while(Button_1==0);	//按键消抖
			systick_delay_ms(5);
			dsp_single_colour(RED);	//切换模式时先清屏
			mode=0;					//模式0
			
		}
		if(Button_2==0)
		{
			while(Button_2==0);	//按键消抖
			systick_delay_ms(5);
			dsp_single_colour(RED);	//切换模式时先清屏
			mode=1;					//模式0
		}
		if(Button_3==0)
		{
			while(Button_3==0);	//按键消抖
			systick_delay_ms(5);
			dsp_single_colour(RED);	//切换模式时先清屏
			mode=2;	
			flag=1;					//锁位
		}
		if(Button_4==0)
		{
			while(Button_4==0);	//按键消抖
			systick_delay_ms(5);
			dsp_single_colour(RED);	//切换模式时先清屏
			mode=3;		
			flag=1;					//锁位
		}
	}
	
	
	//mode=0;
	switch(mode)
	{
	case 0:	Display0();	 break;//正常显示模式 
	case 1:	Display1();	 break;//放大图像 会车区显示
	case 2:	Display2();	 break;//电感值显示 （不采集图像）
	case 3:	Display3();	 break;//调节曝光
	}
	
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      图像缩放函数
//  @param      image[0] site位置 size大小
//  @return     void					
//  @since      v1.0
//  Sample usage:		例子：displayimage(displayimage(image[0],site图像位置,size图像大小);
//-------------------------------------------------------------------------------------------------------------------
void Display_image(uint8 *prt,Site_t site, Size_t size)
{
	int i,j;
	uint16 color = 0;
	uint16 temp = 0;
	
	//	for(i=site.x;i<size.W+site.x;i++)//竖直显示
	//	{
	//		Lcd_SetRegion(i,site.y,i,160-1);		//坐标设置
	//		for(j=0;j<size.H;j++)
	//		{	
	//			temp = *(prt + j*ROW/size.H*COL + (i-site.x)*(COL-1)/(size.W-1));//读取像素点
	//			
	//			color=(0x001f&((temp)>>3))<<11;
	//			color=color|(((0x003f)&((temp)>>2))<<5);
	//			color=color|(0x001f&((temp)>>3));
	//			LCD_WriteData_16Bit(color);
	//		}
	//	}
	
	for(i=site.x;i>=site.x-size.H;i--)//横向显示
	{
		Lcd_SetRegion(i,site.y,i,160-1);		//坐标设置
		for(j=site.y;j<site.y+size.W;j++)
		{
			temp = *(prt + (site.x-i)*ROW/size.H*ROW + (j-site.y)*(COL-1)/(size.W-1));//读取像素点
			
			color=(0x001f&((temp)>>3))<<11;
			color=color|(((0x003f)&((temp)>>2))<<5);
			color=color|(0x001f&((temp)>>3));
			LCD_WriteData_16Bit(color);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      画点程序
//  @param      坐标 大小 颜色
//  @return     void					
//  @since      v1.0
//  Sample usage:		例子：Display_cross(Site_t *prt,uint8 size,uint16 color)
//-------------------------------------------------------------------------------------------------------------------
void Display_cross(Site_t *prt,uint8 size,uint16 color)
{
	int i;
	for(i=size;i>=-size;i--)
	{
		LCD_point(prt->x-i,prt->y-i,color);
		LCD_point(prt->x-i,prt->y+i,color);
	}
}
void LCD_point(uint16 x,uint16 y, uint16 rgb565)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(rgb565);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      按键调节显示函数
//  @param      
//  @return     void					
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Display_Information(uint8 i,uint8 Number,uint8 Long)
{
	uint8 a=0;
	Site_t site_point={0,0};
	site_point.x=128-i*15;//变量显示行地址
	site_point.y=0;
	if(i==0)
	{
		lcd_showstr(site_point.x,site_point.y,"BumpNo:",YELLOW);
		while(1);
	}
	if(i==1)
		lcd_showstr(site_point.x,site_point.y,"BumpLg:",YELLOW);
	if(i==2)
		lcd_showstr(site_point.x,site_point.y,"RoundNo:",YELLOW);
	if(i==3)
		lcd_showstr(site_point.x,site_point.y,"Le:",YELLOW);
	if(i==4)
		lcd_showstr(site_point.x,site_point.y,"Le:",YELLOW);
	
	
	
	site_point.y=50;
	a=Number;
	lcd_showuint8(site_point.x,site_point.y,a,YELLOW);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      字符显示函数
//  @param      
//  @return     void					
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar(uint16 x,uint16 y,uint8 dat,int color)
{
	uint8 i,j;
	uint8 temp;
	for(i=0; i<16; i++)
	{
		Lcd_SetRegion(x-i,y,x-i,y+7);
		temp = tft_ascii[dat-32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	LCD_WriteData_16Bit(color);
			else			LCD_WriteData_16Bit(BGCOLOR);
			temp>>=1;
		}
	}
}
void lcd_showstr(uint16 x,uint16 y,uint8 dat[],int color)
{
	uint16 j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		lcd_showchar(x,y+8*j,dat[j],color);
		j++;
	}
}

void lcd_showint8(uint16 x,uint16 y,int8 dat,int color)
{
	uint8 a[3];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar(x,y,'-',color);
		dat = -dat;
	}
	else	lcd_showchar(x,y,' ',color);
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar(x,y+(8*(i+1)),'0' + a[i],color);
		i++;
	}
	
}

void lcd_showuint8_3(uint16 x,uint16 y,uint16 dat,int color)
{
	uint16 a[3];
	uint8 i;
	a[0] = (uint16)dat/100;
	a[1] = (uint16)dat/10%10;
	a[2] = (uint16)dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar(x,y+(8*(i)),'0' + a[i],color);
		i++;
	}
	
}

void lcd_showuint8(uint16 x,uint16 y,uint8 dat,int color)
{
	uint8 a[2];
	uint8 i;
	
	a[0] = dat/10%10;
	a[1] = dat%10;
	
	i = 0;
	while(i<2)
	{
		lcd_showchar(x,y+(8*(i+1)),'0' + a[i],color);
		i++;
	}
	
}

void lcd_showint16(uint16 x,uint16 y,int16 dat,int color)
{
	uint8 a[5];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar(x,y,'-',color);
		dat = -dat;
	}
	else	lcd_showchar(x,y,' ',color);
	
	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	i = 0;
	
	while(i<5)
	{
		lcd_showchar(x,y+(8*(i+1)),'0' + a[i],color);
		i++;
	}
}

void lcd_showuint16(uint16 x,uint16 y,uint16 dat,int color)
{
	uint8 a[5];
	uint8 i;
	
	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar(x,y+(8*(i+1)),'0' + a[i],color);
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               dsp_single_colour(YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void dsp_single_colour(int color)
{
	uint8 i,j;
	Lcd_SetRegion(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
	for (i=0;i<TFT_Y_MAX;i++)
		for (j=0;j<TFT_X_MAX;j++)
			LCD_WriteData_16Bit(color);
}