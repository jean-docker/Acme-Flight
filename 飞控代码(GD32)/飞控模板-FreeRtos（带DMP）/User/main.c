#include "User.h"

TaskHandle_t Initial_Task_Handler;

float Pitch,Roll,Yaw;

void Initial(void *pvParameters)
{
	while(1)
	{	
		Read_DMP(&Pitch,&Roll,&Yaw);
		vTaskDelay(5);
	}
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
	delay_init();
	IIC_Init();
	DMP_Init();
		
	xTaskCreate((TaskFunction_t)Initial,
							(const char *)"Initial_Task",
							(uint16_t)128,
							(void *)NULL,
							(UBaseType_t)1,
							(TaskHandle_t *)Initial_Task_Handler);
	vTaskStartScheduler();	
	while(1);
}
