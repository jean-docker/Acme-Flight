#include "User.h"

void LED_Config(void)
{
	//定义外设初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//开GPIOA和GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	//PA8 PA15 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PB3 PB4 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//关闭所有LED
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4);
}
