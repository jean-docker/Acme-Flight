#include "System_Config.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t Initial_Task_Handler;
HeapRegion_t xHeapRegions[] =
{
		{(uint8_t *) 0x20000000UL , 0x20000},
    {(uint8_t *) 0x30000000UL , 0x20000},
		{(uint8_t *) 0x30020000UL , 0x20000},
		{(uint8_t *) 0x38000000UL , 0x10000},
    { NULL, 0 }
};
void Initial(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}
int main(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
  HAL_Init();
  SystemClock_Config();
	vPortDefineHeapRegions(xHeapRegions);
	xTaskCreate((TaskFunction_t)Initial,
							(const char *)"Initial_Task",
							(uint16_t)128,
							(void *)NULL,
							(UBaseType_t)1,
							(TaskHandle_t *)Initial_Task_Handler);
	vTaskStartScheduler();
  while (1);
}
