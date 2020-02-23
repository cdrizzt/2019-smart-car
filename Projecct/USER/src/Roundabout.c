#include "Roundabout.h"

roundabout Roundabout;            //建立环岛结构体变量
//-------------------------------------------------------------------------------------------------------------------
//  @brief      寻找环岛起始点函数
//  @return     void   start
//  @since      v1.0
//  Sample usage: 输入   &RoundaboutWait      
//-------------------------------------------------------------------------------------------------------------------
void Roundabout_Start(roundabout *prt)//环岛标志位
{
	
	//电感判
	//左环岛
	static uint8 flag;
	if(prt->Mode)
	{
		if(Left_AD+Right_AD>140)
		{
			flag++;
		}
		else
		{
			flag=0;
		}
		if(flag>1&&!InflectionPointR.Flag&&InflectionPointL.Flag&&Left_Quantity>20
		   &&RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[DropRow+1]>73&&RightEdge[RightStart]>133)//&&InflectionPointL.Row-DropRow<18Left_AD+Right_AD<210&&&&AllLoseClose<45
		{
			//小
			if(DropRow<61&&InflectionPointL.Row-DropRow<=7)
			{
				prt->Flag=1;
				prt->Direction=Leftside;
				prt->State=1;
				prt->Wait=0;
				prt->Size=1;
				prt->Distance=0;
				flag=0;
			}
			else
			{
				prt->Flag=1;
				prt->Direction=Leftside;
				prt->State=1;
				prt->Wait=0;
				prt->Size=0;
				prt->Distance=0;
				flag=0;
			}
		}
		//右
		if(flag>1&&InflectionPointR.Flag&&!InflectionPointL.Flag&&Right_Quantity>20
		   &&LeftEdge[InflectionPointR.Row]!=0&&LeftEdge[DropRow+1]<67&&LeftEdge[DropRow+1]>0&&LeftEdge[LeftStart]<7)//&&InflectionPointR.Row-DropRow<18Left_AD+Right_AD<210&&&&AllLoseClose<45
		{
			//大环
			if(DropRow<61&&InflectionPointR.Row-DropRow<=7)
			{
				prt->Flag=1;
				prt->Direction=Rightside;
				prt->State=1;
				prt->Wait=0;
				prt->Size=1;
				prt->Distance=0;
				flag=0;
			}
			else
			{
				prt->Flag=1;
				prt->Direction=Rightside;
				prt->State=1;
				prt->Wait=0;
				prt->Size=0;
				prt->Distance=0;
				flag=0;
			}
		}
	}
	//摄像头判
	else if(!Rampway.Flag)
	{
		double LeftSlope[3]={0};
		double RightSlope[3]={0};
		if(prt->Flag==0&&prt->Number<3)
		{
			if(RightLose+AllLoseClose>24&&InflectionPointR.Flag&&!InflectionPointL.Flag&&InflectionPointR.Row-DropRow<12&&InflectionPointR.Row<80&&InflectionPointR.Row-DropRow>1
			   &&RightEdge[RightStart]>115&&LeftEdge[DropRow+1]<67&&LeftEdge[DropRow+1]>0&&AllLoseClose<45&&RightStart<103&&DropRow>60&&LeftEdge[InflectionPointR.Row]!=0
				   &&RightStart-InflectionPointR.Row>15&&Right_Quantity>20&&Right_Quantity<34)//
			{//右
				LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
				LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
				LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
				if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>75&&LeftSlope[0]>75&&LeftSlope[2]>70&&AllLoseClose<=19)
				{	
					prt->Flag=1;
					prt->Direction=Rightside;
					prt->State=1;
					prt->Wait=0;
					prt->Size=0;
				}
				else if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>50&&LeftSlope[0]>55&&LeftSlope[2]>50&&AllLoseClose>19)
				{	
					prt->Flag=1;
					prt->Direction=Rightside;
					prt->State=1;
					prt->Wait=0;
					prt->Size=0;
				}
			}
			
			
			
			
			if(LeftLose+AllLoseClose>24&&InflectionPointL.Flag&&!InflectionPointR.Flag&&InflectionPointL.Row-DropRow<12&&InflectionPointL.Row<80&&InflectionPointL.Row-DropRow>1
			   &&LeftEdge[LeftStart]<25&&RightEdge[DropRow+1]>73&&AllLoseClose<45&&LeftStart<103&&DropRow>60&&RightEdge[InflectionPointL.Row]!=ColumnMax
				   &&LeftStart-InflectionPointL.Row>15&&Left_Quantity>20&&Left_Quantity<34)//
			{
				RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
				RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
				RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
				if(ABS(RightSlope[0]-RightSlope[1])<18&&ABS(RightSlope[1]-RightSlope[2])<25 &&RightSlope[0]>76&&RightSlope[1]>76&&RightSlope[2]>76&&AllLoseClose<=19)
				{
					prt->Flag=1;
					prt->Direction=Leftside;
					prt->State=1;
					prt->Wait=0;
					prt->Size=0;
					
				}
				else if(ABS(RightSlope[0]-RightSlope[1])<18&&ABS(RightSlope[1]-RightSlope[2])<22&&RightSlope[0]>50&&RightSlope[1]>55&&RightSlope[2]>50&&AllLoseClose>19)
				{
					prt->Flag=1;
					prt->Direction=Leftside;
					prt->State=1;
					prt->Wait=0;
					prt->Size=0;
				}
			}
			//大环岛 左
			if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<92&&RightEdge[DropRow]>78&&DropRow>58&&LeftEdge[LeftStart]<25&&RightEdge[InflectionPointL.Row]!=ColumnMax&&
			   InflectionPointL.Col<31&&RightEdge[DropRow+3]>=78&&InflectionPointL.Row>71&&InflectionPointL.Row-DropRow<18&&AllLoseClose<37)//&&LeftEdge[InflectionPointL.Row-6]==0
			{
				if(RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>77)
				{
					RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
					RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
					RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
					if(ABS(RightSlope[0]-RightSlope[1])<12&&ABS(RightSlope[1]-RightSlope[2])<30&&RightSlope[0]>55&&RightSlope[1]>50)
					{
						prt->Flag=1;
						prt->Direction=Leftside;
						prt->State=1;
						prt->Wait=0;
						prt->Size=1;
						prt->Distance=0;
						//Beep_ON;
					}
				}
			}
			//大环岛 右//
			if(!InflectionPointL.Flag&&InflectionPointR.Flag&&InflectionPointR.Row<92&&LeftEdge[DropRow]<62&&DropRow>58&&RightEdge[RightStart]>115&&LeftEdge[InflectionPointR.Row]!=0&&
			   InflectionPointR.Col>109&&LeftEdge[DropRow+3]<=62&&InflectionPointR.Row>71&&InflectionPointR.Row-DropRow<18&&AllLoseClose<37)//&&RightEdge[InflectionPointR.Row-6]==ColumnMax
			{
				if(LeftEdge[InflectionPointR.Row]!=0&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>77)
				{
					LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
					LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
					LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
					if(ABS(LeftSlope[0]-LeftSlope[1])<12&&ABS(LeftSlope[1]-LeftSlope[2])<30&&LeftSlope[1]>55&&LeftSlope[0]>50)
					{	
						prt->Flag=1;
						prt->Direction=Rightside;
						prt->State=1;
						prt->Distance=0;
						prt->Wait=0;
						prt->Size=1;
						//Beep_ON;
					}
				}
			}
		}
	}
}

