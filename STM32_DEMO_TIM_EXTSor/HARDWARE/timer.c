#include "timer.h"


/**
 * @brief  TIM2中断配置初始化.
 * @param  自动重装载：arr
 *         时钟预分频：psc
 *		   周期计算：T = (arr + 1) * (psc + 1) / 时钟频率
 * @retval None
 */
void TIM2_ETR_Init()
{
	// 开启外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 选择外部时钟源
	TIM_ETRClockMode1Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
	
	// 配置前停止计时
	TIM_Cmd(TIM2, DISABLE);
	
	// 定义初始化结构体变量
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	// 定时器配置
	// 每计数到 10 更新中断
	TIM_TimeBaseStructure.TIM_Period = 9;
	// 不分频，外部时钟每次到达，计数器加1，到达 重装
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 		// 计数模式，向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;						// 重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 清除定时器更新标志位
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	// 开启中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// 开启计时
	TIM_Cmd(TIM2, ENABLE);
}



