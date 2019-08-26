#ifndef __ADC_H__
#define __ADC_H__

extern uint16_t ADC_Ch1_Val;
extern uint16_t ADC_Ch2_Val;
extern uint16_t ADC_Ch3_Val;
extern uint16_t ADC_Ch4_Val;

void ADC_Init(void);

void ADC_Start_Cvt(void);

void ADC_ISR(void);

#endif //	#ifndef __ADC_H__