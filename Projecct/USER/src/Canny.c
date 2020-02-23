#include "Canny.h"

int Solve_Prewitt(int i,int j)
{
	uint8 Black;
	if(i>=110)//分区阈值
		Black=BlackPoint[0];
	if(i<110&&i>=80)
		Black=BlackPoint[1];
	if(i<80&&i>=60)
		Black=BlackPoint[2];
	if(i<60)
		Black=BlackPoint[3];
	if(image[i][j]<Black)
	{
		uint32 prewitt=0;
		uint16 threshold;
		int16 Gx=0,Gy=0;
		//Prewitt卷积算子
		Gx=(image[i+1][j-1]+image[i+1][j]+image[i+1][j+1])-(image[i-1][j-1]+image[i-1][j]+image[i-1][j+1]);
		Gy=(image[i+1][j+1]+image[i-1][j+1]+image[i][j+1])-(image[i+1][j-1]+image[i-1][j-1]+image[i][j-1]);
		//旧滤光斑程序
		/*int x,y;
		char prewittflag=0;
		//	for(x=-1;x<2;x++)//滤去光班 在光班附近没有黑点 //光班附近点较亮
		//	{
		//		for(y=-1;y<2;y++)
		//		{
		//			if(image[i+x][j+y]>Brightest)
		//			{ 
		//				prewittflag++;
		//				if(prewittflag>=1)
		//				{     
		//					break;
		//				}
		//			}
		//		}
		//		if(prewittflag>=1)
		//		{     
		//			break;
		//		}
		//	}*/
		
		prewitt=Gx*Gx+Gy*Gy;
		
		if(i>=110)//分区阈值
			threshold=Preset_Threshold[0];
		if(i<110&&i>=80)
			threshold=Preset_Threshold[1];
		if(i<80&&i>=60)
			threshold=Preset_Threshold[2];
		if(i<60)
			threshold=Preset_Threshold[3];
		if(prewitt>threshold)//&&prewittflag<1
			return 1;
		else
			return 0;
	}
	else
		return 0;
	
	
	
}