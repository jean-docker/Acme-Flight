#include "main.h"

#define BAUDATE 256000

void UART_Init(void)
{
	InitialUART0_Timer3(BAUDATE);			//使用库初始化UART0
	set_EA;									//开总中断
	set_ES;									//使能串口中断
	set_PS;									//设置优先级低位为1
	set_PSH;								//设置优先级高位为1
}
