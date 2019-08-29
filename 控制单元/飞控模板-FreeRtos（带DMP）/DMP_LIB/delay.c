#include "delay.h"
#include "sys.h"
#include "User.h"
	
	
void delay_init()	 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInitStruct.TIM_Period = 100-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 107;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    while((TIM2->SR & TIM_FLAG_Update)!=SET);
    TIM2->SR = (uint16_t)~TIM_FLAG_Update;
}								    

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	TIM2->CNT = nus-1;
    TIM2->CR1 |= TIM_CR1_CEN;    
    while((TIM2->SR & TIM_FLAG_Update)!=SET);
    TIM2->SR = (uint16_t)~TIM_FLAG_Update;
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

void delay_ms(u16 nms)
{	 		  	  
	while(nms--)
	{
		delay_us(1000);
	}
} 

