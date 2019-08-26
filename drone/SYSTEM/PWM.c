#include "main.h"

void PWM_Init(void)
{
	clr_PWMRUN;							//失能PWM
	set_CLRPWM;							//清除PWM计数
	
	PWM4_P01_OUTPUT_ENABLE;				//使能PWM1输出
	PWM3_P00_OUTPUT_ENABLE;				//使能PWM2输出
	PWM2_P10_OUTPUT_ENABLE;				//使能PWM3输出
	PWM0_P12_OUTPUT_ENABLE;				//使能PWM4输出
	
	PWM_IMDEPENDENT_MODE;				//PWM工作在独立模式
	set_PWMTYP;							//边缘对齐模式
	PWM_CLOCK_FSYS;						//系统时钟作为时钟源
	
	clr_PWMDIV0;
	clr_PWMDIV1;
	clr_PWMDIV2;						//PWM不分频
	
	PWMPH = 0x03;
	PWMPL = 0xFF;						//PWM周期计数器,10Bit精度
	
	PWM0H = 0x00;
	PWM0L = 0x00;						//PWM通道1初始化
	
	PWM2H = 0x00;
	PWM2L = 0x00;						//PWM通道2初始化
	
	PWM3H = 0x00;
	PWM3L = 0x00;						//PWM通道3初始化
	
	set_SFRPAGE;
	PWM4H = 0x00;
	PWM4L = 0x00;						//PWM通道4初始化
	clr_SFRPAGE;
	
	set_LOAD;							//重装填PWM比较器值
    set_PWMRUN;							//启动PWM

}

void PWM1_SetDuty(uint16_t duty)
{
	PWM0H = (duty & 0xff00)>>8;
	PWM0L = duty & 0xff;
	set_LOAD;
}

void PWM2_SetDuty(uint16_t duty)
{
	PWM2H = (duty & 0xff00)>>8;
	PWM2L = duty & 0x00ff;
	set_LOAD;
}

void PWM3_SetDuty(uint16_t duty)
{
	PWM3H = (duty & 0xff00)>>8;
	PWM3L = duty & 0x00ff;
	set_LOAD;
}

void PWM4_SetDuty(uint16_t duty)
{
	set_SFRPAGE;
	PWM4H = (duty & 0xff00)>>8;
	PWM4L = duty & 0x00ff;
	clr_SFRPAGE;
	set_LOAD;
}
