#include "key.h"


/**
 * @brief  按键初始化.
 * @param  None
 * @retval None
 */
void KeyInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY1_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
}


/**
 * @brief  按键检测.
 * @param  None
 * @retval Key_x
 */
Key_x KeyDetect(void)
{
	uint8_t temp1;
	Key_x key = KEY_No;
	
	temp1 = GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN);
	// 按下为高电平为1；否则为0
	if (temp1 == 1)
	{
		key = KEY1;
	}
		
	return key;
}


/**
 * @brief  按键外部中断初始化.-->配置NVIC-->编写中断服务处理程序
 * @param  None
 * @retval None
 */
void KeyExtiInit(void)
{
	// 初始化结构体变量
	GPIO_InitTypeDef	GPIO_InitStructure;
	EXTI_InitTypeDef 	EXTI_InitStructure;
	
	// 开启IC口，复用时钟
	RCC_APB2PeriphClockCmd(KEY2_RCC | RCC_APB2Periph_AFIO, ENABLE);
	
	// 初始化按键IO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
	
	// 初始化EXTI
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;				// 中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				// 中断使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		// 中断 or 事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	// 上升沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	// 设置IO口与中断线的映射关系，选择中断源
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
}



