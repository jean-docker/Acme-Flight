#include "User.h"

TaskHandle_t Initial_Task_Handler;


void Initial(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}

int main(void)
{
	RCC_Config();
	
	xTaskCreate((TaskFunction_t)Initial,
							(const char *)"Initial_Task",
							(uint16_t)128,
							(void *)NULL,
							(UBaseType_t)1,
							(TaskHandle_t *)Initial_Task_Handler);
	vTaskStartScheduler();	
	while(1);
}
