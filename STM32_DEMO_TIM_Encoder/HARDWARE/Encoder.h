#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "stm32f10x.h"                  // Device header

void Encoder_Init(void);
int16_t EncoderGet(void);

void TIM2_IT_Init(uint16_t arr, uint16_t psc);


#endif


