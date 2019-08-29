#include "User.h"

__IO uint16_t ADC_CvtValue[4]={0,0,0,0};

void ADC_Config(void)
{
	//���������ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	//��GPIOA��GPIOB��ADC1��DMA1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | \
							RCC_APB2Periph_ADC1 , ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
	
	//ADCʱ�����Ϊ16M������ʱ�ӷ�Ƶ�������8
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//PA0 PA1 PB0 PB1 ģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//ʹ������ת���������Ҷ��룬���ⲿ����������ģʽ��4ͨ����ʹ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;
	//��ʼ��ADC1
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 4, ADC_SampleTime_55Cycles5);

	DMA_InitStructure.DMA_BufferSize = 4;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_CvtValue;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC1->DR ) );
	DMA_InitStructure.DMA_PeripheralDataSize= DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//��ʼ��DMA1
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	//ʹ��DMA1
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	//ʹ��ADC1 DMA����
	ADC_DMACmd(ADC1,ENABLE);
	
	//ʹ��ADC1
	ADC_Cmd(ADC1,ENABLE);
	
	//����У׼ֵ
	ADC_ResetCalibration(ADC1);
	//�ȴ�����У׼ֵ���
	while(ADC_GetResetCalibrationStatus(ADC1));
	//У׼ADC1
	ADC_StartCalibration(ADC1);
	//�ȴ�ADC1У׼���
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
