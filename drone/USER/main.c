#include "main.h"

void main (void) 
{
	SysClk_Init();
	GPIO_Init();
	PWM_Init();
	ADC_Init();
	UART_Init();
	while(1);
}

