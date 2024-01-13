#include "timeric.h"


void IC_Init(void)
{
	// 开启时钟
	// 这里配置 TIM2 的通道1 PA0 为输入
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// 上拉输入
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 时钟源内部时钟
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 65536 - 1;   // 防止溢出
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; 	// 配置标准频率 1MHz CNT++
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数模式，向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;			// 重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;		// 选择通道
	TIM_ICInitStructure.TIM_ICFilter = 0xF;						// 输入捕获的滤波器
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		// 出发方式上升下降BOTH
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	// 不分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;// 直连通道
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM2, ENABLE);
}	



// fc / N
// fc = 72MHz / (PSC + 1) = 1MHz
// N = TIM_GetCapture1(TIM2)
uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM2) + 1);
}




