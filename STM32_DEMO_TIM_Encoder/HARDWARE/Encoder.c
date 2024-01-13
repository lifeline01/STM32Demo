#include "Encoder.h"


void Encoder_Init(void)
{
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// 外部模块默认高电平选择上拉输入；默认低电平选择下拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 编码器接口托管时钟，不用内部时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 无用，计数方向由编码器控制
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;	// ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1; 	// PSC 不分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3, ENABLE);
}



int16_t EncoderGet(void)
{
	int16_t temp;
	temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	// 获取 CNT 的值
	return temp;
}


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



