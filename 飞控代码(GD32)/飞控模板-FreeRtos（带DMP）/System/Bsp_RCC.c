#include "User.h"

#define GD32_CONFIG_REG		((uint32_t *) ((uint32_t)0x4002))
void RCC_Config(void)
{
	// 把RCC外设初始化成复位状态
	RCC_DeInit();
	
	//使能HSE，开启外部晶振
	RCC_HSEConfig(RCC_HSE_ON);
	
	// 等待 HSE 启动稳定
	if (RCC_WaitForHSEStartUp() == ERROR)
	{
		// 如果HSE开启失败，那么程序就会来到这里
		while (1);
	}
	
	// 使能FLASH 预存取缓冲区
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	
	// SYSCLK周期与闪存访问时间的比例设置，GD32不需要等待
	FLASH_SetLatency(FLASH_Latency_0);

	// AHB预分频因子设置为1分频，HCLK = SYSCLK 
	RCC_HCLKConfig(RCC_SYSCLK_Div1); 

	// APB2预分频因子设置为1分频，PCLK2 = HCLK
	RCC_PCLK2Config(RCC_HCLK_Div1); 

	// APB1预分频因子设置为2分频，PCLK1 = HCLK/2 
	RCC_PCLK1Config(RCC_HCLK_Div2);
	
	// 设置PLL时钟来源为HSE，设置PLL倍频因子,PLLCLK = 8MHz/2 * 27 = 108MHz
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, (uint32_t)0x08280000);

	// 开启PLL 
	RCC_PLLCmd(ENABLE);

	// 等待 PLL稳定
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	// 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	// 读取时钟切换状态位，确保PLLCLK被选为系统时钟
	while (RCC_GetSYSCLKSource() != 0x08);
	*GD32_CONFIG_REG = 0x80;
}
