#include "main.h"

void SysClk_Init(void)
{
	unsigned char hircmap0,hircmap1;
	unsigned int trimvalue16bit;
	
	set_HIRCEN;						//开启HIRC振荡器
	while(CKSWT & 0x20 != 0x20);	//等待振荡器开启
	clr_OSC0;
	clr_OSC1;						//切换时钟源到HIRC
	while(CKEN & 0x01);				//等待时钟源切换完成
	CKDIV = 0x00;					//系统时钟不分频
	
	//使用以下程序调整HIRC到16.6MHZ，减小串口波特率误差
	
	set_IAPEN;						//使能IAP
	IAPAL = 0x30;
	IAPAH = 0x00;					//读取地址
	IAPCN = READ_UID;				//读UID
	set_IAPGO;						//启动IAP
	hircmap0 = IAPFD;				//HIRC校准值低位
	IAPAL = 0x31;
	IAPAH = 0x00;					//读取地址
	set_IAPGO;						//启动IAP
	hircmap1 = IAPFD;				//HIRC校准值高位
	clr_IAPEN;						//失能IAP
	trimvalue16bit = ((hircmap0<<1)+(hircmap1&0x01));
	
	//HIRC校准值减去15，即16M+15*40KHZ = 16.6MHZ
	trimvalue16bit = trimvalue16bit - 15;
	
	hircmap1 = trimvalue16bit&0x01;
	hircmap0 = trimvalue16bit>>1;
	TA=0XAA;
	TA=0X55;						//关TA保护
	RCTRIM0 = hircmap0;				//修改值写入寄存器
	TA=0XAA;
	TA=0X55;						//关TA保护
	RCTRIM1 = hircmap1;				//修改值写入寄存器
}	
