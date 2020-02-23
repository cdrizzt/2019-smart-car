#include "Steer.h"

float  Error;
float  LastError;
float  SteerPwmAdd;
uint32  SteerPwm;

#if (CarMode==AE86)
float  BasicP=0.5;
float  KP=0;
float  J=0.0035;//比例因子
float  BasicD=0;
float  KD=0;
float  JD=0.000;//比例因子
#else
float  BasicP=0.5;
float  KP=0;
float  J=0.0025;//比例因子
float  BasicD=0;
float  KD=0;
float  JD=0.000;//比例因子
#endif

#if (CarMode==AE86)
float Weight[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,     //30-39
	0,0,0,0,0,0,0,0,0,0,       //40-49
	0,0,0,0,0,0,0,0,0,0,      //50-59
	0,5,5,5,6,6,7,7,7,6,       //60-69
	6,6,6,5,5,5,5,4,4,4,     //70-79
	4,4,3,3,3,2,2,2,2,2,      //80-89
	1,1,1,1,1,1,1,1,1,1,         //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
    1,1,1,1,1,1,1,1,1,1,        //100-109
    1,1,1,1,1,1,1,1,1,1,   //110-119
	1,0,0,0,0,0,0,0,0,0,     //120-129
	0,0,0,0,0,0,0,0,0,0,       //130-139
};
float Weight_Crossroad[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,     //30-39
	0,0,0,0,0,0,0,0,0,0,       //40-49
	1,1,1,1,1,1,1,1,1,1,     //50-59
	1,1,1,1,1,1,1,1,1,1,       //60-69
	1,1,1,1,1,1,1,1,1,1,     //70-79
	1,1,1,1,1,1,1,1,1,1,      //80-89
	1,1,1,1,1,1,1,1,1,1,       //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
	1,0,0,0,0,0,0,0,0,0,         //100-109
	1,0,0,0,0,0,0,0,0,0,      //110-119
	1,0,1,0,1,0,1,0,1,0,      //120-129
	0,0,0,0,0,0,0,0,0,0       //130-139
};
float Weight_Meeting[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,      //30-39
	0,0,0,0,0,0,0,0,0,0,      //40-49
	0,0,0,0,0,0,0,0,0,0,      //50-59
	0,0,0,0,0,0,0,0,0,0,      //60-69
	2,2,2,2,2,2,2,2,2,2,      //70-79
	3,3,3,3,3,3,3,3,3,3,      //80-89
	2,2,2,2,2,2,2,2,2,2,      //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
	1,1,1,1,1,1,1,1,1,1,      //100-109
	1,1,1,1,1,1,1,1,1,1,      //110-119
	1,0,1,0,1,0,1,0,1,0,      //120-129
	0,0,0,0,0,0,0,1,1,0       //130-139
};


