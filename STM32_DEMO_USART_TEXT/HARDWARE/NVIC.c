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
	// 选择中断分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/*NVIC配置*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);							//将结构体变量交给NVIC_Init，配置NVIC外设
}
