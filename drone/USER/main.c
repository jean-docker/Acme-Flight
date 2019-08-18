#include "main.h"

void main (void) 
{
	SysClk_Init();
	GPIO_Init();
	PWM_Init();
	ADC_Init();
	UART0_Init();
	
	while(1)
	{
		//ADC_Start_Cvt();
		Send_Data_To_UART0(0x1e);
		Timer0_Delay1ms(1);
	}
}

