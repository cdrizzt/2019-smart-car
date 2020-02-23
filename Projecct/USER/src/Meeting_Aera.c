#include "Meeting_Aera.h"

meeting_area Meeting_Area;
meeting Meeting_My;
meeting	Meeting_Other;
uint8 Mode=0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      会车区识别 
//  @return     void   Insid
//  @since      v1.0
//  Sample usage: 输入   &Meeting_Area     
//-------------------------------------------------------------------------------------------------------------------
void Judge_Meetingarea(meeting_area *prt)
{
	int i;

//	for(i=0;i<140;i++)
//		one_oder[i]=0;
	int16 one_oder[140]={0};
	uint16 Turnback_RightRow=0;
	uint16 Turnback_LeftRow=0;
	uint8 flag1=0,flag2=0;
	InflectionPoint *inf;
	int16 end=0;
	if(InflectionPointR.Flag&&InflectionPointR.Row>82&&InflectionPointR.Row<135&&Right_Quantity>35&&Left_Quantity-Right_Quantity<20&&InflectionPointR.Col<130)
	{
		inf=&InflectionPointR;
		end=inf->Row-17<DropRow?DropRow:inf->Row-17;
		end=end<40?40:end;
		for(i=inf->Row;i>end;i--)
		{
			if(RightEdge[i]-inf->Col<-1)
			{
				Turnback_RightRow=i;
				break;
			}
			if((RightEdge[i]==ColumnMax&&RightEdge[i+1]==ColumnMax)||(RightEdge[i]==ColumnMax&&RightEdge[i+2]==ColumnMax))
			{
				break;
			}
		}
		
		if(Turnback_RightRow&&Turnback_RightRow-DropRow>8)
		{
			for(i=Turnback_RightRow;i>Turnback_RightRow-8;i--)
			{
				if(RightEdge[i+1]!=ColumnMax&&RightEdge[i]!=ColumnMax)
					one_oder[i]=RightEdge[i+1]-RightEdge[i];
				if(one_oder[i]>3)
				{
					flag1=1;	
				}
				if(RightEdge[i]>RightEdge[Turnback_RightRow])
				{
					flag2=1;
				}
			}
		}
		
	}
	
	if(InflectionPointL.Flag&&InflectionPointL.Row>82&&InflectionPointL.Row<135&&Left_Quantity>35&&Right_Quantity-Left_Quantity<20&&InflectionPointL.Col>10)
	{
		inf=&InflectionPointL;
		end=inf->Row-17<DropRow?DropRow:inf->Row-17;
		end=end<40?40:end;
		for(i=inf->Row;i>end;i--)
		{
			if(LeftEdge[i]-inf->Col>1)
			{
				Turnback_LeftRow=i;
				break;
			}
			if((LeftEdge[i]==0&&LeftEdge[i+1]==0)||(LeftEdge[i]==0&&LeftEdge[i+2]==0))
			{
				break;
			}
		}
		
		if(Turnback_LeftRow&&Turnback_LeftRow-DropRow>8)
		{
			for(i=Turnback_LeftRow;i>Turnback_LeftRow-8;i--)
			{
				if(LeftEdge[i+1]!=0&&LeftEdge[i]!=0)
					one_oder[i]=LeftEdge[i+1]-LeftEdge[i];
				if(one_oder[i]<-3)
				{
					flag1=1;	
				}
				if(LeftEdge[i]<LeftEdge[Turnback_LeftRow])
				{
					flag2=1;
				}
			}
		}
		
	}
	if(flag1&&!flag2)
	{
		prt->Flag=1;
		prt->Start_Flag=0;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      会车判断
//  @return     void   Insid
//  @since      v1.0
//  Sample usage: 输入   &Meeting_My &Meeting_Other   
//-------------------------------------------------------------------------------------------------------------------
void Judge_Meeting(meeting *my,meeting *other,meeting_area * area)
{
	static int Last_time=0;
	static int Last_flag=0;
	
	if(Switch_6)
		area->Direction=Leftside;
	else
		area->Direction=Rightside;
	
	if(Switch_7==0)
		my->Track_Mode=1;	//1用电感 0不用电感
	else
		my->Track_Mode=0;	//1用电感 0不用电感
	
	if(Switch_8==0)
		area->Mode=1;	//1弯道 0直道
	else
		area->Mode=0;	//1弯道 0直道
	
	switch(my->State)
	{
	case 0:
		{
			Distance_StartFlag=0;
			ZebraCrossing.Start_Flag=1;
			my->Find_Track=1;
			if(ZebraCrossing.Flag&&ZebraCrossing.StartRow>110)
			{
				my->State=1;
				my->Flag=1;
			}

			break;
		}
	case 1:
		{
			//Beep_ON;
			if(other->Flag==0&&other->State<2)
				my->Stop_Flag=1;
			else
				my->Stop_Flag=0;
			
			if((Last_time==0&&ZebraCrossing.Flag==0)||other->State==2||other->Flag)//当跨过终点线后
			{
				my->End=1;
			}
			
			if(my->End)//延时消除标志位 电机先动 舵机再动 防止相撞
			{
				my->Wait_Time++;
				if(my->Wait_Time>15)
				{
					//进入下一阶段
					my->State=2;
					//清空所有标志位
					my->Flag=0;
					my->End=0;
					my->Wait_Time=0;
					my->Stop_Flag=0;
					my->Find_Track=0;
					my->Brake=0;
					my->Oder=0;
					my->Electric=0;
					// 清空斑马线标志
					ZebraCrossing.Flag=0;			//标志位
					ZebraCrossing.Start_Flag=0;		//起始寻找标志位
					ZebraCrossing.StartRow=0;  		//起始行
					ZebraCrossing.EndRow=0;    		//结束行
					ZebraCrossing.Second_Flag=0;	//停止巡线
					//Beep_OFF;
				}
			}
			break;
		}
	case 2:
		{
			//Beep_OFF;
			if(area->Start_Flag==0)//延时判定会车区和十字
			{
				my->Wait_Time++;
				if(my->Wait_Time>300)
				{
					my->Wait_Time=0;
					area->Start_Flag=1;
				}
				if(my->Wait_Time>10&&Crossroad.Start_Flag==0)
				{
					Crossroad.Start_Flag=1;
				}
			}
			
			if(area->Flag)//判断到会车区后将标志位置3
			{
				Crossroad.Start_Flag=0;//会车区内不判十字
				my->Flag=1;
				my->State=3;
				
				if(area->Mode==0)
				{
					if(other->Flag)
					{
						my->Oder=2;
						my->Brake=1;
					}
					else
					{
						my->Oder=1;
						my->Brake=1;
					}
				}
				else
				{
					if(other->Flag)
					{
						my->Oder=2;
						my->Brake=2;
					}
					else
					{
						my->Oder=1;
						my->Brake=2;
					}
				}

				my->Find_Track=0;
				
				//清空会车区标志位
				area->Start_Flag=0;
				area->Flag=0;
			}
			break;
		}
	case 3:
		{
			
#if (CarMode==AE86)
			if(my->Oder==1&&other->Oder==1)
			{
				my->Oder=2;
				my->Send_Flag=0;
			}
#endif
			//会车前 刹车延时
			Distance_StartFlag=1;//测距模块启动;
			if(my->Find_Track==0&&my->End==0)
			{
				my->Wait_Time++;
				if(my->Wait_Time>2)
				{
					my->Wait_Time=0;
					my->Find_Track=1;
					
				}
			}

			//会车中
			if(area->Mode==0)//直道模式
			{
				if(my->Find_Track)
				{
					if(my->Oder==1)
					{
						if(other->State<3)
							my->Stop_Flag=1;
						else 
						{
							my->Stop_Flag=0;
							//my->Wait_Time++;
							if((my->Distance<7&&my->Distance>0)||my->Wait_Time>70)
							{
								my->End=1;
								my->Wait_Time=0;
							}
						}	
					}
					else if(my->Oder==2)
					{
						if(my->Brake==0&&my->Distance<7&&my->Distance>0)
						{
							my->End=1;
							my->Wait_Time=0;
							
						}
					}
				}
				
				//消位 车子先延边缘跑一小段
				if(my->End||other->State>3)
				{
					my->Wait_Time++;
					if(my->Wait_Time>11||my->Distance>=7||other->State>3||my->Distance<4)//my->Wait_Time>1||
					{
						//进入下一阶段
						my->State=4;
						//清空所有标志位
						my->Flag=0;
						my->End=0;
						my->Wait_Time=0;
						my->Stop_Flag=0;
						my->Brake=0;
						my->Find_Track=0;
						my->Electric=0;
						
						area->Start_Flag=0;
						area->Flag=0;
						
						Distance_StartFlag=0;
						my->Distance=0;
						
					}
				}
			}
			else	//弯道
			{
				if(my->Find_Track)
				{
					if(my->Oder==1)
					{
						if(other->State<3)
							my->Stop_Flag=1;
						else 
						{
							my->Stop_Flag=0;
							//my->Wait_Time++;
							if((my->Distance<6&&my->Distance>0)||my->Wait_Time>70)
							{
								my->End=1;
								my->Wait_Time=0;
							}
						}	
					}
					else if(my->Oder==2)
					{
						if(my->Brake==0&&my->Distance<6&&my->Distance>0)
						{
							my->End=1;
							my->Wait_Time=0;
							
						}
					}
				}
				
				//消位 车子先延边缘跑一小段
				if(my->End||other->State>3)
				{
					//my->Wait_Time++;
					if(my->Wait_Time>40||my->Distance>=6||other->State>3)
					{
						//进入下一阶段
						my->State=4;
						//清空所有标志位
						my->Flag=0;
						my->End=0;
						my->Wait_Time=0;
						my->Stop_Flag=0;
						my->Brake=0;
						my->Find_Track=0;
						my->Electric=0;
						
						area->Start_Flag=0;
						area->Flag=0;
						
						Distance_StartFlag=0;
						my->Distance=0;
						
					}
				}
			}
			break;
			
		}
	case 4:
		{
			//Beep_OFF;
			if(area->Start_Flag==0)
			{
				my->Wait_Time++;
				if(my->Wait_Time>300)
				{
					my->Wait_Time=0;
					area->Start_Flag=1;
				}
				if(my->Wait_Time>10&&Crossroad.Start_Flag==0)
				{
					Crossroad.Start_Flag=1;
				}
			}
			if(area->Flag)
			{
				my->State=5;
				my->Flag=1;
				// 清空斑马线标志
				ZebraCrossing.Flag=0;			//标志位
				ZebraCrossing.Start_Flag=0;		//起始寻找标志位
				ZebraCrossing.StartRow=0;  		//起始行
				ZebraCrossing.EndRow=0;    		//结束行
				ZebraCrossing.Second_Flag=0;	//停止巡线
				if(other->State<6)
				{
					my->Brake=2;
					my->Oder=1;
				}
				else
				{
					my->Oder=1;
					my->Brake=2;
				}
				//my->Brake=2;

				area->Start_Flag=0;
				area->Flag=0;
			}
			
			break;
		}
	case 5:
		{
#if (CarMode==AE86)
			if(my->Oder==1&&other->Oder==1&&other->State==5)
			{
				my->Oder=2;
				my->Send_Flag=0;
			}
#endif

			if(my->Find_Track==0&&my->End==0)
			{
				my->Wait_Time++;
				if(my->Wait_Time>22)
				{
					my->Wait_Time=0;
					my->Find_Track=1;
					ZebraCrossing.Start_Flag=1;
					//Distance_StartFlag=1;//测距模块启动;
				}
			}
			
			
//			if(my->Brake==0)
//			{
//				
//				//Distance_StartFlag=1;
//				//bmy->Distance=0;
//			}
			
			if(ZebraCrossing.Flag)
			{
				my->State=6;
				my->Stop_Flag=1;
				my->Brake=0;
				my->End=0;
				my->Wait_Time=0;
				
				if(other->State<6)
				{
					my->Oder=1;
					my->Send_Flag=1;
				}
				else
					my->Oder=2;
			}
			break;
		}
	case 6:
		{		
#if (CarMode==AE86)
			if(my->Oder==1&&other->Oder==1&&other->State==6)
			{
				my->Oder=2;
				my->Send_Flag=0;
			}
#endif
			
			if(other->State>=6&&my->End==0)
			{
				//my->Flag=1;
				if(my->Oder==1&&other->Oder==2)
				{
					my->Wait_Time=0;
					my->Stop_Flag=0;
					my->End=1;
				}
				else if(my->Oder==2&&other->Oder==1)
				{
					my->Wait_Time++;
					if(my->Wait_Time>15)
					{
						my->Stop_Flag=0;
						my->Wait_Time=0;
						my->Send_Flag=1;
						my->End=1;
					}
				}
//				else
//				{
//					my->Wait_Time=0;
//					my->Stop_Flag=0;
//					my->End=1;
//				}
			}
			
			if(my->End)
			{
				my->Wait_Time++;
				if(my->Wait_Time>35)//&&ZebraCrossing.Flag==0
				{
					//my->Flag=0;
					my->State=7;
					my->Brake=0;
					my->End=0;
					my->Stop_Flag=1;
					my->Wait_Time=0;
					Beep_OFF;
					//my->Oder=0;
					my->Send_Flag=0;
				}
			}
			break;
		}
	case 7:
		{
			
			while(1)
			{
				my->Flag=1;
				Speed_Set();
				Display();   
			}
			break;
		}
	}
	if(my->Flag!=Last_flag&&my->Send_Flag==0)
	{
		my->Send_Flag=1;
		if(my->State==4||my->State==5||my->State==3)
		{
			Reduce_ADD=1;
		}
	}
	Last_time=ZebraCrossing.Flag;
	Last_flag=my->Flag;
	
}
