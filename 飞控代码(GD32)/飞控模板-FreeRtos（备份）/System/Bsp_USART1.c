#include "User.h"


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		USART_ClearFlag(USART1, USART_IT_RXNE);
  }
}


void USART1_Config(unsigned long baud)
{
	float USART1_Div;			//USART1 分频数
	uint16_t Div_Integer;		//USART1 分频数整数部分
	uint8_t Div_Fractional;		//USART1 分频数小数部分
	
	//定义外设初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//开USART1和GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	
	//PA9 USART1_TX 复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA10 USART1_RX 浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART1 优先级设置 抢占优先级4子优先级4
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART1 初始化设置 8位数据 1位停止 无校验 无硬件流控 收发
	////////////////////////////////////////////////////////////////////////////////
	//## 注意：这个波特率在108m并不准确，将在初始化完成后手动填入准确分频值##
	////////////////////////////////////////////////////////////////////////////////
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//USART1 初始化
	USART_Init(USART1, &USART_InitStructure);
	
	USART1_Div =(float)(108000000 / 16) / baud;
	Div_Integer = USART1_Div;
	Div_Fractional = (USART1_Div - Div_Integer) * 16;
	
	USART1->BRR = (Div_Integer<<4) + Div_Fractional;
	
	//启动USART1接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//使能USART1
	USART_Cmd(USART1, ENABLE);
}

