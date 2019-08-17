#ifndef __ADC_H__
#define __ADC_H__

void ADC_Init(void);

uint16_t ADC_GetCH1Result(void);
uint16_t ADC_GetCH2Result(void);
uint16_t ADC_GetCH3Result(void);
uint16_t ADC_GetCH4Result(void);

#endif //	#ifndef __ADC_H__