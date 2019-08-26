#ifndef __MAIN_H__
#define __MAIN_H__


#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "ADC.h"
#include "PWM.h"
#include "SysClk.h"
#include "GPIO.h"
#include "I2C.h"
#include "UART.h"

//############# 注意： 以下数值均是16MHZ下的标准值，在16.6MHZ下并不准确 ###################

#define TIMER_DIV12_VALUE_10us			65536-13		//13*12/16000000 = 10 uS,  			// Timer divider = 12 for TM0/TM1
#define TIMER_DIV12_VALUE_100us			65536-130		//130*12/16000000 = 10 uS,  		// Timer divider = 12 
#define TIMER_DIV12_VALUE_1ms				65536-1334	//1334*12/16000000 = 1 mS, 			// Timer divider = 12 
#define TIMER_DIV12_VALUE_10ms			65536-13334	//13334*12/16000000 = 10 mS 		// Timer divider = 12 
#define TIMER_DIV12_VALUE_40ms			65536-53336	//53336*12/16000000 = 40 ms			// Timer divider = 12 
#define TIMER_DIV4_VALUE_10us				65536-40		//40*4/16000000 = 10 uS,    		// Timer divider = 4	for TM2/TM3
#define TIMER_DIV4_VALUE_100us			65536-400		//400*4/16000000 = 100 us				// Timer divider = 4
#define TIMER_DIV4_VALUE_200us			65536-800		//800*4/16000000 = 200 us				// Timer divider = 4
#define TIMER_DIV4_VALUE_500us			65536-2000	//2000*4/16000000 = 500 us			// Timer divider = 4
#define TIMER_DIV4_VALUE_1ms				65536-4000	//4000*4/16000000 = 1 mS,   		// Timer divider = 4
#define TIMER_DIV16_VALUE_10ms			65536-10000	//10000*16/16000000 = 10 ms			// Timer	divider = 16
#define TIMER_DIV64_VALUE_30ms			65536-7500	//7500*64/16000000 = 30 ms			// Timer divider = 64
#define	TIMER_DIV128_VALUE_100ms		65536-12500	//12500*128/16000000 = 100 ms		// Timer divider = 128
#define	TIMER_DIV128_VALUE_200ms		65536-25000	//25000*128/16000000 = 200 ms		// Timer divider = 128
#define TIMER_DIV256_VALUE_500ms		65536-31250	//31250*256/16000000 = 500 ms 	// Timer divider = 256
#define	TIMER_DIV512_VALUE_1s				65536-31250	//31250*512/16000000 = 1 s.

#endif //	#ifndef __MAIN_H__
