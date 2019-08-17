#include "main.h"

void GPIO_Init(void)
{
	P06_Quasi_Mode;				//TXD准双向
	P07_Quasi_Mode;				//RXD准双向
	
	P03_Input_Mode;				//ADC通道1高阻输入
	P04_Input_Mode;				//ADC通道2高阻输入
	P05_Input_Mode;				//ADC通道3高阻输入
	P11_Input_Mode;				//ADC通道2高阻输入
	
	P30_Quasi_Mode;				//外部中断0准双向
	
	P17_PushPull_Mode;			//LED1推挽输出
	P16_PushPull_Mode;			//LED2推挽输出
	P15_PushPull_Mode;			//LED3推挽输出
	P02_PushPull_Mode;			//LED4推挽输出
	
	P01_PushPull_Mode;			//PWM1推挽输出
	P00_PushPull_Mode;			//PWM2推挽输出
	P10_PushPull_Mode;			//PWM3推挽输出
	P12_PushPull_Mode;			//PWM4推挽输出
	
	set_P0SR_1;					//PWM1高斜率
	set_P0SR_0;					//PWM2高斜率
	set_P1SR_0;					//PWM3高斜率
	set_P1SR_2;					//PWM4高斜率
	
	P13_PushPull_Mode;			//SCL推挽输出
	P14_PushPull_Mode;			//SDA推挽输出
}
