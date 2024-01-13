#include "NVIC.h"


/**
 * @brief  NVIC管理函数
 * @param  None
 * @retval None
 */
void NvicInit()
{
	// 定义初始化结构体变量
	NVIC_InitTypeDef	NVIC_InitStructure;
	// 中断分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			// 中断通道，选择哪个中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// 中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	// 主优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 子优先级
	
	NVIC_Init(&NVIC_InitStructure);
}
