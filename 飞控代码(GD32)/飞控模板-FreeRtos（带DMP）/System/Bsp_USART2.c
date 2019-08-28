#include "User.h"


void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearFlag(USART2, USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART2, USART_IT_TC) == SET)
	{
		USART_ClearFlag(USART2, USART_IT_TC);
	}
}


void USART2_Config(unsigned long baud)
{
	float USART2_Div;			//USART2 分频数
	uint16_t Div_Integer;		//USART2 分频数整数部分
	uint8_t Div_Fractional;		//USART2 分频数小数部分
	
	//定义外设初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//开USART2和GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2 USART2_TX 复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA3 USART2_RX 浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART2 优先级设置 抢占优先级0子优先级0
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART2 初始化设置 8位数据 1位停止 无校验 无硬件流控 收发
	////////////////////////////////////////////////////////////////////////////////
	//## 注意：这个波特率在108m并不准确，将在初始化完成后手动填入准确分频值##
	////////////////////////////////////////////////////////////////////////////////
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//USART2 初始化
	USART_Init(USART2, &USART_InitStructure);
	
	USART2_Div =(float)(54000000 / 16) / baud;
	Div_Integer = USART2_Div;
	Div_Fractional = (USART2_Div - Div_Integer) * 16;
	USART2->BRR = (Div_Integer<<4) + Div_Fractional;
	
	//启动USART2接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//使能USART2
	USART_Cmd(USART2, ENABLE);
}

