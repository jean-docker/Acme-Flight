#ifndef __USER_H__
#define __USER_H__
/////////////////////////	STM32 SPL¿â	/////////////////////////
#include "stm32f10x.h"

/////////////////////////	FREERTOS	/////////////////////////
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/////////////////////////		BSP		/////////////////////////
#include "Bsp_RCC.h"
#include "Bsp_USART1.h"
#include "Bsp_USART2.h"
#include "Bsp_LED.h"
#include "Bsp_PWM.h"
#include "Bsp_ADC.h"

/////////////////////////	DMP_LIB		/////////////////////////
#include "ioi2c.h"
#include "MPU6050.h"
#include "delay.h"

#endif //	#ifndef __USER_H__
