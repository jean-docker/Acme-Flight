#include "User.h"

TaskHandle_t Initial_Task_Handler;

void Send_Buf(USART_TypeDef *USARTT,unsigned char data);
void Initial(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(10);
	}
}

void Send_Buf(USART_TypeDef *USARTT,unsigned char data)
{
	while((USARTT->SR&0X40)==0){}
    USARTT->DR = (u8) data;
}

int main(void)
{	
	//设置NVIC，2抢占优先级2子优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_Config();
	USART1_Config(2250000);
	USART2_Config(115200);
	//LED_Config();
	PWM_Config();
	ADC_Config();
	xTaskCreate((TaskFunction_t)Initial,
							(const char *)"Initial_Task",
							(uint16_t)128,
							(void *)NULL,
							(UBaseType_t)1,
							(TaskHandle_t *)Initial_Task_Handler);
	vTaskStartScheduler();	
	while(1);
}
