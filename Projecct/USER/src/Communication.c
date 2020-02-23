#include "Communicate.h"

#if (CarMode==AE86)
const uint8 Checkou_Start_MY=101;
const uint8 Checkou_End_MY=59;

const uint8 Checkou_Start_OTHER=88;
const uint8 Checkou_End_OTHER=200;
#else
const uint8 Checkou_Start_OTHER=101;
const uint8 Checkou_End_OTHER=59;

const uint8 Checkou_Start_MY=88;
const uint8 Checkou_End_MY=200;
#endif

void Communication_Send(meeting *my,meeting *other)
{
	uint8 sta=0;//查询地址
	uint8 i=0;
	/*****清空发送区 接受区数据****************/
	memset(NRF_TX_Buff,0,NRF_DATA_WIDTH);
	
	
	
	NRF_TX_Buff[0]=Checkou_Start_MY;
	NRF_TX_Buff[1]=my->Flag;
	NRF_TX_Buff[2]=my->State;
	NRF_TX_Buff[4]=my->Oder;
	NRF_TX_Buff[5]=Checkou_End_MY;
 
  /*******开始发送数据**********************/
	 NRF_CE (0);                                                                     	// NRF_CE_PIN置低,进入待机模式
	 NRF_SPI_W_Reg_Byte(NRF_CMD_W_REGISTER  | NRF_REG_CONFIG, NRF_RCD_RX_DR_DI           // 禁用发送完成中断
											| NRF_RCD_MAX_RT_DI           // 禁用发送超时中断
											| NRF_RCD_CRC_EN              // 启用CRC
											| NRF_RCD_CRC16               // CRC16
											| NRF_RCD_PWR_UP              // 上电模式
											| NRF_RCD_PRIM_PTX);          // TX模式
	 
	 NRF_SPI_W_Reg_Burst(NRF_CMD_W_REGISTER | NRF_REG_TX_ADDR,NRF_RF_Addr, NRF_ADDR_WIDTH);  // 设置TX地址
	 NRF_SPI_W_Reg_Burst(NRF_CMD_W_TX_PAYLOAD,NRF_TX_Buff, NRF_DATA_WIDTH);                  // 写入发送数据
	 NRF_CE (1);                                                                     		 // NRF_CE_PIN置高,进入运行模式
			 
	 while(1)
	 {
		 i++;
		 sta = NRF_SPI_R_Reg_Byte(NRF_CMD_R_REGISTER | NRF_REG_STATUS);
		 if(sta&0x10)//发送失败
		 {
			 NRF_SPI_W_Reg_Byte(NRF_CMD_W_REGISTER | NRF_REG_STATUS, 0x10); 				// 写回TX_DR,重置NRF_IRQ_PIN中断
			 NRF_SPI_W_Reg_Byte(NRF_CMD_FLUSH_TX,0xff);
			 break;
		 }
		 else if(sta&0x20)//发送成功
		 {
			 NRF_SPI_W_Reg_Byte(NRF_CMD_W_REGISTER | NRF_REG_STATUS, NRF_RCD_TX_DR); 	// 写回TX_DR,重置NRF_IRQ_PIN中断
			 my->Send_Flag=0;
			 break;   
		 }
//			 Running();
//			 if(my->State==6)
//				 Judge_Meeting(&Meeting_My,&Meeting_Other,&Meeting_Area);
			 //Beep_ON;
		 }
}



void Communication_Accept(meeting *my,meeting *other)
{

	NRF_CE (0);                                                                     	// NRF_CE_PIN置低,进入待机模式
	NRF_SPI_W_Reg_Byte(NRF_CMD_W_REGISTER   | NRF_REG_CONFIG,     NRF_RCD_TX_DS_DI        // 禁用发送完成中断
					   						| NRF_RCD_MAX_RT_DI       // 禁用发送超时中断
						  					| NRF_RCD_CRC_EN          // 启用CRC
							        		| NRF_RCD_CRC16           // CRC16
								   			| NRF_RCD_PWR_UP          // 上电模式
									 	  	| NRF_RCD_PRIM_PRX);      // RX模式
	   										                                            // 清空RXFIFO
	NRF_CE (1);                                                      // NRF_CE_PIN置高,进入运行模式
	
	/************发送数据结束开始接受数据*****************************/
	
	if(NRF_Rece_Packet(NRF_RX_Buff))
	{
		if(NRF_RX_Buff[0]==Checkou_Start_OTHER&& NRF_RX_Buff[5]==Checkou_End_OTHER)
		{
			other->Flag			=NRF_RX_Buff[1];
			other->State		=NRF_RX_Buff[2];
			other->Oder 		=NRF_RX_Buff[4];
			Beep_ON;
		}
	}
	else
	{
		//Beep_OFF;
	}
	if(Fail==1)
	{
		if(other->Flag==1&&other->State==3&&my->Send_Flag==0)
		{
			my->State=4;;
			my->Flag=0;
			other->Flag=0;
			other->State=4;
			my->Send_Flag=1;
		}
		if(other->Flag==1&&other->State==6&&my->Send_Flag==0)
		{
			my->State=6;;
			my->Flag=1;
			my->Oder=2;
//			other->Flag=0;
//			other->State=4;
			my->Send_Flag=1;
		}
	}
	memset(NRF_RX_Buff,0,NRF_DATA_WIDTH);
}
