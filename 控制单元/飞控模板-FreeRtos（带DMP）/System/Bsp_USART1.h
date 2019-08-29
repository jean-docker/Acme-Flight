#ifndef __BSP_USART1_H__
#define __BSP_USART1_H__

#include "User.h"

void USART1_IRQHandler(void);
void USART1_Config(unsigned long baud);

#endif	//	#ifndef __BSP_USART1_H__
