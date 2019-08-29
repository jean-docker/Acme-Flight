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
	float USART2_Div;			//USART2 ��Ƶ��
	uint16_t Div_Integer;		//USART2 ��Ƶ����������
	uint8_t Div_Fractional;		//USART2 ��Ƶ��С������
	
	//���������ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//��USART2��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2 USART2_TX �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA3 USART2_RX ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART2 ���ȼ����� ��ռ���ȼ�0�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART2 ��ʼ������ 8λ���� 1λֹͣ ��У�� ��Ӳ������ �շ�
	////////////////////////////////////////////////////////////////////////////////
	//## ע�⣺�����������108m����׼ȷ�����ڳ�ʼ����ɺ��ֶ�����׼ȷ��Ƶֵ##
	////////////////////////////////////////////////////////////////////////////////
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//USART2 ��ʼ��
	USART_Init(USART2, &USART_InitStructure);
	
	USART2_Div =(float)(54000000 / 16) / baud;
	Div_Integer = USART2_Div;
	Div_Fractional = (USART2_Div - Div_Integer) * 16;
	USART2->BRR = (Div_Integer<<4) + Div_Fractional;
	
	//����USART2�����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//ʹ��USART2
	USART_Cmd(USART2, ENABLE);
}

