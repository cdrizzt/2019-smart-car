#include "Zebra_Line.h"


zebracrossing ZebraCrossing;

/*******************************************************************************
函数名称：Find_ZebraCrossingLine
函数功能：寻找斑马线 可行！！
输出：0-未检测到斑马线  1-检测到斑马线
*******************************************************************************/ 
//-------------------------------------------------------------------------------------------------------------------
//  @brief      寻找斑马线
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	StartRow EndRow
//-------------------------------------------------------------------------------------------------------------------
void Judge_ZebraCrossing(zebracrossing *prt)
{
	int i,j;
	uint8 Line=0;
	uint8 LineLast=0;
	uint8 LineLastLast=0;
	uint8 times=0;
	uint8 flag=0;
	
	uint16 StartCol=0;
	uint16 EndCol=0;
	if(DropRow>=95&&prt->StartRow<115&&prt->Second_Flag==0)//有问题&&LeftStart>118&&LeftEdge[DropRow]<100&&
	{
		for(i=DropRow+10>RowMax-2?RowMax-2:DropRow+10;i>=70;i--)
		{
			times=0;
			Line=0;
			if(!flag)
			{
				StartCol=LeftEdge[i]==0?LeftEdge[DropRow+1]+3:LeftEdge[i]+2;
				EndCol=StartCol+30>135?135:StartCol+30;
				for(j=StartCol;j<EndCol;j++)
				{
					if(Solve_Prewitt(i,j))
					{
						times++;
						
						if(times>3)
						{
							prt->StartRow=i+1;
							prt->Flag=1;
							flag=1;
							Line=1;
							break;
						}
					}
				}
			}
			if(flag)
			{
				StartCol=LeftEdge[prt->StartRow]+3;
				EndCol=StartCol+30>135?135:StartCol+30;
				for(j=StartCol;j<EndCol;j++)
				{
					if(Solve_Prewitt(i,j))
					{
						times++;
						
						if(times>3)
						{
							Line=1;
							break;
						}
					}
				}
				if(Line==0&&LineLast==0&&LineLastLast==1&&i<prt->StartRow-7)
				{
					prt->EndRow=i;
					break;
				}
				LineLastLast=LineLast;
				LineLast=Line;
			}
			
		}
	}
	else if(prt->Flag==1)
	{
		prt->Second_Flag=1;
		for(i=RowMax-2;i>115;i--)
		{
			times=0;
			for(j=75;j<100;j++)
			{
				if(Solve_Prewitt(i,j))
				{
					times++;
					
					if(times>2)
					{
						prt->StartRow=i;
						flag=1;
						break;
					}
				}
			}
			if(flag)
				break;
		}
		if(flag)
		{
			for(i=prt->StartRow-1;i>85;i--)
			{
				Line=0;
				times=0;
				for(j=75;j<120;j++)
				{
					if(Solve_Prewitt(i,j))
					{
						times++;
						if(times>2)
						{
							Line=1;
							break;
						}
					}
				}
				if(Line==0&&LineLast==0&&LineLastLast==1)
				{
					prt->EndRow=i;
					LeftStart=i;
					break;
				}
				LineLastLast=LineLast;
				LineLast=Line;
			}
		}
		else if(prt->StartRow>RowMax-5)
		{
			prt->Flag=0;
			prt->StartRow=0;
			prt->EndRow=0;
			prt->Second_Flag=0;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      寻找中间斑马线  只在第四阶段执行
//  @param      NULL 
//  @return     void					
//  @since      v1.0
//  Sample usage:	StartRow EndRow
//-------------------------------------------------------------------------------------------------------------------
void Judge_MiddleZebraCrossing(zebracrossing *prt)
{
	int i,j;
	uint8 Line=0;
	static uint8 Last_Line,LastLast_Line;
	uint8 times=0;
	if(DropRow>78&&LeftEdge[DropRow+3]!=0&&RightEdge[DropRow+3]!=ColumnMax)
	{
		for(i=DropRow;i>DropRow-6;i--)
		{
			for(j=LeftEdge[DropRow+3]+4;j<RightEdge[DropRow+3]-4;j++)
			{
				if(Solve_Prewitt(i,j))
				{
					times++;
					if(times>7)
					{
						times=0;
						Line=1;
						break;
					}
				}
			}
		}
	}
	if(Line&&Last_Line&&LastLast_Line)
	{
		prt->Flag=1;
	}
	LastLast_Line=Last_Line;
	Last_Line=Line;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      斑马线补线
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	StartRow EndRow
//-------------------------------------------------------------------------------------------------------------------
void ModifyEdge_ZebraCrossing(zebracrossing *prt)
{
	int16 Middle,Left;
	int i,j,jj;
	if(prt->EndRow>80)
	{
		if(prt->Second_Flag)
		{
			Middle=110;
			Left=60;
			for(i=RowMax-2;i>40;i--)
			{
				RightEdge[i]  = ColumnMax;
				LeftEdge[i]   = 0;
			}
		}
		else
		{
			Middle=LeftEdge[prt->StartRow+2]+10>115?115:LeftEdge[prt->StartRow+2]+10;
			Left=LeftEdge[prt->StartRow+2]-5<50?50:LeftEdge[prt->StartRow+2]-5;
		}
		for(i=prt->EndRow-1;i>75;i--)
		{
			if(i==prt->EndRow-1)
			{
				for(j=Middle;j>Left;j--)
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
				if(LeftEdge[i+1]==0)
				{
					for(j=Middle;j>Left;j--)
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
					j = ((LeftEdge[i+1]+10) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);  
					jj = ((LeftEdge[i+1]-10) <= 1)? 1:(LeftEdge[i+1]-10);  
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
			}
			/*计算中线*/
			{
				if(LeftEdge[i]!=0)
				{
					Middle=LeftEdge[i]+Width[i]/4>120?120:LeftEdge[i]+Width[i]/4;
					Left=LeftEdge[i]-10<1?1:LeftEdge[i]-10;
				}
				if(LeftStart==0&&LeftEdge[i+1]!=0&&LeftEdge[i+2]!=0)  
				{
					LeftStart  = i+2;
				}
				if(i==RowMax-5)
				{
					if(ABS(Middle-MidPri)<50)
						MidPri=Middle;
				}
				if(LeftEdge[i]>=125||Solve_Prewitt(i-5,Middle)||Middle-LeftEdge[i]<4&&i<110&&i==76)
				{
					DropRow=i;
					break;
				}
			}
		}
	}
}

