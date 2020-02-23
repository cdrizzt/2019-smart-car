#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模块初始化函数
//  @return     void   
//  @since      v1.0
//  Sample usage:               初始换所有模块
//-------------------------------------------------------------------------------------------------------------------
void HardWare_Init(void)
{
	DisableInterrupts;                  //关闭所有中断进行初始化
	get_clk();                          //上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
	
	Steer_Init();                       //舵机初始化 FTM3
	Motor_Init();						//电机初始化 FTM0 1000
	Switch_Init();                      //拨码开关初始化
	Speed_Level();
	Buzzer_Init();                      //蜂鸣器初始化
	led_init(LED_MAX);                  //LED初始化
	Button_Init();					//按键初始化
	//Beep_ON;
	ADC_init();							//电感初始化
	FLASH_Init();						//初始化flash模块.
	AD_Normalization();					//归一化初始化//读取最大值最小值
	
	camera_init();                      //摄像头初始化
	
	lcd_init();  						//lcd初始化
	//Input_Information();				//按键 输入数据
	//dsp_single_colour(WHITE);
	
	NRF_Dev_Init();						//NRF初始化 包括模拟SPI初始化
	//编码器初始化
	ftm_quad_init(ftm2);  //FTM2  PTA10 （ PTA11 ）正交解码初始化
	ftm_quad_init(ftm1);
	ftm_quad_clean(ftm2);//计数寄存器清零
	ftm_quad_clean(ftm1);//计数寄存器清零
	
	//串口初始化
	//uart_init (uart4, 115200); 		//初始换串口与电脑通信
	uart_init (uart0, 115200);          //初始化swm1000
	uart_rx_irq_en(uart0);
	
	if(Switch_3==0)
		Mode=1;
	else
	{
		Mode=0;
		Meeting_My.Flag=0;
		Meeting_My.State=2;
	}
	
	if(Switch_9==0)
	{
		Roundabout.Mode=1;
	}
	else
	{
		Roundabout.Mode=0;
	}
	
	if(Switch_10==0)
	{
		Rampway.Start=1;
	}
	else
	{
		Rampway.Start=0;
	}
	
	//配置中断向量表
#if chronography 	//计时
	
	pit_init_ms(pit0, 8);                   //初始化PIT0，定时时间为： 8ms
	pit_init_ms(pit1, 1);					  //初始化PIT1	用于计时：1ms
	NVIC_SetPriorityGrouping(5);            //设置优先级分组,4bit 抢占优先级,没有亚优先
	NVIC_SetPriority(PORTB_IRQn , 1);       //配置优先级  图像场中断  PORTA
	NVIC_SetPriority(DMA0_IRQn  , 2);       //配置优先级  图像  DMA0
	NVIC_SetPriority(PIT1_IRQn  , 0);       //配置优先级  编码器   PIT0 
	NVIC_SetPriority(PIT0_IRQn  , 3);       //配置优先级  编码器   PIT0 
	NVIC_SetPriority(UART0_RX_TX_IRQn,4); //配置优先级  串0
	enable_irq(PIT1_IRQn);				  //使能PIT1中断
	enable_irq(PIT0_IRQn);	              //使能PIT0中断
	uart_rx_irq_en(uart0);
	
#else
	pit_init_ms(pit0, 8);                   //初始化PIT0，定时时间为： 8ms
	NVIC_SetPriorityGrouping(4);            //设置优先级分组,4bit 抢占优先级,没有亚优先
	NVIC_SetPriority(PORTB_IRQn , 2);       //配置优先级  图像场中断  PORTA
	NVIC_SetPriority(DMA0_IRQn  , 1);       //配置优先级  图像  DMA0
	NVIC_SetPriority(PIT0_IRQn  , 0);       //配置优先级  编码器   PIT0 
	NVIC_SetPriority(UART0_RX_TX_IRQn,3); //配置优先级  串0
	enable_irq(PIT0_IRQn);	              //使能PIT0中断
	uart_rx_irq_en(uart0);
	
#endif
	EnableInterrupts;                   	  //开启总中断	
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      running  车辆正常运行程序
//  @return     int   
//  @since      v1.0
//  Sample usage:               xxyxxx
//-------------------------------------------------------------------------------------------------------------------

void Running(void)
{

	
	Camera_Get_image();
	if(Mode)
		Read_ADC();

	if(Meeting_My.Flag||Meeting_My.State<2)
	{
		if(!ZebraCrossing.Second_Flag)
		Search_CenterBlackline_Meeting();	//会车区只寻找单边（左边）
		
		if(ZebraCrossing.Start_Flag)	
		{  //只有在会车第0 1 5 6中寻找斑马线 
			Judge_ZebraCrossing(&ZebraCrossing);
			if(ZebraCrossing.Flag&&Meeting_My.Track_Mode==0)//寻找斑马线后的边界
				ModifyEdge_ZebraCrossing(&ZebraCrossing);
		}
	}
	else
	{
		Search_CenterBlackline();     		 	//寻找边线
		
		
		if(!Roundabout.Flag)					//寻找拐点
		{
			FindInflectionPointL(&InflectionPointL ,LeftStart,DropRow+2);   
			FindInflectionPointR(&InflectionPointR ,RightStart,DropRow+2);
		}
		
		
		//判道
		if(Meeting_Area.Start_Flag&&Roundabout.State<2&&!Rampway.Flag&&Crossroad.State<2&&Mode)//判断会车区
			Judge_Meetingarea(&Meeting_Area); 
		
		if(Crossroad.State<2&&Mode)
			Judge_Roundabout(&Roundabout);       //判断环岛

		if(!Roundabout.Flag&&!Rampway.Flag&&Crossroad.Start_Flag)
			Judge_Crossroad(&Crossroad);

		if(Roundabout.State<1)
			Judge_Rampway(&Rampway);
		//补线
		
		
		if(Roundabout.Flag)
			ModifyEdge_Roundabout(&Roundabout);  //环岛补线
		
		if(Crossroad.Flag&&Roundabout.Flag==0)
			ModifyEdge_Crossroad(&Crossroad);
		
	}

	Calculation_Middleline();			 //重新计算中线
	Get_EndLine(MidPri);                 	 //寻找截止行
	Steer_Ctrl();                        //舵机控制
	if(Rampway.Flag||(Roundabout.Size==0&&Roundabout.State==1))
		Beep_ON;
	else
		Beep_OFF;

	switch(Level)
	{
	case Fast_Level:
		{	
			Fast_Set();
			break;
		}
	case Nor_Level:
		{
			Speed_Set();
			break;
			
		}
	case FastFast_Level:
		{
			FastFast_Set();
			break;
		}
	case Low_Level:
		{
			Low_Set();
		//	Beep_ON;
			break;
		}
		
	}

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      main函数
//  @return     int   
//  @since      v1.0
//  Sample usage:               xxyxxx
//------------------------------------------------------------------------------------------------------------------
int main(void)
{
	HardWare_Init();   //初始化函数
	//选择模式
	if(Switch_4)
	{
		//Mode=1;
		Meeting_My.Flag=0;
		Meeting_My.State=2;
		Meeting_Other.Flag=0;
		Meeting_Other.State=2;
		//Meeting_Other.Oder=1;
	}
	if(Switch_5)
	{
		Meeting_My.Flag=0;
		Meeting_My.State=4;
		Meeting_Other.Flag=0;
		Meeting_Other.State=4;
	}
	while(1)
	{
/********************************************/
		//计时用
#if chronography
		static int a=0;
		a=!a;
		gpio_init(E24, GPO,a);
		
#endif
/********************************************/
		//get_config();
		if(Mode)//3ms
		{	//接收数据 测距
			Communication_Accept(&Meeting_My,&Meeting_Other);
			Read_Distance();
			//会车区判定
			Judge_Meeting(&Meeting_My,&Meeting_Other,&Meeting_Area);
		}
		
		Running();//小车跑程序 10ms
		//Beep_ON;
		if(Meeting_My.Send_Flag&&Mode)	
		{	//发送程序
			Communication_Send(&Meeting_My,&Meeting_Other);
		}
		
/********************************************/		
		if(Switch_1)
		{
			Display();
		}
		//Beep_OFF;
		
	}
	

	
	
}