/*
	
	}
	/*else if(prt->State==1)
	{
		if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<92&&RightEdge[DropRow]>78&&DropRow>58&&LeftEdge[LeftStart]<25&&RightEdge[InflectionPointL.Row]!=ColumnMax&&
		   InflectionPointL.Col<31&&RightEdge[DropRow+3]>=78&&InflectionPointL.Row>71&&InflectionPointL.Row-DropRow<18&&AllLoseClose<37)//&&LeftEdge[InflectionPointL.Row-6]==0
		{
			if(RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>77)
			{
				RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
				RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
				RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
				if(ABS(RightSlope[0]-RightSlope[1])<12&&ABS(RightSlope[1]-RightSlope[2])<30&&RightSlope[0]>55&&RightSlope[1]>50)
				{
					prt->Flag=1;
					prt->Direction=Leftside;
					prt->State=1;
					prt->Wait=0;
					prt->Size=1;
					prt->Distance=0;
					//Beep_ON;
				}
			}
		}
		//大环岛 右//
		if(!InflectionPointL.Flag&&InflectionPointR.Flag&&InflectionPointR.Row<92&&LeftEdge[DropRow]<62&&DropRow>58&&RightEdge[RightStart]>115&&LeftEdge[InflectionPointR.Row]!=0&&
		   InflectionPointR.Col>109&&LeftEdge[DropRow+3]<=62&&InflectionPointR.Row>71&&InflectionPointR.Row-DropRow<18&&AllLoseClose<37)//&&RightEdge[InflectionPointR.Row-6]==ColumnMax
		{
			if(LeftEdge[InflectionPointR.Row]!=0&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>77)
			{
				LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
				LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
				LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
				if(ABS(LeftSlope[0]-LeftSlope[1])<12&&ABS(LeftSlope[1]-LeftSlope[2])<30&&LeftSlope[1]>55&&LeftSlope[0]>50)
				{	
					prt->Flag=1;
					prt->Direction=Rightside;
					prt->State=1;
					prt->Distance=0;
					prt->Wait=0;
					prt->Size=1;
					//Beep_ON;
				}
			}
		}
	}
*/

