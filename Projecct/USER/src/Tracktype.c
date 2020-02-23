#include "Tracktype.h"

InflectionPoint  InflectionPointL;//建立左边拐点结构体变量
InflectionPoint  InflectionPointR;//建立右边拐点结构体变量
//-------------------------------------------------------------------------------------------------------------------
//  @brief      寻找右拐点
//  @param      右拐点结构体 起始行 截止行
//  @return     void					
//  @since      v1.0
//  Sample usage:    FindInflectionPointR(&InflectionPointR ,90,60);
//-------------------------------------------------------------------------------------------------------------------
void FindInflectionPointR(InflectionPoint *inf ,unsigned char Start ,unsigned char End )
{
	int i;
	inf->Row=0;
	inf->Col=0;
	inf->Flag=0;
	inf->Number=0;
	for(i=Start;i>End;i--)
	{
		if(inf->Flag==0)
		{
			if(RightEdge[i]>0&&RightEdge[i-1]>0&&RightEdge[i+1]>0&&RightEdge[i+2]>0&&
			   RightEdge[i]<ColumnMax-1&&RightEdge[i-1]<ColumnMax-1&&RightEdge[i+1]<ColumnMax-1&&RightEdge[i+2]<ColumnMax-1)
				/*  &&(RightEdge[i]>10&&RightEdge[i-1]>10&&RightEdge[i+1]>10&&RightEdge[i-2]>10)*///RightEdge[i-2]>0&&&&RightEdge[i-2]<ColumnMax-1
			{//三行不丢线
				//右线往右拐
				if(RightEdge[i]-RightEdge[i+1]<=0&&RightEdge[i-1]-RightEdge[i]>0&&(RightEdge[i-2]-RightEdge[i]>0||RightEdge[i-2]==ColumnMax))
				{//下一行偏移 且上一行不偏移 且下两行不丢线
					//找到右边线有拐点
					inf->Row=i;//记录拐点的行
					inf->Col=RightEdge[i];//记录拐点的列
					inf->Flag=1;//标记找到右拐点
					inf->Number=1;
					i=i-5;
				}
			}
			else if(i<120&&RightEdge[i+1]!=ColumnMax&&RightEdge[i]!=ColumnMax
					&&RightEdge[i-1]==ColumnMax&&RightEdge[i-2]==ColumnMax&&RightEdge[i]<133&&RightEdge[i]-RightEdge[i+1]<=0)
				//&&RightEdge[i+2]!=ColumnMax
			{	//连续丢两行 && 边缘不靠近图像边缘
				//找到右边线有拐点
				inf->Row=i;//记录拐点的行
				inf->Col=RightEdge[i];//记录拐点的列
				inf->Flag=1;//标记找到右拐点
				inf->Number=1;
				i=i-5;
			}
			else if(RightEdge[i]>0&&RightEdge[i+1]>0&&RightEdge[i+2]>0
					&&RightEdge[i]<ColumnMax-1&&RightEdge[i+1]<ColumnMax-1&&RightEdge[i+2]<ColumnMax-1
						&&RightEdge[i-1]==ColumnMax&&RightEdge[i-2]>0&&RightEdge[i-2]<ColumnMax-1)
			{
				if(RightEdge[i]-RightEdge[i+1]<=0&&RightEdge[i]-RightEdge[i-2]<0)
				{//下一行丢线 下下行小 比上一行大
					inf->Row=i;//记录拐点的行
					inf->Col=RightEdge[i];//记录拐点的列
					inf->Flag=1;//标记找到右拐点
					inf->Number=1;
					i=i-5;
				}
			}
		}
		
		else if(inf->Flag)
		{
			if(RightEdge[i]>0&&RightEdge[i-1]>0&&RightEdge[i+1]>0&&RightEdge[i+2]>0&&
			   RightEdge[i]<ColumnMax-1&&RightEdge[i-1]<ColumnMax-1&&RightEdge[i+1]<ColumnMax-1&&RightEdge[i+2]<ColumnMax-1)
				/*  &&(RightEdge[i]>10&&RightEdge[i-1]>10&&RightEdge[i+1]>10&&RightEdge[i-2]>10)*///RightEdge[i-2]>0&&&&RightEdge[i-2]<ColumnMax-1
			{//三行不丢线
				//右线往右拐
				if(RightEdge[i]-RightEdge[i+1]<=0&&RightEdge[i-1]-RightEdge[i]>0&&(RightEdge[i-2]-RightEdge[i]>0||RightEdge[i-2]==ColumnMax))
				{//下一行偏移 且上一行不偏移 且下两行不丢线
					inf->Number++;
					i=i-5;
				}
			}
			else if(i<120&&RightEdge[i+1]!=ColumnMax&&RightEdge[i]!=ColumnMax
					&&RightEdge[i-1]==ColumnMax&&RightEdge[i-2]==ColumnMax&&RightEdge[i]<133&&RightEdge[i]-RightEdge[i+1]<=0)
				//&&RightEdge[i+2]!=ColumnMax
			{	//连续丢两行 && 边缘不靠近图像边缘
				inf->Number++;
				i=i-5;
			}
			else if(RightEdge[i]>0&&RightEdge[i+1]>0&&RightEdge[i+2]>0
					&&RightEdge[i]<ColumnMax-1&&RightEdge[i+1]<ColumnMax-1&&RightEdge[i+2]<ColumnMax-1
						&&RightEdge[i-1]==ColumnMax&&RightEdge[i-2]>0&&RightEdge[i-2]<ColumnMax-1)
			{
				if(RightEdge[i]-RightEdge[i+1]<=0&&RightEdge[i]-RightEdge[i-2]<0)
				{//下一行丢线 下下行小 比上一行大
					
					inf->Number++;
					i=i-5;
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      寻找左拐点
//  @param      左拐点结构体 起始行 截止行
//  @return     void					
//  @since      v1.0
//  Sample usage:    FindInflectionPointL(&InflectionPointL ,90,60);
//-------------------------------------------------------------------------------------------------------------------
void FindInflectionPointL(InflectionPoint *inf ,unsigned char Start ,unsigned char End )
{
	int i;
	inf->Row=0;
	inf->Col=0;
	inf->Flag=0;
	inf->Number=0;
	for(i=Start;i>End;i--)
	{
		if(inf->Flag==0)
		{
			if(LeftEdge[i]>0&&LeftEdge[i-1]>0&&LeftEdge[i+1]>0&&LeftEdge[i+2]>0
			   &&LeftEdge[i]<ColumnMax-1&&LeftEdge[i-1]<ColumnMax-1&&LeftEdge[i+1]<ColumnMax-1&&LeftEdge[i+2]<ColumnMax-1)
			  //&&LeftEdge[i-2]>0&&LeftEdge[i-2]<ColumnMax-1
			{//三行不丢线
				if(LeftEdge[i]-LeftEdge[i+1]>=0&&LeftEdge[i-1]-LeftEdge[i]<0&&//&LeftEdge[i]>
				   (LeftEdge[i-2]-LeftEdge[i]<0||LeftEdge[i-2]==0))//找到拐点//&&(LeftEdge[i-2]-LeftEdge[i-1]<0)&&LeftEdge[i-2]<ColumnMax&&LeftEdge[i-2]>0)
				{ //下一行偏移 且上一行不偏移 且下两行不丢线
					inf->Row=i;//记录该拐点的行
					inf->Col=LeftEdge[i];//记录该拐点的列
					inf->Flag=1;//标记找到左拐点
					inf->Number=1;
					i=i-4;
				}
			}
			else if(i<125&&LeftEdge[i+2]!=0&&LeftEdge[i+1]!=0&&LeftEdge[i]!=0
					&&LeftEdge[i-1]==0&&LeftEdge[i-2]==0&&LeftEdge[i]>7&&LeftEdge[i]-LeftEdge[i+1]>=0)//<LeftEdge[i+1]
			{ //连续丢两行 && 边缘不靠近图像边缘
				//找到左边线有拐点
				inf->Row=i;//记录该拐点的行
				inf->Col=LeftEdge[i];//记录该拐点的列
				inf->Flag=1;//标记找到左拐点
				inf->Number=1;
				i=i-4;
			}
			
			else if(LeftEdge[i]>0&&LeftEdge[i+1]>0&&LeftEdge[i+2]>0
					&&LeftEdge[i]<ColumnMax-1&&LeftEdge[i+1]<ColumnMax-1&&LeftEdge[i+2]<ColumnMax-1
						&&LeftEdge[i-1]==0&&LeftEdge[i-2]>0&&LeftEdge[i-2]<ColumnMax-1)
			{ //
				if(LeftEdge[i]-LeftEdge[i+1]>=0&&LeftEdge[i]-LeftEdge[i-2]>=0)
				{//下一行丢线 下下行小 比上一行大
					inf->Row=i;//记录该拐点的行
					inf->Col=LeftEdge[i];//记录该拐点的列
					inf->Flag=1;//标记找到左拐点
					inf->Number=1;
					i=i-4;
				}
			}
		}
		
		else if(inf->Flag)
		{
			if(LeftEdge[i]>0&&LeftEdge[i-1]>0&&LeftEdge[i+1]>0&&LeftEdge[i+2]>0
			   &&LeftEdge[i]<ColumnMax-1&&LeftEdge[i-1]<ColumnMax-1&&LeftEdge[i+1]<ColumnMax-1&&LeftEdge[i+2]<ColumnMax-1)
				//&&LeftEdge[i-2]>0&&LeftEdge[i-2]<ColumnMax-1
			{//三行不丢线
				if(LeftEdge[i]-LeftEdge[i+1]>=0&&LeftEdge[i-1]-LeftEdge[i]<0&&//&LeftEdge[i]>
				   (LeftEdge[i-2]-LeftEdge[i]<0||LeftEdge[i-2]==0))//找到拐点//&&(LeftEdge[i-2]-LeftEdge[i-1]<0)&&LeftEdge[i-2]<ColumnMax&&LeftEdge[i-2]>0)
				{
					inf->Number++;
					i=i-4;
				}
			}
			else if(i<125&&LeftEdge[i+2]!=0&&LeftEdge[i+1]!=0&&LeftEdge[i]!=0
					&&LeftEdge[i-1]==0&&LeftEdge[i-2]==0&&LeftEdge[i]>7&&LeftEdge[i]-LeftEdge[i+1]>=0)//<LeftEdge[i+1]
			{ 
				inf->Number++;
				i=i-4;
			}
			else if(LeftEdge[i]>0&&LeftEdge[i+1]>0&&LeftEdge[i+2]>0
					&&LeftEdge[i]<ColumnMax-1&&LeftEdge[i+1]<ColumnMax-1&&LeftEdge[i+2]<ColumnMax-1
						&&LeftEdge[i-1]==0&&LeftEdge[i-2]>0&&LeftEdge[i-2]<ColumnMax-1)
			{ //
				if(LeftEdge[i]-LeftEdge[i+1]>=0&&LeftEdge[i]-LeftEdge[i-2]>=0)
				{//下一行丢线 下下行小 比上一行大
					inf->Number++;
					i=i-4;
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief              求斜率
//  @param              x轴坐标数组  y轴坐标数组
//  @return             double					
//  @Manufacturer       章锦灶
//  Sample usage:       Slope=get_line_slope(x,y,20)x[n],y[n]
//-------------------------------------------------------------------------------------------------------------------
double Get_Line_Slope(int x[], int y[], int n)
{
	
	int i;                           //斜率
	double numerator=0.0, denominator=0.0;  //分子分母
	double sum_x=0.0,sum_y=0.0;             //x、y的和
	double sum_xx=0.0;                      //x的平方和
	double sum_xy=0.0;                      //xy求和
	double average_x=0.0,average_y=0.0;     //x、y的平均数
	
	for(i=0;i<n;i++)
	{
		sum_xx+=x[i] * x[i]; //x的平方和
		sum_x+=x[i];         //x求和
		sum_y+=y[i];         //y求和
		sum_xy+=x[i]*y[i];   //x*y求和
	} 
	average_x=sum_x/n;
	average_y=sum_y/n;
	
	for(i=0;i<n;i++)
	{
		numerator+=(y[i]-average_y) * (x[i]-average_x);
		denominator+=(x[i]-average_x) * (x[i]-average_x);
	}
	
	if(denominator==0)
		return 0;
	else
		return (numerator/denominator);  //指针斜率
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              计算边线数组
//  @param              0左边线斜率，1右边线斜率，2中线斜率，起始行，截止行
//  @return             double					
//  @Manufacturer       章锦灶
//  Sample usage:       Slope=EdgeSlope(0,100,75)
//-------------------------------------------------------------------------------------------------------------------
double EdgeSlope(uint8 LineMode,int16 ScanStart,int16 ScanEnd)
{

	int32 i,j;
	double Slope=0;
	int SlopeX[100];//斜率X轴数组
	int SlopeY[100];//斜率Y轴数组
	if(LineMode==0)
	{
		for(i=ScanStart,j=0; j<ScanStart-ScanEnd; i--,j++)
		{
			if(LeftEdge[i]!=0)
			{
				SlopeX[j]=LeftEdge[i];
			}
			else
			{
				SlopeX[j]=LeftEdge[i+1];
			}
			SlopeY[j]=i;
		}
		Slope=Get_Line_Slope(SlopeX,SlopeY,ScanStart-ScanEnd);
	}
	else if(LineMode==1)
	{
		for(i=ScanStart,j=0; j<ScanStart-ScanEnd; i--,j++)
		{
			if(RightEdge[i]!=140)
			{
				SlopeX[j]=RightEdge[i];
			}
			else
			{
				SlopeX[j]=RightEdge[i+1];
			}
			SlopeY[j]=i;
		}
		Slope=Get_Line_Slope(SlopeX,SlopeY,ScanStart-ScanEnd);
	}
	else
	{
		for(i=ScanStart,j=0; j<ScanStart-ScanEnd; i--,j++)
		{
			SlopeX[j]=MiddleLine[i];
			SlopeY[j]=i;
		}
		Slope=Get_Line_Slope(SlopeX,SlopeY,ScanStart-ScanEnd);
	}
	return Slope;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              求斜率/截距
//  @param              x轴坐标数组  y轴坐标数组
//  @return             double					
//  @Manufacturer       章锦灶
//  Sample usage:       Slope=get_line_slope(x,y,20)x[n],y[n]
//-------------------------------------------------------------------------------------------------------------------
void get_slope_intercept(int x[],int y[],int n, double *slope_line, double *intercept)
{
	long int i;
	double numerator=0.0, denominator=0.0, sum_x=0.0,sum_y=0.0;
	double sum_xx=0.0; //x的平方和
	double sum_xy=0.0; // xy求和
	double average_x=0.0,average_y=0.0;
	for(i=0;i<n;i++)
	{
		sum_xx+=x[i] * x[i]; //x的平方和
		sum_x+=x[i];         //x求和
		sum_y+=y[i];         //y求和
		sum_xy+=x[i]*y[i];   //x*y求和
	} 
	average_x=sum_x/n;
	average_y=sum_y/n;
	for(i=0;i<n;i++)
	{
		numerator+=(y[i]-average_y) * (x[i]-average_x);
		denominator+=(x[i]-average_x) * (x[i]-average_x);
	}
	
	if(denominator==0)
		*slope_line=0;
	else
		*slope_line=numerator/denominator;  //指针斜率
	
	* intercept=(sum_y-(*slope_line) * sum_x)/n; //指针截距
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              求斜率/截距
//  @param              x轴坐标数组  y轴坐标数组
//  @return             double					
//  @Manufacturer       章锦灶
//  Sample usage:       EdgeSlopeIntercept(right,start,end,&斜率,&截距)
//-------------------------------------------------------------------------------------------------------------------
void EdgeSlopeIntercept(uint8 LineMode,int16 ScanStart,int16 ScanEnd,double *Slope,double *Intercept)
{
	int32 i,j;
	int SlopeX[100];//斜率X轴数组
	int SlopeY[100];//斜率Y轴数组
	if(LineMode==0)
	{
		for(i=ScanStart,j=0; j<ScanStart-ScanEnd; i--,j++)
		{
			if(LeftEdge[i]!=0)
			{
				SlopeX[j]=LeftEdge[i];
			}
			else
			{
				SlopeX[j]=LeftEdge[i+1];
			}
			SlopeY[j]=i;
		}
		get_slope_intercept(SlopeX,SlopeY,ScanStart-ScanEnd,Slope,Intercept);//Slope=Get_Line_Slope();
	}
	else if(LineMode==1)
	{
		for(i=ScanStart,j=0; j<ScanStart-ScanEnd; i--,j++)
		{
			if(RightEdge[i]!=140)
			{
				SlopeX[j]=RightEdge[i];
			}
			else
			{
				SlopeX[j]=RightEdge[i+1];
			}
			SlopeY[j]=i;
		}
		get_slope_intercept(SlopeX,SlopeY,ScanStart-ScanEnd,Slope,Intercept);//Get_Line_Slope2(SlopeX,SlopeY,ScanStart-ScanEnd,&Slope,&Intercept);
	}
	else
	{
		for(i=ScanStart,j=0; j<ScanStart-ScanEnd; i--,j++)
		{
			SlopeX[j]=MiddleLine[i];
			SlopeY[j]=i;
		}
		get_slope_intercept(SlopeX,SlopeY,ScanStart-ScanEnd,Slope,Intercept); //Get_Line_Slope2(SlopeX,SlopeY,ScanStart-ScanEnd,&Slope,&Intercept);
	}
	
}

