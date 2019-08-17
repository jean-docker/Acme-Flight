#include "main.h"

void SysClk_Init(void)
{
	set_HIRCEN;						//开启HIRC振荡器
	while(CKSWT & 0x20 != 0x20);	//等待振荡器开启
	clr_OSC0;
	clr_OSC1;						//切换时钟源到HIRC
	while(CKEN & 0x01);				//等待时钟源切换完成
	CKDIV = 0x00;					//系统时钟不分频
}
