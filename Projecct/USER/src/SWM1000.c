#include "swm1000.h"

uint8 Distance_StartFlag;

//uint8 as[18]={0};

void Rx_Distance()
{
	int i;
	uint8 as[18]={0};
	//Time=0;
	for(i=0;i<18;i++)
	{
		uart_getchar(uart0,&as[i]);
	}
	for(i=0;i<21;i++)
	{
		if(as[i]==0x0D && as[i+5]==0x0A)
		{
			Meeting_My.Distance=((as[i+1]-48)*100+(as[i+2]-48)*10+(as[i+3]-48)*1); 
			break;
		}
	}
	//	Time=0;
	uart_rx_irq_dis(uart0);
	
}

void Read_Distance()
{
	if(Distance_StartFlag)
	{
		uart_rx_irq_en(uart0);	//Ê¹ÄÜuart0£»
	}
	else
	{
		uart_rx_irq_dis(uart0);
	}
}