//-------------------------------------------------------------------------------------------------------------------
//  @brief      寻找环岛进入点函数
//  @return     void   Entrance
//  @since      v1.0
//  Sample usage: 输入   &RoundaboutWait      
//-------------------------------------------------------------------------------------------------------------------
//uint16 ScanRow[140]={0};
void Roundabout_Entrance(roundabout *prt)		//环岛第二点判断
{
	int i,j;
	//按列查找数组
	static uint8 FLAG;
//			for(i=0;i<140;i++)
//					ScanRow[i]=0;
	uint16 ScanRow[140]={0};
	uint16 left=0,right=0;
	uint16 up=0,down=0;
	if(prt->Direction==Leftside)
	{
		if(prt->State==1)//&&(LeftStart>90||prt->Size||InflectionPointL.Col<15)
		{
			FindInflectionPointL(&InflectionPointL ,LeftStart,DropRow+1);   
			if(InflectionPointL.Flag)
			{
				if(prt->State==1&&RightEndRow)
				{
					down=InflectionPointL.Row;//LeftEndRow<RightEndRow?RightEndRow+8:LeftEndRow+8;
					up=RightEndRow;
//					if(prt->Size)
//					{
//						if(InflectionPointL.Flag)
//							down=InflectionPointL.Row+4;//
//						else
//							down=LeftEndRow<RightEndRow?RightEndRow+10:LeftEndRow+4;
//					}
				}
				for(i=up;i<down;i++)
				{
					right=RightEdge[i]==ColumnMax?(RightEdge[DropRow]-Width[DropRow]/2):(RightEdge[i]-Width[i]/2);
					for(j=right;j>InflectionPointL.Col-4;j--)
					{
						j=j>110?110:j;
						if(Solve_Prewitt(i,j))
						{
							if(j-ScanRow[i-1]>8&&ScanRow[i-1]!=0)
								continue;
							ScanRow[i]=j;
							break;
						}
					}
					if(ScanRow[i-2]!=0&&ScanRow[i-1]!=0&&(ScanRow[i]==0||ScanRow[i-1]-ScanRow[i]>10)&&i<down-1&&ABS(ScanRow[i-2]-ScanRow[i-1]<10)&&ScanRow[i-1]>35)
					{//左
						prt->Row=i-1;
						prt->Col=ScanRow[i-1];
						prt->State=2;
						prt->Distance=0;
						prt->Number++;
						break;
					}
				}
			}
		}
		else if(prt->State==2)
		{
			FindInflectionPointL(&InflectionPointL ,LeftStart,DropRow+1);  
			if(prt->Row<100)
			{
				up=prt->Row-10<RightEndRow+3?RightEndRow+3:prt->Row-10;
				down=prt->Row+20>RowMax-2?RowMax-2:prt->Row+20;
				
				for(i=up;i<down;i++)
				{
					if(RightStart>prt->Row)
					{
						if(i>RightStart-10)
							right=RightEdge[i]==ColumnMax?135:RightEdge[i]-Width[i]/2;
						else
							right=RightEdge[i]==ColumnMax?(RightEdge[DropRow]-Width[DropRow]/2):(RightEdge[i]-Width[i]/2);
					}
					
					else
					{	
						if(i>RightStart)
							right=130;
						else
							right=120;
					}
					for(j=right;j>10;j--)
					{
						if(Solve_Prewitt(i,j))
						{
							if(j-ScanRow[i-1]>8&&ScanRow[i-1]!=0)
								continue;
							ScanRow[i]=j;
							break;
						}
					}
					if(ScanRow[i-3]>prt->Col-10&&ScanRow[i-2]>prt->Col-10&&ScanRow[i-1]<prt->Col-10&&ScanRow[i]<prt->Col-10
					   &&ScanRow[i-2]-ScanRow[i-1]>10)
					{//左
						if(i>=prt->Row&&ABS(ScanRow[i-3]-prt->Col)<40)
						{
							prt->Row=i-3;
							prt->Col=ScanRow[i-3];
							prt->State=2;
						}
						break;
					}
					else if(ABS(ScanRow[i-4]-ScanRow[i-3])<5&&ABS(ScanRow[i-3]-ScanRow[i-2])<5
							&&ScanRow[i-2]>70&&ScanRow[i-3]>70&&ScanRow[i-4]>70&&ScanRow[i-1]<50&&ScanRow[i]<50)
					{
						if(i>=prt->Row&&ABS(ScanRow[i-2]-prt->Col)<40)
						{
							prt->Row=i-2;
							prt->Col=ScanRow[i-2];
							prt->State=2;
							break;
						}
					}
					
					if(ABS(ScanRow[i-4]-ScanRow[i-3])<5&&ABS(ScanRow[i-3]-ScanRow[i-2])<5&&ScanRow[i-4]!=0&&ScanRow[i-3]!=0&&ScanRow[i-2]!=0
					   &&(ScanRow[i-2]-ScanRow[i-1]>15||ScanRow[i-1]==0)&&(ScanRow[i-1]-ScanRow[i]>15||ScanRow[i]==0)&&ScanRow[i-4]>40)
					{
						if(i>=prt->Row&&ABS(ScanRow[i-2]-prt->Col)<40)
						{
							prt->Row=i-2;
							prt->Col=ScanRow[i-2];
							prt->State=2;			
							break;
						}
					}
				}
			}
			else
			{
				for(i=100;i<RowMax-2;i++)
				{
					for(j=20;j<135;j++)
					{
						if(Solve_Prewitt(i,j))
						{
							ScanRow[i]=j;
							break;
						}
					}
					if(ScanRow[i]>130||ScanRow[i]==0||i>125)
					{
						prt->Row=i-1;
						prt->Col=ScanRow[i-1];
						prt->State=2;
						break;
					}
				}
			}
			if((prt->State==2&&prt->Col>110&&prt->Row>85)||(prt->Col>88&&prt->Size==1&&prt->Distance>6000))//||prt->Distance>6000
			{
				uint8 left,mid,right;
				uint8 flag[3]={0};
				for(i=RowMax-2;i>65;i--)
				{
					if(Solve_Prewitt(i,60)&&flag[0]==0)
					{
						left=i;
						flag[0]=1;
					}
					if(Solve_Prewitt(i,70)&&flag[1]==0)
					{
						mid=i;
						flag[1]=1;
					}
					if(Solve_Prewitt(i,ColumnMax-10)&&flag[2]==0)
					{
						right=i;
						flag[2]=1;
					}
					if(left<=mid&&mid<right&&flag[0]&&flag[1]&&flag[2])
					{
						FLAG=1;
					}
				}
			}
		}
	}
	
	else if(prt->Direction==Rightside)
	{
		if(prt->State==1)//&&(RightStart>90||prt->Size||InflectionPointR.Col>125)
		{
			FindInflectionPointR(&InflectionPointR,RightStart,DropRow+1);
			if(InflectionPointR.Flag)
			{
				if(prt->State==1&&LeftEndRow)
				{
					down=InflectionPointR.Row;//LeftEndRow>RightEndRow?LeftEndRow+8:RightEndRow+8;
					up=LeftEndRow;
//					if(prt->Size)
//					{
//						if(InflectionPointR.Flag)
//							down=InflectionPointR.Row+4;//
//						else
//							down=LeftEndRow>RightEndRow?LeftEndRow+10:RightEndRow+4;
//					}
				}
				for(i=up;i<down;i++)
				{
					left=LeftEdge[i]==0?(LeftEdge[DropRow]+Width[DropRow]/2):(LeftEdge[i]+Width[i]/2);
					for(j=left;j<InflectionPointR.Col+4;j++)
					{
						j=j<30?30:j;
						if(Solve_Prewitt(i,j))
						{
							if(j-ScanRow[i-1]>8&&ScanRow[i-1]!=0)
								continue;
							ScanRow[i]=j;
							break;
						}
					}
					if(ScanRow[i-2]!=0&&ScanRow[i-1]!=0&&(ScanRow[i]==0||ScanRow[i]>125)&&i<down-1&&ABS(ScanRow[i-2]-ScanRow[i-1]<10)&&ScanRow[i-1]<105)
					{//右
						prt->Row=i-1;
						prt->Col=ScanRow[i-1];
						prt->State=2;
						prt->Distance=0;
						prt->Number++;
						break;
					}
				}
			}
		}
		else if(prt->State==2)
		{
			FindInflectionPointR(&InflectionPointR,RightStart,DropRow+1);
			if(prt->Row<100)
			{
				up=prt->Row-10<LeftEndRow+3?LeftEndRow+3:prt->Row-10;
				down=prt->Row+20>RowMax-2?RowMax-2:prt->Row+20;
				
				for(i=up;i<down;i++)
				{
					if(LeftStart>prt->Row)
					{
						if(i>LeftStart-10)
							left=LeftEdge[i]==0?4:(LeftEdge[i]+Width[i]/2);
						else
							left=LeftEdge[i]==0?(LeftEdge[DropRow]+Width[DropRow]/2):(LeftEdge[i]+Width[i]/2);
					}
					else
					{
						if(i>LeftStart)
							left=10;
						else
							left=20;
					}
					for(j=left;j<130;j++)
					{
						if(Solve_Prewitt(i,j))
						{
							if(j-ScanRow[i-1]>8&&ScanRow[i-1]!=0)
								continue;
							ScanRow[i]=j;
							break;
						}
					}
					//					if(ScanRow[i-3]<prt->Col+10&&ScanRow[i-2]<prt->Col+10&&(ScanRow[i-1]>prt->Col+10||ScanRow[i-1]==0&&ScanRow[i]>prt->Col+10||ScanRow[i-1]==0)
					//					   &&ScanRow[i-3]!=0&&ScanRow[i-2]!=0)
					if(ScanRow[i-3]<prt->Col+10&&ScanRow[i-2]<prt->Col+10&&((ScanRow[i-1]>prt->Col+10||ScanRow[i-1]==0)&&(ScanRow[i]>prt->Col+10||ScanRow[i-1]==0))
					   &&ScanRow[i-3]!=0&&ScanRow[i-2]!=0
						   &&(ScanRow[i-1]-ScanRow[i-2]>10||ScanRow[i-1]==0))
					{//右
						if(i>=prt->Row&&ABS(ScanRow[i-3]-prt->Col)<50)
						{
							prt->Row=i-3;
							prt->Col=ScanRow[i-3];
							prt->State=2;
						}
						break;
					}
					else if(ABS(ScanRow[i-4]-ScanRow[i-3])<5&&ABS(ScanRow[i-3]-ScanRow[i-2])<5&&ScanRow[i-2]<70&&ScanRow[i-3]!=0&&ScanRow[i-4]!=0
							&&ScanRow[i-2]<70&&ScanRow[i-3]<70&&ScanRow[i-4]<70&&(ScanRow[i-1]>90||ScanRow[i-1]==0)&&(ScanRow[i]>90||ScanRow[i-1]==0))
					{
						if(i>=prt->Row&&ABS(ScanRow[i-2]-prt->Col)<50)
						{
							prt->Row=i-2;
							prt->Col=ScanRow[i-2];
							prt->State=2;	
							break;
						}
					}
					if(ABS(ScanRow[i-4]-ScanRow[i-3])<5&&ABS(ScanRow[i-3]-ScanRow[i-2])<5&&ScanRow[i-4]!=0&&ScanRow[i-3]!=0&&ScanRow[i-2]!=0
					   &&(ScanRow[i-2]-ScanRow[i-1]<-15||ScanRow[i-1]==0)&&(ScanRow[i-1]-ScanRow[i]<-15||ScanRow[i]==0)&&ScanRow[i-4]<110)
					{
						if(i>=prt->Row&&ABS(ScanRow[i-2]-prt->Col)<50)
						{
							prt->Row=i-2;
							prt->Col=ScanRow[i-2];
							prt->State=2;
							break;
						}
					}
				}
			}
			else
			{
				for(i=100;i<RowMax-2;i++)
				{
					for(j=120;j>5;j--)
					{
						if(Solve_Prewitt(i,j))
						{
							ScanRow[i]=j;
							break;
						}
					}
					if(ScanRow[i]<10||i>125)
					{
						prt->Row=i-1;
						prt->Col=ScanRow[i-1];
						prt->State=2;
						break;
					}
				}
			}
			if(prt->State==2&&(prt->Col<30&&prt->Row>85)||(prt->Size==1&&prt->Col<52&&prt->Distance>6000))//||prt->Distance>6000
			{
				uint8 left,mid,right;
				uint8 flag[3]={0};
				for(i=RowMax-2;i>65;i--)
				{
					if(Solve_Prewitt(i,12)&&flag[0]==0)
					{
						left=i;
						flag[0]=1;
					}
					if(Solve_Prewitt(i,70)&&flag[1]==0)
					{
						mid=i;
						flag[1]=1;
					}
					if(Solve_Prewitt(i,80)&&flag[2]==0)
					{
						right=i;
						flag[2]=1;
					}
					if(left>mid&&mid>=right&&flag[0]&&flag[1]&&flag[2])
					{
						FLAG=1;
					}
				}
			}
		}
	}
	
	if(FLAG&&prt->Last_Time||prt->Row>124||prt->Distance>10000)
	{
		prt->State=3;
		prt->Distance=0;
		prt->Last_Time=0;
		FLAG=0;
		InflectionPointR.Flag=0;
		InflectionPointL.Flag=0;
	}
	prt->Last_Time=FLAG;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      环岛内寻找拐点函数
//  @return     void   Insid
//  @since      v1.0
//  Sample usage: 输入   &RoundaboutWait      
//-------------------------------------------------------------------------------------------------------------------
void Roundabout_Inside(roundabout *prt)		//环岛内
{
	char finish=0;
	static uint8 Length=0;
	InflectionPoint *inf;
	
	FindInflectionPointL(&InflectionPointL,LeftStart,DropRow+5);
	FindInflectionPointR(&InflectionPointR,RightStart,DropRow+5);
	if(prt->Direction==Leftside)
	{    
		finish=InflectionPointR.Flag;
		inf=&InflectionPointR;
	}
	else
	{      
		finish=InflectionPointL.Flag;
		inf=&InflectionPointL;
	}
	finish=inf->Flag;
	if(prt->State==3)
	{
		if(prt->Distance>1000)
		{
			Length++;
			prt->Distance=0;
		}
		if(Length>8)
		{
			prt->Size=1;
		}
		if(finish==1&&prt->Last_Time==1&&Length>3&&prt->Last_Time)
		{
			if(Length>15)
			{
				prt->Size=1;
				prt->State=4;
				prt->Distance=0;
				Length=0;
			}
			else
			{
				prt->Size=0;
				prt->State=4;
				prt->Distance=0;
				Length=0;
			}
		}
		
	}
	
	else if(prt->State==4&&prt->Distance>500&&
			((finish==0&&!prt->Last_Time)||((prt->Col>130&&prt->Direction==Leftside)||(prt->Col<10&&prt->Direction==Rightside))))
	{
		prt->State=5;
		prt->Distance=0;
	}
	prt->Last_Time=finish;//
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      出环岛
//  @return     void   Insid
//  @since      v1.0
//  Sample usage: 输入   &RoundaboutWait      
//-------------------------------------------------------------------------------------------------------------------
void Roundabout_Out(roundabout *prt)		//环岛内
{
	if(prt->State==5)
	{
		if(prt->Size)
		{
			if(prt->Direction==Leftside&&(Right_Quantity>=20||Left_Quantity>=18)&&AllLoseClose<=45)
				prt->State=6;
			else if(prt->Direction==Rightside&&(Right_Quantity>=18||Left_Quantity>=20)&&AllLoseClose<=45)
				prt->State=6;
		}
		else
		{
			if(prt->Direction==Leftside&&Right_Quantity>=20)
				prt->State=6;
			else if(prt->Direction==Rightside&&Left_Quantity>=20)
				prt->State=6;
		}
		prt->Wait=0;
	}
	else if(prt->State==6)
	{
		if(prt->Wait==0&&prt->Size==0)
			prt->Wait=30;
		
		prt->Wait++;
		if(prt->Wait>50)
		{
			prt->Wait=0;
			prt->Col=0;
			prt->Row=0;
			prt->State=0;
			prt->Distance=0;
			prt->Flag=0;
			prt->Direction=3;
			prt->Last_Time=0;
			//Beep_OFF;
			prt->Size=0;
		}
		//		InflectionPoint *inf;
		//		if(prt->Direction==Rightside)
		//		{
		//			FindInflectionPointR(&InflectionPointR ,RightStart,RightStart-20);
		//			inf=&InflectionPointR;
		//		}
		//		else
		//		{
		//			FindInflectionPointL(&InflectionPointL ,LeftStart,LeftStart-20);
		//			inf=&InflectionPointL;
		//		}
		//		if(prt->Distance>2000&&(inf->Row>90&&inf->Flag&&(RightStart>100||prt->Direction==Rightside))||(inf->Row>90&&inf->Flag&&(LeftStart>100||prt->Direction==Leftside)))//prt->Wait>6&&
		//		{
		//			prt->Wait=0;
		//			prt->Col=0;
		//			prt->Row=0;
		//			prt->State=0;
		//			prt->Distance=0;
		//			prt->Flag=0;
		//			prt->Direction=3;
		//			prt->Last_Time=0;
		//		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      判断环岛函数
//  @return     void   
//  @since      v1.0
//  Sample usage: 输入   &Roundabout      
//-------------------------------------------------------------------------------------------------------------------
void Judge_Roundabout(roundabout *prt)
{
	if(!prt->Flag)//没有判到环岛前
	{
		prt->State=0;
		Roundabout_Start(prt);
	}
	else//判道环岛后
	{
		switch(prt->State)
		{

		case 1:Roundabout_Entrance(prt); 		break;
		case 2:Roundabout_Entrance(prt); 		break;
		case 3:Roundabout_Inside(prt);			break;
		case 4:Roundabout_Inside(prt); 			break;//Beep_ON;
		case 5:Roundabout_Out(prt);				break;
		case 6:Roundabout_Out(prt);  		    break;//Roundabout_Start(prt);
		} 
		if(prt->State==1)
		{
			prt->Wait++;
			if(prt->Wait>20)
			{
				prt->Wait=0;
				prt->Flag=0;
				prt->State=0;
				prt->Size=0;
			}
		}
		else if(prt->State==2)
		{
			prt->Wait=0;
		}
		if(prt->Flag)
		{//若判到环岛重置十字
			Crossroad.State=0;
			Crossroad.Flag=0;
			Crossroad.Direction=3;
			Rampway.Flag=0;
			Rampway.State=0;
		}
		switch(prt->State)
		{
		case 1:led(LED4,LED_ON);				break;//Beep_ON;
		case 2:led(LED0,LED_ON);				break;//Beep_ON;
		case 3:led(LED1,LED_ON);   	Beep_OFF;		break;
		case 4:led(LED2,LED_ON);						break;
		case 5:led(LED3,LED_ON);		Beep_ON;		break;
		case 6:led(LED_MAX,LED_OFF);	Beep_OFF;		break;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief     环岛补线
//  @return     void   Edge
//  @since      v1.0
//  Sample usage: 输入   &RoundaboutWait      
//-------------------------------------------------------------------------------------------------------------------
void ModifyEdge_Roundabout(roundabout *prt)
{
	int i,j,jj;
	float Initial=0;	        //初值
	float Change_Quantity=0;	//变化量
	int16 Middle=0;
	//uint16 END=0;
	if(prt->State==2)
	{
		prt->Row=prt->Row>138?138:prt->Row;
		prt->Row=prt->Row<1?1:prt->Row;
		prt->Col=prt->Col>138?138:prt->Col;
		prt->Col=prt->Col<1?1:prt->Col;
		
		Initial=(Entrance_Initial-(int)(Entrance_Coefficient*(prt->Row-Entrance_BaseRow)));  //计算变化量初值
		Initial=Initial<Min_Initial?Min_Initial:Initial;            //初值不小于2（直线上每行变化约2）
		if(prt->Direction==Leftside)
		{
			
			for(i=RowMax-3;i>40;i--)
			{
				if(i<=prt->Row)
					RightEdge[i]  = ColumnMax;
				if((LeftStart<prt->Row+20||prt->Row>70)&&prt->Size==0)
				{
					LeftEdge[i]=0;
					LeftStart=0;
				}
			}
			
			RightEdge[prt->Row]=prt->Col;
			Middle=RightEdge[prt->Row]-Width[prt->Row]/2<1?1:RightEdge[prt->Row]-Width[prt->Row]/2;
		}
		else
		{
			
			for(i=RowMax-3;i>40;i--)
			{
				if(i<=prt->Row)
					LeftEdge[i]   = 0;
				if((RightStart<prt->Row+20||prt->Row>70)&&prt->Size==0)
				{
					RightEdge[i]=ColumnMax;
					RightStart=0;
				}
			}
			LeftEdge[prt->Row]=prt->Col;
			Middle=LeftEdge[prt->Row]+Width[prt->Row]/2>ColumnMax-2?ColumnMax-2:LeftEdge[prt->Row]+Width[prt->Row]/2;
		}
		for(i=prt->Row+1;i<138;i++)
		{
			switch(i-prt->Row)
			{
			case 0:		Change_Quantity=Initial;
			case 1:		Change_Quantity=Initial-(Initial/2.8);	break;
			case 2:		Change_Quantity=Initial-(Initial/2.4);	break;
			case 3:		Change_Quantity=Initial-(Initial/2.0);	break;
			case 4:		Change_Quantity=Initial-(Initial/2.0);	break;
			case 5:		Change_Quantity=Initial-(Initial/1.8);	break;
			default:		Change_Quantity=Initial-(Initial/1.6);	break;
			}
			Change_Quantity=Change_Quantity<Min_Initial?Min_Initial:Change_Quantity;
			if(prt->Direction==Leftside)
			{
				RightEdge[i]=RightEdge[i-1]+(int)Change_Quantity>140?140:RightEdge[i-1]+(int)Change_Quantity;
				if((RightEdge[i+1]-RightEdge[i]<3||RightEdge[i]>138)&&i>prt->Row+5)
				{
					if(RightEdge[i]>138)
						RightEdge[i]=138;
					break;
				}
			}
			else
			{
				LeftEdge[i]=LeftEdge[i-1]-(int)Change_Quantity<0?0:LeftEdge[i-1]-(int)Change_Quantity;
				if((LeftEdge[i]-LeftEdge[i+1]<3||LeftEdge[i]<2)&&i>prt->Row+5)
				{   //若补的边线与边界连上了 跳出
					if(LeftEdge[i]<2)
						LeftEdge[i]=2;
					break;
				}
			}
		}
		uint8 flag=1;
		if(prt->Row>70)
		{
			if(Solve_Prewitt(prt->Row,Middle)) 
			{
				DropRow=prt->Row;
				flag=0;
			}
			if(flag)
			{
				for(i=prt->Row-1;i>50;i--)
				{
					uint8 j,jj;
					if(prt->Direction==Leftside)
					{
						if(RightEdge[i+1]!=ColumnMax)
						{
							j = ((RightEdge[i+1]-CLOSE) <= 1)? 1:(RightEdge[i+1]-CLOSE);  
							jj = ((RightEdge[i+1]+FAR) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+FAR);   
							while(j<=jj)
							{
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									Right_Quantity++;
									RightEdge[i]=j;                                        //记录此时的列坐标
									break;   
								}
								j++;
							}
						}
						else
						{
							for(j=Middle;j<prt->Col;j++)
							{	
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									Right_Quantity++;
									RightEdge[i]=j;                                        //记录此时的列坐标
									break;   
								}
							}
						}
						if(RightEdge[i]!=ColumnMax)
						{
							Middle=RightEdge[i]-Width[i]/2<5?5:RightEdge[i]-Width[i]/2;
						}
						if((RightEdge[i]<=35||Solve_Prewitt(i,Middle)||Solve_Prewitt(i-1,Middle)||Solve_Prewitt(i-2,Middle))&&i<120||Middle<10)
						{
							DropRow=i;
							break;
						}
					}
					else if(prt->Direction==Rightside)
					{
						if(LeftEdge[i+1]!=0)
						{
							j = ((LeftEdge[i+1]+CLOSE) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+CLOSE);  
							jj = ((LeftEdge[i+1]-FAR) <= 1)? 1:(LeftEdge[i+1]-FAR);  
							while(j>=jj)
							{
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									Left_Quantity++;
									LeftEdge[i]=j;                                        //记录此时的列坐标
									break;                                      //跳出循环
								}
								j--;
							}
						}
						else
						{
							for(j=Middle;j>prt->Col;j--)
							{
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									Left_Quantity++;
									LeftEdge[i]=j;                                        //记录此时的列坐标
									break;                                      //跳出循环
								}
							}
						}
						if(LeftEdge[i]!=0)
							Middle=LeftEdge[i]+Width[i]/2>135?135:LeftEdge[i]+Width[i]/2;
							if((LeftEdge[i]>=105||Solve_Prewitt(i,Middle)||Solve_Prewitt(i-1,Middle)||Solve_Prewitt(i-2,Middle))&&i<120||Middle>130)
							{
								DropRow=i;
								break;
							}
					}
				}
			}
		}
		else
		{
			DropRow=prt->Row;
		}
		for(i=RowMax-2;i>DropRow;i--)
		{
			if(RightEdge[i]<135&prt->Direction==Leftside)
			{
				RightStart=i;
				break;
			}
			if(LeftEdge[i]>5&&prt->Direction==Rightside)
			{
				LeftStart=i;
				break;
			}
		}
	}
	
	else if(prt->State==3&&((prt->Direction==Rightside&&LeftStart<85)||(prt->Direction==Leftside&&RightStart<85)))
	{
		LeftStart     	= 0;
		RightStart    	= 0;
		//		LeftInfRow		= 0;
		//		LeftInfCol		= 0;		//左边丢线点
		//		RightInfRow		= 0;
		//		RightInfCol		= 0;	//右边丢线点
		LeftEndRow		= 0;
		RightEndRow		= 0;
		Left_Quantity	= 0;
		Right_Quantity	= 0;
		DropRow			= 40;
		for(i=0;i<=140;i++)
		{
			RightEdge[i]  = ColumnMax;
			LeftEdge[i]   = 0;
			
		}
		if(prt->Direction==Rightside)
			Middle=130;
		else
			Middle=10;
		for(i=RowMax-2;i>RowMax-20;i--)
		{	//寻找左边
			for(j=Middle;j>1;j--)
			{
				if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
				{
					Left_Quantity++;
					LeftEdge[i]=j;                                        //记录此时的列坐标
					break;                                      //跳出循环
				}
			}
			//寻找右边
			for(j=Middle;j<ColumnMax-2;j++)
			{	
				if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
				{
					Right_Quantity++;
					RightEdge[i]=j;                                        //记录此时的列坐标
					break;   
				}
			}
			/***************************************/
			if(LeftStart==0&&LeftEdge[i+1]!=0&&LeftEdge[i+2]!=0)  
			{
				LeftStart  = i+2;
			}
			//连续三行不丢线
			if(RightStart==0&&RightEdge[i+1]!=ColumnMax&&RightEdge[i+2]!=ColumnMax)
			{
				RightStart  = i+2;
			}
			/***************************************/
			if(LeftEdge[i]!=0 && RightEdge[i]!=ColumnMax)                           //兩邊都沒有丟線
			{
				Middle= (LeftEdge[i]+RightEdge[i])/2;                       //中线等于左右边界和/2   
			}
			else if(LeftEdge[i]==0 && RightEdge[i]!=ColumnMax)                      //仅左边丢线
			{ 
				if(LeftStart||RightStart)                                     //记录丢左线
				{
					LeftLose++;
				}
				if(Width[i]<=140)//中线=右边界-路宽
					Middle=RightEdge[i]-Width[i]/2;    
				else
					Middle=RightEdge[i]-70;
			}
			else if(LeftEdge[i]!=0 &&RightEdge[i]==ColumnMax)                       //仅丟了右線   
			{
				if(LeftStart||RightStart)                                     //记录丢右线
				{
					RightLose++;
				}
				if(Width[i]<=140)
					Middle=LeftEdge[i]+Width[i]/2;                               //中线=左边界+路宽
				else
					Middle=LeftEdge[i]+70;
			}
			else if(LeftEdge[i]==0 && RightEdge[i]==ColumnMax)                      //兩邊丟線  
			{         
				if(LeftStart||RightStart)                                     //记录丢线
				{
					AllLose++;
				}              
				AllLoseClose++; 
			}
			//			if(LeftEdge[i+1]-LeftEdge[i]>3&&Middle<130)//&&LeftInfRow==0
			//			{
			//				LeftInfCol=LeftEdge[i+1];                //本行丢线
			//				LeftInfRow=i+1; 
			//			}
			//			if(RightEdge[i]-RightEdge[i+1]>3&&RightInfRow==0&&Middle>10)
			//			{
			//				RightInfCol=RightEdge[i+1];            //本行丢线
			//				RightInfRow=i+1;      
			//			}
			Middle = Middle>ColumnMax-2?ColumnMax-2:Middle;
			Middle = Middle<1?1:Middle;
			if(i==RowMax-5)
			{
				if(ABS(Middle-MidPri)<60)
					MidPri=Middle;
			}
		}
		
		/***************************************/
		for(i=RowMax-20;i>DropRow;i--)
		{
			if(LeftEdge[i+1]!=0 && RightEdge[i+1]!=ColumnMax)       //上一行兩邊都沒有丟線 
			{	//先寻找左边
				j = ((LeftEdge[i+1]+CLOSE) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+CLOSE);  
				jj = ((LeftEdge[i+1]-FAR) <= 1)? 1:(LeftEdge[i+1]-FAR);  
				while(j>=jj)
				{
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						Left_Quantity++;
						LeftEdge[i]=j;                                        //记录此时的列坐标
						break;                                      //跳出循环
					}
					j--;
				}
				
				//寻找右边
				j = ((RightEdge[i+1]-CLOSE) <= 1)? 1:(RightEdge[i+1]-CLOSE);  
				jj = ((RightEdge[i+1]+FAR) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+FAR);   
				while(j<=jj)
				{
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						Right_Quantity++;
						RightEdge[i]=j;                                        //记录此时的列坐标
						break;   
					}
					j++;
				}
			}
			else if(LeftEdge[i+1]==0 && RightEdge[i+1]!=ColumnMax)	//丢左边
			{
				//寻找右边
				j = ((RightEdge[i+1]-CLOSE) <= 1)? 1:(RightEdge[i+1]-CLOSE);  
				jj = ((RightEdge[i+1]+FAR) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+FAR);   
				while(j<=jj)
				{
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						Right_Quantity++;
						RightEdge[i]=j;                                        //记录此时的列坐标
						break;   
					}
					j++;
				}
				
				for(j=Middle;j>1;j--)
				{
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						//						if(LeftInfRow&&j<LeftInfCol+TrackArea_Ratio*(LeftInfRow-i))
						//							break;
						Left_Quantity++;
						LeftEdge[i]=j;                                        //记录此时的列坐标
						break;                                      //跳出循环
					}
				}
			}
			else if(LeftEdge[i+1]!=0 && RightEdge[i+1]==ColumnMax)	//丢右边
			{
				//先寻找左边
				j = ((LeftEdge[i+1]+CLOSE) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+CLOSE);  
				jj = ((LeftEdge[i+1]-FAR) <= 1)? 1:(LeftEdge[i+1]-FAR);  
				while(j>=jj)
				{
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						Left_Quantity++;
						LeftEdge[i]=j;                                        //记录此时的列坐标
						break;                                      //跳出循环
					}
					j--;
				}
				
				for(j=Middle;j<ColumnMax-2;j++)
				{	
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						//						if(RightInfRow!=0&&j>RightInfCol-TrackArea_Ratio*(RightInfRow-i))
						//							break;
						Right_Quantity++;
						RightEdge[i]=j;                                        //记录此时的列坐标
						break;   
					}
				}
				
			}
			else if(LeftEdge[i+1]==0 && RightEdge[i+1]==ColumnMax)
			{
				for(j=Middle;j<ColumnMax-2;j++)
				{	
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						//						if(RightInfRow!=0&&j>RightInfCol-TrackArea_Ratio*(RightInfRow-i))
						//							break;
						Right_Quantity++;
						RightEdge[i]=j;                                        //记录此时的列坐标
						break;   
					}
				}
				for(j=Middle;j>1;j--)
				{
					if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
					{
						//						if(LeftInfRow&&j<LeftInfCol+TrackArea_Ratio*(LeftInfRow-i))
						//							break;
						Left_Quantity++;
						LeftEdge[i]=j;                                        //记录此时的列坐标
						break;                                      //跳出循环
					}
				}
			}
			
			
			
			if(LeftEdge[i]!=0 && RightEdge[i]!=ColumnMax)   //沒有丟線的情況下
			{
				Middle=(LeftEdge[i] + RightEdge[i])/2;
			} 
			//丟了右線
			else if(LeftEdge[i]!=0 && RightEdge[i]==ColumnMax)   
			{    
				RightLose++;
				if(Width[i]<=140)
					Middle=LeftEdge[i]+Width[i]/2;                               //中线=左边界+路宽
				else
					Middle=LeftEdge[i]+70;
			}
			//丟了左線
			else if(LeftEdge[i]==0 && RightEdge[i]!=ColumnMax)     
			{      
				LeftLose++;
				if(Width[i]<=140)//中线=右边界-路宽
					Middle=RightEdge[i]-Width[i]/2;    
				else
					Middle=RightEdge[i]-70;
			}
			//兩邊丟線
			else if(LeftEdge[i]==0 && RightEdge[i]==ColumnMax)  
			{         
				AllLose++;
				AllLoseClose++;
			}
			//			if(LeftEdge[i+1]-LeftEdge[i]>3&&LeftInfRow==0&&Middle<110)
			//			{
			//				LeftInfCol=LeftEdge[i+1];                //本行丢线
			//				LeftInfRow=i+1; 
			//			}
			//			if(RightEdge[i]-RightEdge[i+1]>3&&RightInfRow==0&&Middle>30)
			//			{
			//				RightInfCol=RightEdge[i+1];            //本行丢线
			//				RightInfRow=i+1;      
			//			}
			
			
			if(LeftStart==0&&LeftEdge[i+1]!=0&&LeftEdge[i+2]!=0)  
			{
				LeftStart  = i+2;
			}
			//连续三行不丢线
			if(RightStart==0&&RightEdge[i+1]!=ColumnMax&&RightEdge[i+2]!=ColumnMax)
			{
				RightStart  = i+2;
			}
			Middle = Middle>ColumnMax-2?ColumnMax-2:Middle;
			Middle = Middle<2?2:Middle;
			if(LeftEdge[i]>=110||RightEdge[i]<=30|RightEdge[i]-LeftEdge[i]<25||
			   Solve_Prewitt(i-3,Middle))
			{
				DropRow=i;
				break;
			}
		}
	}
	
	else if(prt->State==4)    
	{
		if(prt->Direction==Rightside)
		{
			if(InflectionPointL.Flag!=0)
			{
				prt->Row=InflectionPointL.Row+3>130?130:InflectionPointL.Row;
				prt->Col=LeftEdge[prt->Row+3];
			}
			for(i=prt->Row-3;i>DropRow;i--)
			{
				LeftEdge[i]=0;
				RightEdge[i]=ColumnMax;
			}
			Initial=(LeftEdge[prt->Row+4]-LeftEdge[prt->Row+10])/5;//计算初值
			Initial=Initial<2?2:Initial;
			for(i=prt->Row;i>DropRow;i--)
			{//分区域计算变化量
				if(i<prt->Row&&i>prt->Row-(int)((prt->Row-DropRow)*0.65))
				{
					Change_Quantity=Initial;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.65)&&
				   i>prt->Row-(int)((prt->Row-DropRow)*0.75))
				{
					Change_Quantity=Initial+1;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.75)&&
				   i>prt->Row-(int)((prt->Row-DropRow)*0.9))
				{
					Change_Quantity=Initial+2;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.9)&&
				   i>prt->Row-(int)((prt->Row-DropRow)*0.95))
				{
					Change_Quantity=Initial+3;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.95))
				{
					Change_Quantity=Initial+3;
				}
				
				LeftEdge[i]=LeftEdge[i+1]+(int)Change_Quantity;
				if(LeftEdge[i]>120)
				{
					LeftEdge[i]=120;
					DropRow=i;
					break;
				}
			}
			//	  for(i=RowMax-2;i>DropRow;i--)
			//	  {
			//		if(RightEdge[i]<135)
			//		{
			//		  RightStart=i;
			//		  break;
			//		}
			//	  }
		}
		
		else if(prt->Direction==Leftside)
		{
			if(InflectionPointR.Flag!=0)
			{
				prt->Row=InflectionPointR.Row+3>130?130:InflectionPointR.Row;
				prt->Col=RightEdge[prt->Row+3];
			}
			for(i=prt->Row-3;i>DropRow;i--)
			{
				LeftEdge[i]=0;
				RightEdge[i]=ColumnMax;
			}
			Initial=(RightEdge[prt->Row+10]-RightEdge[prt->Row+4])/5;
			Initial=Initial<2?2:Initial;
			for(i=prt->Row;i>DropRow;i--)
			{
				if(i<prt->Row&&i>prt->Row-(int)((prt->Row-DropRow)*0.65))
				{
					Change_Quantity=Initial;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.65)&&
				   i>prt->Row-(int)((prt->Row-DropRow)*0.75))
				{
					Change_Quantity=Initial+1;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.75)&&
				   i>prt->Row-(int)((prt->Row-DropRow)*0.9))
				{
					Change_Quantity=Initial+2;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.9)&&
				   i>prt->Row-(int)((prt->Row-DropRow)*0.95))
				{
					Change_Quantity=Initial+3;
				}
				if(i<=prt->Row-(int)((prt->Row-DropRow)*0.95))
				{
					Change_Quantity=Initial+3;
				}
				
				RightEdge[i]=RightEdge[i+1]-(int)Change_Quantity;
				if(RightEdge[i]<20)
				{
					RightEdge[i]=20;
					DropRow=i;
					break;
				}
			}
			//	  for(i=RowMax-2;i>DropRow;i--)
			//	  {
			//		if(LeftEdge[i]>5)
			//		{
			//		  LeftStart=i;
			//		  break;
			//		}
			//	  }
		}
	} 
}


