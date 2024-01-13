#ifndef __TIMER_H
#define __TIMER_H



#include "stm32f10x.h"                  // Device header


#define PWM_CH1_RCC		RCC_APB2Periph_GPIOA
#define PWM_CH1_PORT		GPIOA
#define PWM_CH1_PIN		GPIO_Pin_6


// 函数声明
void TIM2_IT_Init(uint16_t arr, uint16_t psc);
void TIM3_PWM_Init(uint16_t arr, uint16_t psc);
void PWM_SetCompare1(uint16_t Compare);

#endif

