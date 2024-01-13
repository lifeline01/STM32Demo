#ifndef __TIMER_H
#define __TIMER_H



#include "stm32f10x.h"                  // Device header


void TIM3_PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetPrescaler(uint16_t Prescaler);


#endif

