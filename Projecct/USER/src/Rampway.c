#include "rampway.h"
rampway Rampway;
bump Bump;
uint8 Bump_Long[5]={0};
uint8 Rampway_flag=0;
float  g_fGravityAngle=0.0;
float g_fGyroAngleSpeed=0.0;

int RFlag=0;
float g_fCarAngle=0;
float  g_fCarAngle1=0;
float  g_fCarAngle2=0;
float  g_fCarAngle3=0;

int g_fAccel_y,g_fAccel_x,g_fAccel_z;
int  g_fAccel_yy[IPHONE]={0}, g_fAccel_xx[IPHONE]={0}, g_fAccel_zz[IPHONE]={0};
//static int KJK=0;


int JKJ_Flag=0;
float GYRO_RATIO = 1.75 ;//?????????????????0.34
float ACCE_RATIO = 0.8 ; //590   94.1                   45.3          1980    1750

float g_acce_off =8;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      坡道判断函数 //仅用摄像头以及延时
//  @return     int   
//  @since      v1.0
//  Sample usage:   State->uphill peak downhill 0
//-------------------------------------------------------------------------------------------------------------------
void Judge_Rampway(rampway *prt)
{
	static uint16 time=0;//强制消除坡道
	static uint8 TIME=0;//一段时间内不判坡道
	switch(prt->State)
	{
	case 0:
		{
			//if(Rampway.Start)		
			{
				if(DropRow<=48&&prt->State==0&&TIME==0&&DropRow_Straight<=50&&(Right_Quantity>=65||Left_Quantity>=65)&&(Right_Quantity+Left_Quantity+LeftLose+RightLose)>=130&&AllLoseClose<=34)//&&LeftEdge[DropRow]<60&RightEdge[DropRow]>80
			{
				prt->Flag=1;
				prt->State=uphill;
				
			}
			break;
			}
//			else
//			{
//				if(DropRow<=48&&prt->State==0&&TIME==0&&DropRow_Straight<=52&&(Right_Quantity>=65||Left_Quantity>=65)&&(Right_Quantity+Left_Quantity+LeftLose+RightLose)>=130&&AllLoseClose<=32)//&&LeftEdge[DropRow]<60&RightEdge[DropRow]>80
//			{
//				prt->Flag=1;
//				prt->State=uphill;
//			}
//			break;
//			}
		}
	case uphill:
		{
			if(DropRow_Straight>=70||(Right_Quantity+Left_Quantity)<=100)
			{
				prt->State=peak;
			}
			break;
		}
	case peak:
		{
			if((DropRow<=55&&time>=30)||(Right_Quantity+Left_Quantity)>=140||(Right_Quantity>=75)||(Left_Quantity>=75))		
			{
				prt->State=downhill;
			}
			break;
		}
	case downhill:
		{
			if(DropRow>=58||Stright_Flag||DropRow_Straight>=60)
			{
				
				prt->Flag=0;
				prt->State=0;
				time=0;
				
			}
			break;
		}
	}
	if(prt->Flag)
	{
		time++;
//		if(time>=6&&prt->State==uphill)
//		{
//			prt->Flag=0;
//				prt->State=0;
//				time=0;
//		}
		
		if((time>80&&prt->State==uphill))
		{
			time=0;
			prt->Flag=0;
			prt->State=0;
		}
	   if(time>120)
		{
			time=0;
			prt->Flag=0;
			prt->State=0;
		}
	
	}
	if(prt->State==downhill||TIME!=0)
	{
		TIME++;
		if(TIME>200)
		{
			TIME=0;
		}
	}

}


static int SHEN=0;
void Meet_Bump(bump *prt)
{  // Get_Angle();
	//prt->Number=0;
	//Get_Gyro();
	if(DropRow_Straight>=60&&!prt->Flag&&Right_Quantity>=40&&Left_Quantity>=40&&(mpu_gyro_y>=25||mpu_gyro_y<=-25)&&!Rampway.Flag&&!prt->Flag)
	{
		prt->Number++;
		
	}
	else
		if(prt->Number)
	{    SHEN++;
		if(SHEN>=15)
		{
			SHEN=0;
			prt->Number=0;
		}
	}
	if(prt->Number>=3)
	{
		prt->Number=0;
		prt->Flag=1;
	}
	
	
	if(prt->Flag&&mpu_gyro_z<=20&&mpu_gyro_z>=-20)
	{
		prt->number++;
		if(prt->number>=5)
		{ 
			prt->number=0;
			prt->Flag=0;
		}
	}
}


