#include "main.h"

void ADC_Init(void)
{
	AINDIDS = 0xf0;						//所有ADC引脚不连接数字电路
	set_ADCEN;							//使能ADC 
}

uint16_t ADC_GetCH1Result(void)
{
	clr_ADCHS0;
	set_ADCHS1;
	set_ADCHS2;
	clr_ADCHS3;							//设置为通道1
	CKDIV = 0x02;						//时钟临时分频，ADC时钟不能过高
	clr_ADCF;							//清除转换完成标志位
	set_ADCS;							//开始转换
	while(ADCF == 0);					//等待转换完成
	CKDIV = 0x00;						//恢复时钟分频
	return (ADCRH>>4) + ADCRL;
}

uint16_t ADC_GetCH2Result(void)
{
	set_ADCHS0;
	clr_ADCHS1;
	set_ADCHS2;
	clr_ADCHS3;							//设置为通道2
	CKDIV = 0x02;						//时钟临时分频，ADC时钟不能过高
	clr_ADCF;							//清除转换完成标志位
	set_ADCS;							//开始转换
	while(ADCF == 0);					//等待转换完成
	CKDIV = 0x00;						//恢复时钟分频
	return (ADCRH>>4) + ADCRL;
}

uint16_t ADC_GetCH3Result(void)
{
	clr_ADCHS0;
	clr_ADCHS1;
	set_ADCHS2;
	clr_ADCHS3;							//设置为通道3
	CKDIV = 0x02;						//时钟临时分频，ADC时钟不能过高
	clr_ADCF;							//清除转换完成标志位
	set_ADCS;							//开始转换
	while(ADCF == 0);					//等待转换完成
	CKDIV = 0x00;						//恢复时钟分频
	return (ADCRH>>4) + ADCRL;
}

uint16_t ADC_GetCH4Result(void)
{
	set_ADCHS0;
	set_ADCHS1;
	set_ADCHS2;
	clr_ADCHS3;							//设置为通道4
	CKDIV = 0x02;						//时钟临时分频，ADC时钟不能过高
	clr_ADCF;							//清除转换完成标志位
	set_ADCS;							//开始转换
	while(ADCF == 0);					//等待转换完成
	CKDIV = 0x00;						//恢复时钟分频
	return (ADCRH>>4) + ADCRL;
}