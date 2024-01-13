#include "stm32f10x_it.h"


/**
  * 函    数：USART1中断函数
  * 参    数：无
  * 返 回 值：无
  */

uint8_t ReceiveByte;
  
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		// 接收一个字节8位
		ReceiveByte = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量									//置接收标志位变量为1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
	}
}