/*if(LeftLose+AllLoseClose>25&&InflectionPointL.Flag&&InflectionPointL.Row<90&&!InflectionPointR.Flag&&Right_Quantity>28&&Left_Quantity>30&&ABS(RightStart-LeftStart)<15&&LeftStart>95&&InflectionPointL.Col<25)
{
for(i=MIN(RightStart,LeftStart);i>InflectionPointL.Row;i--)
{
width+=RightEdge[i]-LeftEdge[i];
if(RightEdge[i]==ColumnMax)
break;
		}

if(width>2600&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>65)
{
RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
if(ABS(RightSlope[0]-RightSlope[1])<15&&ABS(RightSlope[1]-RightSlope[2])<22 &&RightSlope[0]>76&&RightSlope[1]>76)
{
prt->Flag=1;
prt->Direction=Leftside;
prt->State=1;
prt->Wait=0;
prt->Size=1;
prt->Distance=0;
			}
		}
	}
//大环岛 左 车体靠环岛一侧
if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<90&&RightLose>4&&InflectionPointL.Col<30&&Left_Quantity>35
&&Right_Quantity>28&&Right_Quantity<45&&LeftStart>110&&LeftStart<125&&InflectionPointL.Col<25)
{
if(RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>85)
{
RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
if(ABS(RightSlope[0]-RightSlope[1])<15&&ABS(RightSlope[1]-RightSlope[2])<22 &&RightSlope[0]>60&&RightSlope[1]>60)
{
prt->Flag=1;
prt->Direction=Leftside;
prt->State=1;
prt->Wait=0;
prt->Size=1;
prt->Distance=0;
			}
		}
	}
if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<90&&RightLose>10&&InflectionPointL.Col<30&&Left_Quantity>25&&Right_Quantity>20&&Left_Quantity+Right_Quantity<68&&LeftStart>110&&RightEdge[DropRow+2]>75&&LeftStart<125)
{//大环岛 左 靠环岛
if(RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>85)
{
RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
if(ABS(RightSlope[0]-RightSlope[1])<15&&ABS(RightSlope[1]-RightSlope[2])<22 &&RightSlope[0]>60&&RightSlope[1]>60)
{
prt->Flag=1;
prt->Direction=Leftside;
prt->State=1;
prt->Wait=0;
prt->Size=1;
prt->Distance=0;
//Beep_ON;
			}
		}
	} 
//车体靠近另一侧 左
if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<90&&AllLoseClose+LeftLose>22&&Right_Quantity>40
&&LeftLose>4&&InflectionPointL.Col<30&&RightEdge[DropRow+3]>75)
{
if(RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>85)
{
RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
if(ABS(RightSlope[0]-RightSlope[1])<15&&ABS(RightSlope[1]-RightSlope[2])<22 &&RightSlope[0]>60&&RightSlope[1]>60)
{
prt->Flag=1;
prt->Direction=Leftside;
prt->State=1;
prt->Wait=0;
prt->Size=1;
prt->Distance=0;
Beep_ON;
			}
		}
	}*/

