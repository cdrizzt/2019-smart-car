#include "Electromagnetism.h"
uint16 ad_max_left,ad_min_left;
uint16 ad_max_right,ad_min_right;
uint16 Left_AD,Right_AD;//归一化后
int16 AD_left,AD_right;//真实值
uint8 AD_Normalization_Flag=0;
uint8 Fail;
float Error_AD;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      adcn_ch         选择ADC通道
//  @return     void
//  @since      v1.0
//  Sample usage:         adc_init(ADC0_SE8); 在H中宏定义了左右
//-------------------------------------------------------------------------------------------------------------------
void ADC_init()
{
	adc_init(AD_Left);
	adc_init(AD_Right);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC平均值
//  @param      adcn_ch		位数 	次数
//  @return     void
//  @since      v1.0
//  Sample usage:         adc_init(ADC0_SE8); 在H中宏定义了左右
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_ave(ADCn_Ch adcn_ch,ADC_nbit bit,uint8 N)
{
	uint32 ave = 0;
	uint8 i = N;
	
	while(i--)
	{
		ave += adc_once(adcn_ch,bit);
	}
	
	ave = ave / N;
	
	return (uint16)ave;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      归一化 由拨码开关控制
//  @return     void
//  @since      v1.0
//  Sample usage:      
//-------------------------------------------------------------------------------------------------------------------
void AD_Normalization()
{
	uint32 i;
	uint16 ad_left,ad_right;
	uint16 last_ad_left,last_ad_right;
	if(Switch_2||AD_Normalization_Flag)
	{
		ad_max_left=0; ad_min_left=5;
		ad_max_right=0; ad_min_right=5;
		for(i=0;i<1000;i++)
		{	
			ad_right=adc_ave(AD_Left,ADC_10bit,15);
			ad_left=adc_ave(AD_Right,ADC_10bit,15);
			{//限幅
				if(ad_left>1000)
					ad_left=last_ad_left;
				else
					last_ad_left=ad_left;	 
				
				if(ad_right>1000)
					ad_right=last_ad_right;
				else
					last_ad_right=ad_right;	
			}
			
			if(ad_max_left<ad_left)
			{
				ad_max_left=ad_left;
			}
			if(ad_max_right<ad_right)
			{
				ad_max_right=ad_right;
			}
			
			systick_delay_ms(5);
		}
		Beep_ON;
		while(FLASH_EraseSector(254));	//擦除扇区
		systick_delay_ms(10);
		while(FLASH_EraseSector(253));	//擦除扇区
		systick_delay_ms(10);
		while(FLASH_WriteSector(254,(const uint8 *)&ad_max_right,16,0));
		systick_delay_ms(5);
		while(FLASH_WriteSector(253,(const uint8 *)&ad_max_left,16,0));
		systick_delay_ms(5);
		Beep_OFF;
		AD_Normalization_Flag=0;
	}
	else
	{
		ad_min_left=5;  ad_min_right=5;
		uint8 number=5;
		for(i=0;i<number;i++)
		{
			ad_max_right+=flash_read(254,0,uint16);
			ad_max_left+=flash_read(253,0,uint16);
		}
		ad_max_right=ad_max_right/(number);
		ad_max_left=ad_max_left/(number);
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取电感值
//  @return     void
//  @since      v1.0
//  Sample usage:      
//-------------------------------------------------------------------------------------------------------------------
void Read_ADC()
{
	uint16 i,j;
	int32 ad_right[5],ad_left[5];
	int32 temp;
	static uint8 time;
	static float sensor_to_one;
	
	for(i=0;i<5;i++)
	{
		ad_right[i]=adc_ave(AD_Left,ADC_10bit,15);
		ad_left[i]=adc_ave(AD_Right,ADC_10bit,15);
	}
	
	for(i=0;i<4;i++)
		for(j=0;j<4-i;j++)
		{
			if(ad_right[j]>ad_right[j+1])
			{
				temp=ad_right[j+1];
				ad_right[j+1]=ad_right[j];
				ad_right[j]=temp;
			}
			if(ad_left[j]>ad_left[j+1])
			{
				temp=ad_left[j+1];
				ad_left[j+1]=ad_left[j];
				ad_left[j]=temp;
			}
		}
	AD_left=(ad_left[1]+ad_left[2]+ad_left[3])/3;
	AD_right=(ad_right[1]+ad_right[2]+ad_right[3])/3;
	if(AD_right+AD_left<2)
	{
		time++;
	}
	else
	{
		time=0;
	}
	if(time>10)
	{
		while(1)
		{
			led(LED_MAX,LED_ON);
			RSpeedSet=0;
			LSpeedSet=0;
//			Fail=1;
//			//Meeting_My.Send_Flag=1;
//			Communication_Accept(&Meeting_My,&Meeting_Other);
//			if(Meeting_My.Send_Flag)
//				Communication_Send(&Meeting_My,&Meeting_Other);
//			Beep_OFF;
//			Display();
		}
	}

	Fail=0;
	sensor_to_one=(float)(AD_right-ad_min_right)/(float)(ad_max_right-ad_min_right);
	if(sensor_to_one<=0.01)
		sensor_to_one=0.01;
	Right_AD=(uint16)(sensor_to_one*100);
	
	sensor_to_one=(float)(AD_left-ad_min_left)/(float)(ad_max_left-ad_min_left);
	if(sensor_to_one<=0.01)
		sensor_to_one=0.01;
	Left_AD=(uint16)(sensor_to_one*100);
	
	//Error_AD=(float)20*(Left_AD-Right_AD)/(Right_AD+Left_AD);
}