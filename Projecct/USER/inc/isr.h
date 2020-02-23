#ifndef _isr_h
#define _isr_h


#include "headfile.h"

#if chronography 	//¼ÆÊ±

extern uint32 Time;
#endif

void PORTB_IRQHandler(void);
void PIT1_IRQHandler(void);
void DMA0_IRQHandler(void);
void UART0_RX_TX_IRQHandler(void);
#endif