float WeightBBB[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,     //30-39
	0,0,0,0,0,0,0,0,0,0,       //40-49
	0,0,0,0,0,0,0,0,0,0,      //50-59
	0,0,0,0,0,0,0,0,0,0,      //60-69
	0,0,0,0,0,0,0,0,0,0,     //70-79
	0,0,0,0,0,0,0,0,0,0,       //
	0,0,0,0,0,0,0,0,0,0,      //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
    0,0,0,0,0,0,0,0,0,0,        //100-109
    0,0,0,0,0,0,0,0,0,0,   //110-119
	1,1,1,1,1,1,1,1,1,1,    //120-129
	1,1,1,1,1,1,1,1,1,1,      //130-139
};
#else
float Weight[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,     //30-39
	0,0,0,0,0,0,0,0,0,0,       //40-49
	0,0,0,0,0,0,0,0,0,0,      //50-59
	0,5,5,5,6,6,7,7,7,6,       //60-69
	6,6,6,5,5,5,5,4,4,4,     //70-79
	4,4,3,3,3,2,2,2,2,2,      //80-89
	1,1,1,1,1,1,1,1,1,1,         //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
    1,1,1,1,1,1,1,1,1,1,        //100-109
    1,1,1,1,1,1,1,1,1,1,   //110-119
	1,0,0,0,0,0,0,0,0,0,     //120-129
	0,0,0,0,0,0,0,0,0,0,       //130-139
};
float Weight_Crossroad[140]={       
	1,1,1,1,1,1,1,1,1,1,      //0-9
	1,1,1,1,1,1,1,1,1,1,      //10-19
	1,1,1,1,1,1,1,1,1,1,      //20-29
	1,1,1,1,1,1,1,1,1,1,     //30-39
	1,1,1,1,1,1,1,1,1,1,       //40-49
	1,1,1,1,1,1,1,1,1,1,     //50-59
	1,1,1,1,1,1,1,1,1,1,       //60-69
	1,1,1,1,1,1,1,1,1,1,     //70-79
	1,1,1,1,1,1,1,1,1,1,      //80-89
	1,1,1,1,1,1,1,1,1,1,       //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
	1,0,0,0,0,0,0,0,0,0,         //100-109
	1,0,0,0,0,0,0,0,0,0,      //110-119
	0,0,0,0,0,0,0,0,0,0,      //120-129
	0,0,0,0,0,0,0,0,0,1       //130-139
};
float Weight_Meeting[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,      //30-39
	0,0,0,0,0,0,0,0,0,0,      //40-49
	0,0,0,0,0,0,0,0,0,0,      //50-59
	0,0,0,0,0,0,0,0,0,0,      //60-69
	2,2,2,2,2,2,2,2,2,2,      //70-79
	3,3,3,3,3,3,3,3,3,3,      //80-89
	2,2,2,2,2,2,2,2,2,2,      //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
	1,1,1,1,1,1,1,1,1,1,      //100-109
	1,1,1,1,1,1,1,1,1,1,      //110-119
	1,0,1,0,1,0,1,0,1,0,      //120-129
	0,0,0,0,0,0,0,1,1,0       //130-139
};

float WeightBBB[140]={       
	0,0,0,0,0,0,0,0,0,0,      //0-9
	0,0,0,0,0,0,0,0,0,0,      //10-19
	0,0,0,0,0,0,0,0,0,0,      //20-29
	0,0,0,0,0,0,0,0,0,0,     //30-39
	0,0,0,0,0,0,0,0,0,0,       //40-49
	0,0,0,0,0,0,0,0,0,0,      //50-59
	0,0,0,0,0,0,0,0,0,0,      //60-69
	0,0,0,0,0,0,0,0,0,0,     //70-79
	0,0,0,0,0,0,0,0,0,0,        //
	0,0,0,0,0,0,0,0,0,0,    //90-99 5,5,5,5,5,5,5,5,5.5,       //80-89
 	0,0,0,0,0,0,0,0,0,0,         //100-109
 	0,0,0,0,0,0,0,0,0,0,     //110-119
	1,1,1,1,1,1,1,1,1,1,  //120-129
	1,1,1,1,1,1,1,1,1,1,       //130-139
};

