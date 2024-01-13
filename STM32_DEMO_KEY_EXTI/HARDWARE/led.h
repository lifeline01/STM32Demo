#ifndef __LED_H
#define __LED_H
#endif

#include "stm32f10x.h"                  // Device header


typedef enum
{
	LED1 = 1,
	LED2 = 2,
	// ...
}Led_x;


// 时钟；端口；引脚宏定义
#define 	LED1_RCC 	RCC_APB2Periph_GPIOA
#define 	LED1_PORT	GPIOA
#define 	LED1_PIN	GPIO_Pin_0


// 函数声明
void LEDInit(void);
void LED_On(Led_x led);
void LED_Off(Led_x led);
void LED_Toggle(Led_x led);
