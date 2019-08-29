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
	float USART1_Div;			//USART1 ��Ƶ��
	uint16_t Div_Integer;		//USART1 ��Ƶ����������
	uint8_t Div_Fractional;		//USART1 ��Ƶ��С������
	
	//���������ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//��USART1��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	
	//PA9 USART1_TX �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PA10 USART1_RX ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART1 ���ȼ����� ��ռ���ȼ�4�����ȼ�4
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART1 ��ʼ������ 8λ���� 1λֹͣ ��У�� ��Ӳ������ �շ�
	////////////////////////////////////////////////////////////////////////////////
	//## ע�⣺�����������108m����׼ȷ�����ڳ�ʼ����ɺ��ֶ�����׼ȷ��Ƶֵ##
	////////////////////////////////////////////////////////////////////////////////
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//USART1 ��ʼ��
	USART_Init(USART1, &USART_InitStructure);
	
	USART1_Div =(float)(108000000 / 16) / baud;
	Div_Integer = USART1_Div;
	Div_Fractional = (USART1_Div - Div_Integer) * 16;
	
	USART1->BRR = (Div_Integer<<4) + Div_Fractional;
	
	//����USART1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//ʹ��USART1
	USART_Cmd(USART1, ENABLE);
}

