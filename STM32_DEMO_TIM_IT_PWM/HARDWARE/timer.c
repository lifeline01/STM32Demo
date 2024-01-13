#include "timer.h"


/**
 * @brief  TIM2中断配置初始化.
 * @param  自动重装载：arr
 *         时钟预分频：psc
 *		   周期计算：T = (arr + 1) * (psc + 1) / 时钟频率
 * @retval None
 */
void TIM2_IT_Init(uint16_t arr, uint16_t psc)
{
	// 定义初始化结构体变量
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	
	// 开启外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// 配置前停止计时
	TIM_Cmd(TIM2, DISABLE);
	
	// 定时器配置
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
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





/**
 * @brief  TIM3PWM初始化配置.
 * @param  自动重装载：arr
 *         时钟预分频：psc
 *		   周期计算：T = (arr + 1) * (psc + 1) / 时钟频率
 * @retval None
 */
void TIM3_PWM_Init(uint16_t arr, uint16_t psc)
{
	// 定义初始化结构体变量
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef   TIM_OCInitStructure;
	
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(PWM_CH1_RCC, ENABLE);
	
	// 重映射需要开启AFIO时钟
	// 查看参考手册定时器复用功能重映射
	// 部分重映射和完全重映射对应不同的GPIO口
	
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
	// 定时器配置
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				// 时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数模式，向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;			// 重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 输出比较配置
	TIM_OCStructInit(&TIM_OCInitStructure); // 结构体赋初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;				// 输出比较模式
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 输出使能
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 输出极性高，若选择低，则输出高低电平取反
	TIM_OCInitStructure.TIM_Pulse = 0;								// 初始CCR值
   TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	// GPIO初始化
	GPIO_InitStructure.GPIO_Pin = PWM_CH1_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		// 复用推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(PWM_CH1_PORT, &GPIO_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
	
	// TIM_CtrlPWMPutputs(TIM1, ENABLE);	// 主输出使能，高级定时器需要添加
}


/**
  * 函    数：PWM设置CCR
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCompare1(uint16_t Compare)
{
	// 高电平持续时间
	TIM_SetCompare1(TIM3, Compare);
}

