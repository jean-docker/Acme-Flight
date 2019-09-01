#include "User.h"

#define GD32_CONFIG_REG		((uint32_t *) ((uint32_t)0x4002))
void RCC_Config(void)
{
	// ��RCC�����ʼ���ɸ�λ״̬
	RCC_DeInit();
	
	//ʹ��HSE�������ⲿ����
	RCC_HSEConfig(RCC_HSE_ON);
	
	// �ȴ� HSE �����ȶ�
	if (RCC_WaitForHSEStartUp() == ERROR)
	{
		// ���HSE����ʧ�ܣ���ô����ͻ���������
		while (1);
	}
	
	// ʹ��FLASH Ԥ��ȡ������
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	
	// SYSCLK�������������ʱ��ı������ã�GD32����Ҫ�ȴ�
	FLASH_SetLatency(FLASH_Latency_0);

	// AHBԤ��Ƶ��������Ϊ1��Ƶ��HCLK = SYSCLK 
	RCC_HCLKConfig(RCC_SYSCLK_Div1); 

	// APB2Ԥ��Ƶ��������Ϊ1��Ƶ��PCLK2 = HCLK
	RCC_PCLK2Config(RCC_HCLK_Div1); 

	// APB1Ԥ��Ƶ��������Ϊ2��Ƶ��PCLK1 = HCLK/2 
	RCC_PCLK1Config(RCC_HCLK_Div2);
	
	// ����PLLʱ����ԴΪHSE������PLL��Ƶ����,PLLCLK = 8MHz/2 * 27 = 108MHz
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, (uint32_t)0x08280000);

	// ����PLL 
	RCC_PLLCmd(ENABLE);

	// �ȴ� PLL�ȶ�
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	// ��PLL�ȶ�֮�󣬰�PLLʱ���л�Ϊϵͳʱ��SYSCLK
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	// ��ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
	while (RCC_GetSYSCLKSource() != 0x08);
	*GD32_CONFIG_REG = 0x80;
}
