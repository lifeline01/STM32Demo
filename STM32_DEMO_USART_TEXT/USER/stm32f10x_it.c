#include "stm32f10x_it.h"
#include "USART.h"

extern uint8_t USART_RxFlag;
extern char USART_RxPacket[];

void USART1_IRQHandler(void)
{
	// 状态变量，标志状态机位置
	static uint8_t RxState = 0;
	static uint8_t pRxData = 0;
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		// 接收包头
		if (RxState == 0 && USART_RxFlag == 0)
		{
			if (RxData == '@')
			{
				RxState = 1;
				pRxData = 0;
			}
		}
		// 接收数据
		else if (RxState == 1)
		{
			if (RxData == '\r')
			{
				RxState = 2;
			}
			else
			{
				USART_RxPacket[pRxData] = RxData;
				pRxData++;
			}
		}
		// 接收包尾
		else if (RxState == 2)
		{
			if (RxData == '\n')
			{
				RxState = 0;
				USART_RxFlag = 1;
				USART_RxPacket[pRxData] = '\0';
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
	}
}

