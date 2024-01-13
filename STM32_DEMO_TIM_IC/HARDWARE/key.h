#ifndef __KEY_H
#define __KEY_H
#endif

#include "stm32f10x.h"                  // Device header


typedef enum
{
	KEY_No = 0,
	KEY1 = 1,
	KEY2 = 2,
	// ...
}Key_x;


// 时钟；端口；引脚宏定义
#define 	KEY1_RCC 	RCC_APB2Periph_GPIOA
#define 	KEY1_PORT	GPIOA
#define 	KEY1_PIN	GPIO_Pin_1

#define 	KEY2_RCC 	RCC_APB2Periph_GPIOA
#define 	KEY2_PORT	GPIOA
#define 	KEY2_PIN	GPIO_Pin_2


// 函数声明
void KeyInit(void);
Key_x KeyDetect(void);

void KeyExtiInit(void);
