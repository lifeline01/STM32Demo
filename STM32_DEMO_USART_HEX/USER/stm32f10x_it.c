#include "stm32f10x_it.h"

extern uint8_t USART_RxFlag;
extern uint8_t USART_RxPacket[4];

/**
  * 函    数：USART1中断函数
  * 参    数：无
  * 返 回 值：无
  */ 
void USART1_IRQHandler(void)
{
	// 状态变量，标志状态机位置
	static uint8_t RxState = 0;
	static uint8_t pRxData = 0;
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		// 接收包头
		if (RxState == 0)
		{
			if (RxData == 0xFF)
			{
				RxState = 1;
				pRxData = 0;
			}
		}
		// 接收数据
		else if (RxState == 1)
		{
			USART_RxPacket[pRxData] = RxData;
			pRxData++;
			if (pRxData >= 4)
			{
				RxState = 2;
			}
		}
		// 接收包尾
		else if (RxState == 2)
		{
			if (RxData == 0xFE)
			{
				RxState = 0;
				USART_RxFlag = 1;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
	}
}