#endif
//---------------------------------------------------------------------------------------------------------------
//  @brief      舵机初始化
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	ftm1_ch0        50Hz
//-------------------------------------------------------------------------------------------------------------------
void Steer_Init()
{
#if (CarMode==AE86)
	switch(Level)
	{
	case Fast_Level :   
		J=0.0025;
		break; 
	case Nor_Level :    
		J=0.001;
		break;
	case FastFast_Level:
		{
			J=0.0028;
			break;
		}
	case Low_Level:
		{
			J=0.001;
			break;
		}
		
	}
#else
	switch(Level)
	{
	case Fast_Level :   
		J=0.0026;
		break; 
	case Nor_Level :    
		J=0.001;
		break;
	case FastFast_Level:
		{
			J=0.0025;
			break;
		}
	case Low_Level:
		{
			J=0.00085;
			break;
		}
		
	}
#endif
	ftm_pwm_init(Steer_ftm,Steer_CH,Steer_HZ,SteerMiddle);//908  830  992
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      舵机偏差计算
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	Error=中值-偏差量
//-------------------------------------------------------------------------------------------------------------------
void Steer_Error()
{
	float ErrorSum=0;           //MiddleLine[i]*Weight[i]
	float WeightCalSum=0;       //權值累加
	float Value=0;              //ErrorSum/ErrorCalSum
	int i;
	for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
	{
		ErrorSum+=MiddleLine[i]*Weight[i];
		WeightCalSum+= Weight[i];
	}
	if(WeightCalSum==0)
		Error=LastError;
	else
	{
		Value=(ErrorSum/WeightCalSum);
		Error=70-Value;
		
	}
	if(Error>=70.0)       //限制幅值
		Error=70.0;
	
	if(Error<=-70.0)
		Error=-70.0; 
	
	if(Stright_Flag)
	{
		KP=0.5;
		KD=2.5;
		if(DropRow_Straight>=68)
		{
			//if(ABS(Error)>=12)
			KP=BasicP+(Error* Error)*J;//KP
			
			
			switch(Level)
			{
			case Fast_Level :   
				KD=6.5;
				break; 
			case Nor_Level :    
				KD=2.5;
				break;
			case FastFast_Level:
				{
					KD=6;
					break;
				}
			case Low_Level:
				{
					KD=2;
					break;
				}
				
			}
		}
	}
	else
	{	
		//		if(ABS(Error)>=12)
		KP=BasicP+(Error* Error)*J;//KP
		//		else
		//			KP=0.5;
		
		switch(Level)
		{
		case Fast_Level :   
			KD=6.5;
			break; 
		case Nor_Level :    
			KD=2.5;
			break;
		case FastFast_Level:
			{
				KD=7.5;
				break;
			}
		case Low_Level:
			{
				KD=2;
				break;
			}
			
		}
		
	}
	if(KP>=13) KP=13;//P值限幅
	
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      十字舵机偏差计算
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	Error=中值-偏差量
//-------------------------------------------------------------------------------------------------------------------
void Cross_Error()
{
	float ErrorSum=0;           //MiddleLine[i]*Weight[i]
	float WeightCalSum=0;       //權值累加
	float Value=0;              //ErrorSum/ErrorCalSum
	uint16 Start,End;
	static uint8 last_state;
	int i;
	
	if(Crossroad.State==1)
	{
		if(Crossroad.Direction==Straight)
		{    
			End=MAX(InflectionPointR.Row,InflectionPointL.Row);
			for(i=MAX(LeftStart,RightStart);i>End;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight_Crossroad[i];
				WeightCalSum+=Weight_Crossroad[i];
			}
			
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=(70-Value);
			}
			if(Error>=70.0)    Error=70.0;
			
			if(Error<=-70.0)   Error=-70.0; 
		}
		else if(Crossroad.Direction==Leftside)
		{
			End=InflectionPointL.Row;
			for(i=LeftStart;i>End;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight_Crossroad[i];
				WeightCalSum+=Weight_Crossroad[i];
			}
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=(70-Value);
			}
			if(Error>=70.0)     Error=70.0;
			if(Error<=-70.0)    Error=-70.0; 
			
		}
		else if(Crossroad.Direction==Rightside)
		{
			End=InflectionPointR.Row;
			for(i=RightStart;i>End;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight_Crossroad[i];
				WeightCalSum+=Weight_Crossroad[i];
			}
			
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=(70-Value);
			}
			if(Error>=70.0)   Error=70.0;
			if(Error<=-70.0)  Error=-70.0; 
		}
		KP=BasicP+(Error* Error)*0.001;//KP
		KD=2;
	}
	else if(Crossroad.State==2)
	{
		if(Crossroad.Direction==Straight)
		{
			if(RightStart>100)
				Start=LeftStart;
			else if(LeftStart>100)
				Start=RightStart;
			else
				Start=MAX(RightStart,LeftStart);
			
			for(i=Start;i>DropRow;i--)
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+= Weight[i];
			}
			if(WeightCalSum==0||(RightStart>100&&LeftStart>100))
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=(70-Value);
			}
			if(Error>=70.0)     Error=70.0;
			if(Error<=-70.0)    Error=-70.0; 
		}
		else if(Crossroad.Direction==Leftside)
		{
			if(RightStart>100)
				Start=LeftStart;
			else if(LeftStart>100)
				Start=RightStart;
			else
				Start=MAX(RightStart,LeftStart);
			for(i=Start;i>DropRow;i--)
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+=Weight[i];
			}
			
			if(WeightCalSum==0||(RightStart>100&&LeftStart>100))
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=(70-Value);
			}
			if(DropRow+AllLoseClose>=130)
				Error=LastError;
			if(Error>=70.0)     Error=70.0;
			if(Error<=-70.0)    Error=-70.0; 
		}
		else if(Crossroad.Direction==Rightside)
		{
			if(RightStart>100)
				Start=LeftStart;
			else if(LeftStart>100)
				Start=RightStart;
			else
				Start=MAX(RightStart,LeftStart);
			for(i=Start;i>DropRow;i--)
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+=Weight[i];
			}
			
			if(WeightCalSum==0||(RightStart>100&&LeftStart>100))
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=(70-Value);
			}
			
			
			if(DropRow+AllLoseClose>=130)
				Error=LastError;
			
			if(Error>=70.0)     Error=70.0;
			if(Error<=-70.0)    Error=-70.0; 
		}
		KP=BasicP+(Error* Error)*J;//KP
		if(last_state==1)
			KD=0;
		else
			KD=4;
	}
	last_state=Crossroad.State;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      环岛舵机偏差计算
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	Error=中值-偏差量
//-------------------------------------------------------------------------------------------------------------------
void Roundabout_Error()
{
	static uint8 last_state;
	float ErrorSum=0;           //MiddleLine[i]*Weight[i]
	float WeightCalSum=0;       //權值累加
	float Value=0;              //ErrorSum/ErrorCalSum
	int i;
	static float Roundabout_Error=0;
	
	
	switch(Level)
	{
	case Fast_Level :   
		if(Roundabout.State==5)
		{
			if(Roundabout.Size==1)
			{       
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-25?-25:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<25?25:Roundabout_Error;
				}
			}
			else
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-30?-30:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<30?30:Roundabout_Error;
				}
			}
		}
		else
		{
			for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+= Weight[i];
			}
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)  Error=70.0;
			if(Error<=-70.0) Error=-70.0; 
			
			if(Roundabout.State==4)
			{
				Roundabout_Error=Error;
			}
			else if(Roundabout.State==3)
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Error>-5?-5:Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Error<5?5:Error;
				}
			}
		}
		
		if(Roundabout.State!=1&&Roundabout.State!=2)
		{	
			if(Roundabout.Size==0)
			{	
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.5+(Error* Error)*0.002;//KP
				else
					KP=BasicP;
				if(Roundabout.State==4)
	{
		          if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.5+(Error* Error)*0.0008;//KP
				else
					KP=BasicP;
	}
				
				
				if(KP>=13) KP=13;//P值限幅
				
			}
			else
			{
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=1.0+(Error* Error)*0.0002;//KP
				else
					KP=BasicP;
			
				if(KP>=13) KP=13;//P值限幅
				
			}
		}
		else
		{
			if(Roundabout.Size==1)
				KP=0.9+(Error* Error)*0.0005;//KP
			else
				KP=1.2+(Error* Error)*0.0035;//KP
			if(KP>=13) KP=13;//P值限幅eak;
		}
		
		if(Roundabout.State==6)
		{
			KP=0.5+(Error* Error)*0.0025;//KP
			if(KP>=13) KP=13;//P值限幅eak;
		}
		
		if((last_state==1&&Roundabout.State==2)||last_state==5)
		{		
			if(Roundabout.Size==0)
				KD=2;
			else
				KD=0;
			
		}	
		else
		{		
			if(Roundabout.Size==0)
				KD=2;
			else
				KD=1;
			
		}
	
		
		if(Roundabout.State==6&&Roundabout.Size==1)
		{
		KD=5;
		}
		
		break; 
		
		//***************************	
	case Nor_Level :    
		if(Roundabout.State==5)
		{
			if(Roundabout.Size==1)
			{       
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-25?-25:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<25?25:Roundabout_Error;
				}
			}
			else
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-30?-30:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<30?30:Roundabout_Error;
				}
			}
		}
		else
		{
			for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+= Weight[i];
			}
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)  Error=70.0;
			if(Error<=-70.0) Error=-70.0; 
			
			if(Roundabout.State==4)
			{
				Roundabout_Error=Error;
			}
			else if(Roundabout.State==3)
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Error>-5?-5:Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Error<5?5:Error;
				}
			}
		}
		
		if(Roundabout.State!=1&&Roundabout.State!=2)
		{	
			if(Roundabout.Size==0)
			{	
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.5+(Error* Error)*0.002;//KP
				else
					KP=BasicP;
				if(Roundabout.State==4)
	{
		          if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.8+(Error* Error)*0.0002;//KP
				else
					KP=BasicP;
	}
				
				
				if(KP>=13) KP=13;//P值限幅
				
				
			}
			else
			{
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=1.0+(Error* Error)*0.0002;//KP
				else
					KP=BasicP;
				if(KP>=13) KP=13;//P值限幅
			}
	
		
		
		}
		else
		{
			if(Roundabout.Size==1)
				KP=0.5+(Error* Error)*0.00095;//KP
			else
				KP=0.5+(Error* Error)*0.003;//KP
			if(KP>=13) KP=13;//P值限幅eak;
		}
		if(Roundabout.State==6)
		{
			KP=0.5+(Error* Error)*J;//KP
		}
		
		if((last_state==1&&Roundabout.State==2)||last_state==5)
		{		
			if(Roundabout.Size==0)
				KD=4;
			else
				KD=0;
			
		}	
		else
		{		
			if(Roundabout.Size==0)
				KD=1;
			else
				KD=1;
			
		}
		
		if(Roundabout.State==6&&Roundabout.Size==1)
		{
		KD=3;
		}
		
		break;
		//***************************
	case Low_Level :    
		if(Roundabout.State==5)
		{
			if(Roundabout.Size==1)
			{       
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-25?-25:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<25?25:Roundabout_Error;
				}
			}
			else
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-30?-30:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<30?30:Roundabout_Error;
				}
			}
		}
		else
		{
			for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+= Weight[i];
			}
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)  Error=70.0;
			if(Error<=-70.0) Error=-70.0; 
			
			if(Roundabout.State==4)
			{
				Roundabout_Error=Error;
			}
			else if(Roundabout.State==3)
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Error>-5?-5:Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Error<5?5:Error;
				}
			}
		}
		
		if(Roundabout.State!=1&&Roundabout.State!=2)
		{	
			if(Roundabout.Size==0)
			{	
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=1.0+(Error* Error)*0.002;//KP
				else
					KP=BasicP;
				
								if(Roundabout.State==4)
	{
		          if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.5+(Error* Error)*0.002;//KP
				else
					KP=BasicP;
	}
				
				
				if(KP>=13) KP=13;//P值限幅
				
			}
			else
			{
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=1.0+(Error* Error)*0.0002;//KP
				else
					KP=BasicP;
				if(KP>=13) KP=13;//P值限幅
			}
		}
		else
		{
			if(Roundabout.Size==1)
				KP=0.5+(Error* Error)*0.00075;//KP
			else
				KP=0.5+(Error* Error)*0.003;//KP
			if(KP>=13) KP=13;//P值限幅eak;
		}
		if(Roundabout.State==6)
		{
			KP=0.5+(Error* Error)*J;//KP
		}
		
		if((last_state==1&&Roundabout.State==2)||last_state==5)
		{		
			if(Roundabout.Size==0)
				KD=3;
			else
				KD=0;
			
		}	
		else
		{		
			if(Roundabout.Size==0)
				KD=2;
			else
				KD=1;
			
		}
		
		
		
		break;
		//***************************
	case FastFast_Level :    
		if(Roundabout.State==5)
		{
			if(Roundabout.Size==1)
			{       
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-25?-25:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<25?25:Roundabout_Error;
				}
			}
			else
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Roundabout_Error>-30?-30:Roundabout_Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Roundabout_Error<30?30:Roundabout_Error;
				}
			}
		}
		else
		{
			for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
			{
				ErrorSum+=MiddleLine[i]*Weight[i];
				WeightCalSum+= Weight[i];
			}
			if(WeightCalSum==0)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)  Error=70.0;
			if(Error<=-70.0) Error=-70.0; 
			
			if(Roundabout.State==4)
			{
				Roundabout_Error=Error;
			}
			else if(Roundabout.State==3)
			{
				if(Roundabout.Direction==Rightside)
				{
					Error=Error>-5?-5:Error;
				}
				else if(Roundabout.Direction==Leftside)
				{
					Error=Error<5?5:Error;
				}
			}
		}
		
		if(Roundabout.State!=1&&Roundabout.State!=2)
		{	
			if(Roundabout.Size==0)
			{	
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.9+(Error* Error)*0.002;//KP
				else
					KP=BasicP;
								if(Roundabout.State==4)
	{
		          if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=0.5+(Error* Error)*0.002;//KP
				else
					KP=BasicP;
	}
				
				
				if(KP>=13) KP=13;//P值限幅
				
			}
			else
			{
				if(ABS(Error)>=12)
					//KP=1.3+(Error* Error)*0.0002;//KP
					KP=1.0+(Error* Error)*0.0002;//KP
				else
					KP=BasicP;
				if(KP>=13) KP=13;//P值限幅
			}
		}
		else
		{
			if(Roundabout.Size==1)
				KP=0.5+(Error* Error)*0.0015;//KP
			else
				KP=0.5+(Error* Error)*0.0035;//KP
			if(KP>=13) KP=13;//P值限幅eak;
		}
		if(Roundabout.State==6)
		{
			KP=0.5+(Error* Error)*J;//KP
		}
		
		if((last_state==1&&Roundabout.State==2)||last_state==5)
		{		
			if(Roundabout.Size==0)
				KD=3;
			else
				KD=0;
			
		}	
		else
		{		
			if(Roundabout.Size==0)
				KD=2;
			else
				KD=1;
			
		}
		
		
		
		break;
		
	}
	last_state=Roundabout.State;
	
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      坡道舵机偏差计算
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	Error=中值-偏差量
//-------------------------------------------------------------------------------------------------------------------
void Ramway_Error()
{
	float ErrorSum=0;           //MiddleLine[i]*Weight[i]
	float WeightCalSum=0;       //權值累加
	float Value=0;              //ErrorSum/ErrorCalSum
	int i;
	if(Rampway.State==peak)
	{	for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
		{
			ErrorSum+=MiddleLine[i]*WeightBBB[i];
			WeightCalSum+= WeightBBB[i];
		}

	if(WeightCalSum==0)
		Error=LastError;
	else
	{
		Value=(ErrorSum/WeightCalSum);
		Error=70-Value;
		
	}
	}
	else
	{
	for(i=MAX(RightStart,LeftStart);i>DropRow+2;i--)//中線坐標 加權平均
		{
			ErrorSum+=MiddleLine[i]*Weight[i];
			WeightCalSum+= Weight[i];
		}

	if(WeightCalSum==0)
		Error=LastError;
	else
	{
		Value=(ErrorSum/WeightCalSum);
		Error=70-Value;
		
	}
	
	}

	if(Error>=40.0)       //限制幅值
		
		Error=40.0;
	
	if(Error<=-40.0)
		
		Error=-40.0; 
		if(AllLose+AllLoseClose>=30)
		{
				if(Error>=20.0)       //限制幅值
		
		Error=20.0;
	
	if(Error<=-20.0)
		
		Error=-20.0; 
			
		KP=BasicP;//KP
		KD=2;
		}
		else
		{
		
			
			KP=BasicP+(Error* Error)*J;//KP
		KD=2;}
	if(KP>=13) KP=13;//P值限幅
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      会车区舵机偏差计算
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	Error=中值-偏差量
//-------------------------------------------------------------------------------------------------------------------
void Meeting_Error()
{
	float ErrorSum=0;           //MiddleLine[i]*Weight[i]
	float WeightCalSum=0;       //權值累加
	float Value=0;              //ErrorSum/ErrorCalSum
	int i;
	uint16 Start=0;
	if(Meeting_My.State==0)
	{
		//if(Meeting_My.Track_Mode==0)
		{
			for(i=LeftStart;i>DropRow+2;i--)//中線坐標 加權平均Roundabout.Direction==Rightside?LeftStart:RightStart
			{
				ErrorSum+=MiddleLine[i]*Weight_Meeting[i];
				WeightCalSum+= Weight_Meeting[i];
			}
			
			if(WeightCalSum==0)//|| Lose_Line)
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)       //限制幅值
				Error=70.0;
			if(Error<=-70.0)
				Error=-70.0; 
			
			if(Lose_Line==1)
				Error=-70;
			
			if(ABS(Error)>=12)
				KP=1+(Error* Error)*J;//KP
			else
				KP=1;
			if(KP>=13) KP=13;//P值限幅
			KD=2;
		}
		//		else
		//		{
		//			Error=-(17-Right_AD*1)*2.3;
		//			
		//			KP=2.2;
		//			KD=0.8;
		//		}
	}
	else if(Meeting_My.State==1||Meeting_My.State==6)
	{
		//if(Meeting_My.Track_Mode==0||Meeting_My.State==6)
		{
			for(i=LeftStart;i>DropRow+2;i--)//中線坐標 加權平均Roundabout.Direction==Rightside?LeftStart:RightStart
			{
				if(i<ZebraCrossing.StartRow+1&&i>ZebraCrossing.EndRow-1)//终点线在近处时
				{
					continue;
				}
				ErrorSum+=MiddleLine[i]*Weight_Meeting[i];
				WeightCalSum+= Weight_Meeting[i];
			}
			
			if(WeightCalSum==0)//|| Lose_Line
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)       //限制幅值
				Error=70.0;
			if(Error<=-70.0)
				Error=-70.0; 
			if(Lose_Line==1)
				Error=-70;
			if(Meeting_My.End==1)
			{
				if(Error<-18)
					Error=-18;
				if(Error>18)
					Error=18;
			}
			
			if(ABS(Error)>=12)
				KP=1+(Error* Error)*J;//KP
			else
				KP=1;
			if(KP>=13) KP=13;//P值限幅
			KD=2;
		}
//		else
//		{
//			
//			Error=-(28-Right_AD*1);
//			if(Meeting_My.End==1)
//			{
//				if(Error<-18)
//					Error=-18;
//				if(Error>18)
//					Error=18;
//			}
//			if(ABS(Error)>=12)
//				KP=3;//KP
//			else
//				KP=4;
//			if(KP>=13) KP=13;//P值限幅
//			KD=0.8;
//			
//		}
	}
	
	else if(Meeting_My.State==3||Meeting_My.State==5)
	{
		if(Meeting_My.Electric==0)
		{
			Start=MAX(RightStart,LeftStart);
			for(i=Start;i>DropRow+2;i--)//中線坐標 加權平均Roundabout.Direction==Rightside?LeftStart:RightStart
			{
				ErrorSum+=MiddleLine[i]*Weight_Meeting[i];
				WeightCalSum+= Weight_Meeting[i];
			}
			
			if(WeightCalSum==0)//|| Lose_Line
				Error=LastError;
			else
			{
				Value=(ErrorSum/WeightCalSum);
				Error=70-Value;
			}
			if(Error>=70.0)       //限制幅值
				Error=70.0;
			if(Error<=-70.0)
				Error=-70.0; 
			
			if(Lose_Line==1)
			{
				
				if(Meeting_Area.Direction==Leftside||Meeting_My.State==5)
					Error=-50.0; 
				else if(Meeting_Area.Direction==Rightside&&Meeting_My.State!=5)
					Error=50.0; 
			}
			
			
			if(Meeting_My.Oder==1)
			{
				if(ABS(Error)>=12)
					KP=0.5+(Error* Error)*J/2;//KP
				else
					KP=0.5;
				if(KP>=13) KP=13;//P值限幅
				KD=0.5;
			}
			else
			{
				KP=BasicP+(Error* Error)*J/2;//KP
				KD=0.5;
			}
			
		}
		else
		{
			if(Meeting_Area.Direction==Leftside)
			{
				Error=-(20-Right_AD*1)*2.2;
			}
			else if(Meeting_Area.Direction==Rightside)
			{
				Error=(20-Left_AD*1)*2.2;
			}
			
			KP=2.2;
			KD=1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      舵机控制
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	SteerPwm=SteerMiddle+偏差量
//-------------------------------------------------------------------------------------------------------------------
void Steer_Ctrl()
{
	
	if(!Roundabout.Flag&&!Crossroad.Flag&&!Meeting_My.Find_Track&&Meeting_My.State>1&&!Rampway.Flag)//&&!Crossroad.Flag
		Steer_Error(); 
	else if(Crossroad.Flag)
		Cross_Error();
	else if(Roundabout.Flag)
		Roundabout_Error(); 
	else if(Meeting_My.Find_Track||Meeting_My.State<=1)
		Meeting_Error();
	else if(Rampway.Flag)
		Ramway_Error();
	
	
	//PID计算过程
	SteerPwmAdd=(KP*Error)+KD*(Error-LastError);                      //舵机PID+KD*(Error-LastError)
	SteerPwm=(uint32)(SteerPwmAdd+SteerMiddle);         //舵機PWM
	SteerPwm=SteerPwm>SteerMax?SteerMax:SteerPwm;       //限幅
	SteerPwm=SteerPwm<SteerMin?SteerMin:SteerPwm;
	
	//输出PWM
	ftm_pwm_duty(Steer_ftm,Steer_CH,SteerPwm);//舵機PWM更新
	
	//更新上一次误差 
	LastError=Error;
}