/*if(RightLose+AllLoseClose>25&&!InflectionPointL.Flag&&InflectionPointR.Flag&&Left_Quantity>28&&Right_Quantity>30&&ABS(RightStart-LeftStart)<15&&RightStart>95&&InflectionPointR.Col>115)
{
for(i=MIN(RightStart,LeftStart);i>InflectionPointR.Row;i--)
{
width+=RightEdge[i]-LeftEdge[i];
if(LeftEdge[i]==0)
break;
		}

if(width>2500&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>68)
{
LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>75&&LeftSlope[0]>75)
{	
prt->Flag=1;
prt->Direction=Rightside;
prt->State=1;
prt->Wait=0;
prt->Size=1;
prt->Distance=0;
			}
		}
	}
//大环岛 右 车体靠环岛一侧
if(!InflectionPointL.Flag&&InflectionPointR.Flag&&LeftLose>4&&InflectionPointR.Col>105&&Right_Quantity>35&&Left_Quantity>28&&Left_Quantity<45&&
RightStart>110&&RightStart<125&&InflectionPointR.Row<90&&InflectionPointR.Col>115)
{

if(LeftEdge[InflectionPointR.Row]!=0&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>85)
{
LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>60&&LeftSlope[0]>60)
{	
prt->Flag=1;
prt->Direction=Rightside;
prt->State=1;
prt->Distance=0;
prt->Wait=0;
prt->Size=1;
			}
		}
	}
if(!InflectionPointL.Flag&&InflectionPointR.Flag&&InflectionPointR.Row<90&&LeftLose>10&&InflectionPointR.Col>105&&
Right_Quantity>25&&Left_Quantity>20&&Left_Quantity+Right_Quantity<68&&RightStart>110&&RightStart<125&&LeftEdge[DropRow+2]<62)
{//大环岛 右 靠 环岛
if(LeftEdge[InflectionPointR.Row]!=0&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>85)
{
LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>60&&LeftSlope[0]>60)
{	
prt->Flag=1;
prt->Direction=Rightside;
prt->State=1;
prt->Distance=0;
prt->Wait=0;
prt->Size=1;
			}
		}
	}

if(!InflectionPointL.Flag&&InflectionPointR.Flag&&InflectionPointR.Row<90&&AllLoseClose+RightLose>22&&Left_Quantity>40
&&RightLose>4&&InflectionPointR.Col<30&&LeftEdge[DropRow+3]<75)
{
if(LeftEdge[InflectionPointR.Row]!=0&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>85)
{
LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>60&&LeftSlope[0]>60)
{	
prt->Flag=1;
prt->Direction=Rightside;
prt->State=1;
prt->Distance=0;
prt->Wait=0;
prt->Size=1;
Beep_ON;
//			}
//		}
//	}*/
//	else if(prt->State==6)
//	{
//		if(prt->Direction==Rightside)
//		{
//			if(InflectionPointL.Flag&&!InflectionPointR.Flag&&InflectionPointL.Row-DropRow<11&&DropRow>60
//			   &&LeftEdge[LeftStart]<25&&RightEdge[DropRow+1]>73&&AllLoseClose<45&&LeftStart<103
//				   &&LeftStart-InflectionPointL.Row>15&&Left_Quantity>20&&Left_Quantity<30)
//			{
//				RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
//				RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
//				RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
//				if(ABS(RightSlope[0]-RightSlope[1])<18&&ABS(RightSlope[1]-RightSlope[2])<25 &&RightSlope[0]>76&&RightSlope[1]>76&&RightSlope[2]>76&&AllLoseClose<=19&&RightSlope[0]<130)
//				{
//					prt->Flag=1;
//					prt->Direction=Leftside;
//					prt->State=1;
//					prt->Wait=0;
//					
//				}
//				else if(ABS(RightSlope[0]-RightSlope[1])<18&&ABS(RightSlope[1]-RightSlope[2])<22&&RightSlope[0]>50&&RightSlope[1]>55&&RightSlope[2]>50&&AllLoseClose>19&&RightSlope[0]<130)
//				{
//					prt->Flag=1;
//					prt->Direction=Leftside;
//					prt->State=1;
//					prt->Wait=0;
//				}
//			}
//			/*//大环岛 左
//			//	if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<90&&
//			//	   ((AllLoseClose+LeftLose>25&&LeftLose>6&&Right_Quantity>24)||(RightLose>10&&Left_Quantity>35&&AllLoseClose>15))&&RightEdge[DropRow]>82&&
//			//		   InflectionPointL.Col<30&&RightEdge[DropRow+3]>85&&InflectionPointL.Row>71&&InflectionPointL.Row-DropRow<18)&&AllLoseClose>15RightStart<127&&
//			//	{*/
//			
//			if(!InflectionPointR.Flag&&InflectionPointL.Flag&&InflectionPointL.Row<102&&RightEdge[DropRow]>78&&DropRow>58&&LeftEdge[LeftStart]<25&&
//			   InflectionPointL.Col<35&&RightEdge[DropRow+3]>83&&InflectionPointL.Row>71&&InflectionPointL.Row-DropRow<20&&AllLoseClose<38)
//			{
//				if(RightEdge[InflectionPointL.Row]!=ColumnMax&&RightEdge[InflectionPointL.Row]-InflectionPointL.Col>77)
//				{
//					RightSlope[0]=ABS(100*EdgeSlope(Rightside,RightStart,RightStart-(RightStart-DropRow)/3));
//					RightSlope[1]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)/3,RightStart-(RightStart-DropRow)*2/3));
//					RightSlope[2]=ABS(100*EdgeSlope(Rightside,RightStart-(RightStart-DropRow)*2/3,DropRow+2));
//					if(ABS(RightSlope[0]-RightSlope[1])<12&&ABS(RightSlope[1]-RightSlope[2])<30&&RightSlope[0]>55&&RightSlope[1]>50)
//					{
//						prt->Flag=1;
//						prt->Direction=Leftside;
//						prt->State=1;
//						prt->Wait=0;
//						prt->Size=1;
//						prt->Distance=0;
//						Beep_ON;
//					}
//				}
//			}
//		}
//		else if(prt->Direction==Leftside)
//		{
//			if(InflectionPointR.Flag&&!InflectionPointL.Flag&&InflectionPointR.Row-DropRow<11&&DropRow>60
//			   &&RightEdge[RightStart]>115&&LeftEdge[DropRow+1]<67&&LeftEdge[DropRow+1]>0&&AllLoseClose<45&&RightStart<103
//				   &&RightStart-InflectionPointR.Row>15&&Right_Quantity>20&&Right_Quantity<30)
//			{//右
//				LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
//				LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
//				LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
//				if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>75&&LeftSlope[0]>75&&LeftSlope[2]>70&&AllLoseClose<=19&&LeftSlope[0]<130)
//				{	
//					prt->Flag=1;
//					prt->Direction=Rightside;
//					prt->State=1;
//					prt->Wait=0;
//				}
//				else if(ABS(LeftSlope[0]-LeftSlope[1])<15&&ABS(LeftSlope[1]-LeftSlope[2])<22&&LeftSlope[1]>50&&LeftSlope[0]>55&&LeftSlope[2]>50&&AllLoseClose>19&&LeftSlope[0]<130)
//				{	
//					prt->Flag=1;
//					prt->Direction=Rightside;
//					prt->State=1;
//					prt->Wait=0;
//				}
//			}
//			/*//大环岛 右//
//			//	if(!InflectionPointL.Flag&&InflectionPointR.Flag&&InflectionPointR.Row<90&&
//			//	   ((AllLoseClose+RightLose>25&&Left_Quantity>24&&RightLose>6)||(LeftLose>10&&Right_Quantity>35&&AllLoseClose>15))&&LeftEdge[DropRow]<58&&
//			//		   InflectionPointR.Col>110&&LeftEdge[DropRow+3]<54&&InflectionPointR.Row>71&&InflectionPointR.Row-DropRow<18)&&AllLoseClose>15LeftStart<127&&*/
//			if(!InflectionPointL.Flag&&InflectionPointR.Flag&&InflectionPointR.Row<102&&LeftEdge[DropRow]<62&&DropRow>58&&RightEdge[RightStart]>115&&
//			   InflectionPointR.Col>105&&LeftEdge[DropRow+3]<57&&InflectionPointR.Row>71&&InflectionPointR.Row-DropRow<20&&AllLoseClose<38)
//			{
//				if(LeftEdge[InflectionPointR.Row]!=0&&InflectionPointR.Col-LeftEdge[InflectionPointR.Row]>77)
//				{
//					LeftSlope[0]=ABS(100*EdgeSlope(Leftside,LeftStart,LeftStart-(LeftStart-DropRow)/3));
//					LeftSlope[1]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)/3,LeftStart-(LeftStart-DropRow)*2/3));
//					LeftSlope[2]=ABS(100*EdgeSlope(Leftside,LeftStart-(LeftStart-DropRow)*2/3,DropRow+2));
//					if(ABS(LeftSlope[0]-LeftSlope[1])<12&&ABS(LeftSlope[1]-LeftSlope[2])<30&&LeftSlope[1]>55&&LeftSlope[0]>50)
//					{	
//						prt->Flag=1;
//						prt->Direction=Rightside;
//						prt->State=1;
//						prt->Distance=0;
//						prt->Wait=0;
//						prt->Size=1;
//						Beep_ON;
//					}
//				}
//			}
//		}
//	}
/*if(prt->Row>73)
		{
			for(i=RowMax-2;i>56;i--)
			{
				if(i<=prt->Row)
				{
					LeftEdge[i]   = 0;
					RightEdge[i]  = ColumnMax;
				}
				else
				{
					if(LeftEdge[i]>RightEdge[i]&&prt->Direction==Leftside)
						LeftEdge[i]   = 0;
					if(LeftEdge[i]>RightEdge[i]&&prt->Direction==Rightside)
						RightEdge[i]  = ColumnMax;
				}
			}
			for(i=prt->Row+5>138?138:prt->Row+5;i>65;i--)
			{
				if(prt->Direction==Rightside)
				{
					if(Solve_Prewitt(i,134))
					{
						END=i;
					}
				}
				else
				{
					if(Solve_Prewitt(i,6))
					{
						END=i;
					}
				}
			}
			if(prt->Row-END>2)
			{
				DropRow=END;
				if(prt->Direction==Rightside)
				{
					Middle=prt->Col+Width[prt->Row]/2;
					for(i=prt->Row;i>DropRow;i--)
					{
						if(LeftEdge[i]==0)
						{
							for(j=Middle;j>1;j--)
							{
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									LeftEdge[i]=j;                                        //记录此时的列坐标
									break;                                      //跳出循环
								}
							}
						}
						else
						{
							j = ((LeftEdge[i+1]+CLOSE) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+CLOSE);  
							jj = ((LeftEdge[i+1]-FAR) <= 1)? 1:(LeftEdge[i+1]-FAR);  
							while(j>=jj)
							{
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									LeftEdge[i]=j;                                        //记录此时的列坐标
									break;                                      //跳出循环
								}
								j--;
							}
						}
						if(LeftEdge[i]!=0)
							Middle=LeftEdge[i]+Width[i]/2;
						if(LeftEdge[i]>=110||Solve_Prewitt(i-3,Middle)||LeftEdge[i]==0)
						{
							DropRow=i;
							break;
						}
					}
				}
				else if(prt->Direction==Leftside)
				{
					Middle=prt->Col+Width[prt->Row]/2;
					for(i=prt->Row;i>DropRow;i--)
					{
						if(RightEdge[i+1]==ColumnMax)
						{
							for(j=Middle;j<ColumnMax-2;j++)
							{	
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									RightEdge[i]=j;                                        //记录此时的列坐标
									break;   
								}
							}
						}
						else if(RightEdge[i+1]!=ColumnMax)
						{
							//寻找右边
							j = ((RightEdge[i+1]-CLOSE) <= 1)? 1:(RightEdge[i+1]-CLOSE);  
							jj = ((RightEdge[i+1]+FAR) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+FAR);   
							while(j<=jj)
							{
								if(Solve_Prewitt(i,j))                                    //若改点为边缘点进入
								{
									RightEdge[i]=j;                                        //记录此时的列坐标
									break;   
								}
								j++;
							}
						}
						if(RightEdge[i]!=ColumnMax)
							Middle=RightEdge[i]-Width[i]/2;
						if(RightEdge[i]<=30||Solve_Prewitt(i-3,Middle)||RightEdge[i]==ColumnMax)
						{
							DropRow=i;
							break;
						}
					}
				}
			}
		}
		else
		{
			DropRow=prt->Row;
		}*/