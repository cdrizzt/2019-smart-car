#include "isr.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PROTA�ж�ִ�к���
//  @return     void   
//  @since      v1.0
//  Sample usage:               ��A�������жϹ����ҷ����жϵ�ʱ����Զ�ִ�иú���
//-------------------------------------------------------------------------------------------------------------------
void PORTB_IRQHandler(void)
{
	uint8  n;    //���ź�
	uint32 flag;
	
	while(!PORTB->ISFR );
	flag = PORTB->ISFR;
	PORTB->ISFR  = ~0;                                   //���жϱ�־λ
	
	n = 17;                                             //���ж�
	if(flag & (1 << n))                                 //PTA29�����ж�
	{
		VSYNC();                                        //����ͼ����
	}
	PORTB->ISFR  = ~0;                                   //���жϱ�־λ
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA0�ж�ִ�к���
//  @return     void   
//  @since      v1.0
//  Sample usage:               ��DMA���ͽ���������ж�
//-------------------------------------------------------------------------------------------------------------------
void DMA0_IRQHandler(void)              
{
	cream_dma();                                    //MT9v032dma����
}

#if chronography 	//��ʱ
uint32 Time;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ�ж�
//  @return     void   
//  @since      v1.0
//  Sample usage:    ��ʱ�ж�
//-------------------------------------------------------------------------------------------------------------------
void PIT1_IRQHandler(void)
{
	disable_irq(PIT1_IRQn);     //��PIT�ж�
	PIT_FlAG_CLR(pit1);        //���PIT0��־
	Time++;
	//		delay_ms(10);
	PIT_FlAG_CLR(pit1);        //���PIT0��־
	enable_irq(PIT1_IRQn);	   //ʹ���ж�
}
#endif

//-------------------------------------------------------------------------------------------------------------------
//  @brief      UART0�ж�ִ�к���
//  @return     void   
//  @since      v1.0
//  Sample usage:     ����ͷ��    ��UART0�����жϹ����ҷ����жϵ�ʱ����Զ�ִ�иú���
//-------------------------------------------------------------------------------------------------------------------
void UART3_RX_TX_IRQHandler(void)
{
	if(UART3->S1 & UART_S1_RDRF_MASK)                                     //�������ݼĴ�����
	{
		//�û���Ҫ������������
		mt9v032_cof_uart_interrupt();
	}
	if(UART3->S1 & UART_S1_TDRE_MASK )                                    //�������ݼĴ�����
	{
		//�û���Ҫ������������
		
	}
}


void UART0_RX_TX_IRQHandler(void)
{
	if(UART0->S1 & UART_S1_RDRF_MASK)                                     //�������ݼĴ�����
	{
		//�û���Ҫ������������
		Rx_Distance();
	}
	
}
/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ������DMA0�жϣ�Ȼ��͵�����ȥ���ĸ���DMA0���жϺ������ƣ��ҵ���дһ�������Ƶĺ�������
void DMA0_IRQHandler(void)
{
;
}
�ǵý����жϺ������־λ


DMA0_IRQHandler  
DMA1_IRQHandler  
DMA2_IRQHandler  
DMA3_IRQHandler  
DMA4_IRQHandler  
DMA5_IRQHandler  
DMA6_IRQHandler  
DMA7_IRQHandler  
DMA8_IRQHandler  
DMA9_IRQHandler  
DMA10_IRQHandler 
DMA11_IRQHandler 
DMA12_IRQHandler 
DMA13_IRQHandler 
DMA14_IRQHandler 
DMA15_IRQHandler 
DMA_Error_IRQHandler      
MCM_IRQHandler            
FTFL_IRQHandler           
Read_Collision_IRQHandler 
LVD_LVW_IRQHandler        
LLW_IRQHandler            
Watchdog_IRQHandler       
RNG_IRQHandler            
I2C0_IRQHandler           
I2C1_IRQHandler           
SPI0_IRQHandler           
SPI1_IRQHandler           
SPI2_IRQHandler           
CAN0_ORed_Message_buffer_IRQHandler    
CAN0_Bus_Off_IRQHandler                
CAN0_Error_IRQHandler                  
CAN0_Tx_Warning_IRQHandler             
CAN0_Rx_Warning_IRQHandler             
CAN0_Wake_Up_IRQHandler                
I2S0_Tx_IRQHandler                     
I2S0_Rx_IRQHandler                     
CAN1_ORed_Message_buffer_IRQHandler    
CAN1_Bus_Off_IRQHandler                
CAN1_Error_IRQHandler                  
CAN1_Tx_Warning_IRQHandler             
CAN1_Rx_Warning_IRQHandler             
CAN1_Wake_Up_IRQHandler                
Reserved59_IRQHandler                  
UART0_LON_IRQHandler                   
UART0_RX_TX_IRQHandler                 
UART0_ERR_IRQHandler                   
UART1_RX_TX_IRQHandler                 
UART1_ERR_IRQHandler  
UART2_RX_TX_IRQHandler
UART2_ERR_IRQHandler  
UART3_RX_TX_IRQHandler
UART3_ERR_IRQHandler  
UART4_RX_TX_IRQHandler
UART4_ERR_IRQHandler  
UART5_RX_TX_IRQHandler
UART5_ERR_IRQHandler  
ADC0_IRQHandler
ADC1_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
FTM0_IRQHandler
FTM1_IRQHandler
FTM2_IRQHandler
CMT_IRQHandler 
RTC_IRQHandler 
RTC_Seconds_IRQHandler  
PIT0_IRQHandler  
PIT1_IRQHandler  
PIT2_IRQHandler  
PIT3_IRQHandler  
PDB0_IRQHandler  
USB0_IRQHandler  
USBDCD_IRQHandler
ENET_1588_Timer_IRQHandler
ENET_Transmit_IRQHandler  
ENET_Receive_IRQHandler
ENET_Error_IRQHandler  
Reserved95_IRQHandler  
SDHC_IRQHandler
DAC0_IRQHandler
DAC1_IRQHandler
TSI0_IRQHandler
MCG_IRQHandler 
LPTimer_IRQHandler 
Reserved102_IRQHandler 
PORTA_IRQHandler 
PORTB_IRQHandler 
PORTC_IRQHandler 
PORTD_IRQHandler 
PORTE_IRQHandler 
Reserved108_IRQHandler
Reserved109_IRQHandler
SWI_IRQHandler 
*/


