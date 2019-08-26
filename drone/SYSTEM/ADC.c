#include "main.h"

uint16_t ADC_Ch1_Val;
uint16_t ADC_Ch2_Val;
uint16_t ADC_Ch3_Val;
uint16_t ADC_Ch4_Val;

void ADC_Init(void)
{
	AINDIDS = 0xf0;						//所有用到的ADC引脚不连接数字电路
	set_ADCEN;							//使能ADC 
	clr_ADCHS0;set_ADCHS1;set_ADCHS2;clr_ADCHS3;//设置为通道1
	clr_ADCF;							//清除转换完成标志位
	set_EA;								//开总中断
	set_EADC;							//使能ADC中断
}

void ADC_Start_Cvt(void)
{
	if(ADCS == 1 || (ADCCON0 &0x0f) != 0x06)	//ADC模块正在转换或者所有通道没有转换完成
	{
		return;
	}
	CKDIV = 0x02;						//时钟临时分频，ADC时钟不能过高
	clr_ADCF;							//清除转换完成标志位
	set_ADCS;							//开始转换
}

void ADC_ISR(void)   interrupt 11     	//ADC中断号11
{
	switch(ADCCON0 & 0x0f)
	{
		case 0x06:
			ADC_Ch1_Val = (ADCRH<<4) + ADCRL;	//通道1转换结果
			set_ADCHS0;clr_ADCHS1;set_ADCHS2;clr_ADCHS3;//设置为通道2
			clr_ADCF;							//清除转换完成标志位
			set_ADCS;							//开始转换
			break;
		
		case 0x05:
			ADC_Ch2_Val = (ADCRH<<4) + ADCRL;	//通道2转换结果
			clr_ADCHS0;clr_ADCHS1;set_ADCHS2;clr_ADCHS3;//设置为通道3
			clr_ADCF;							//清除转换完成标志位
			set_ADCS;							//开始转换
			break;
		
		case 0x04:
			ADC_Ch3_Val = (ADCRH<<4) + ADCRL;	//通道3转换结果
			set_ADCHS0;set_ADCHS1;set_ADCHS2;clr_ADCHS3;//设置为通道4
			clr_ADCF;							//清除转换完成标志位
			set_ADCS;							//开始转换
			break;
		
		case 0x07:
			ADC_Ch4_Val = (ADCRH<<4) + ADCRL;	//通道4转换结果
			clr_ADCHS0;set_ADCHS1;set_ADCHS2;clr_ADCHS3;//设置为通道1
			clr_ADCF;							//清除转换完成标志位
			CKDIV = 0x00;						//恢复时钟分频
			break;
	}

}
