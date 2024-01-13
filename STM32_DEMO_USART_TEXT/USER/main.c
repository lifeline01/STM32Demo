#include "stm32f10x.h"
#include "Delay.h"
#include "USART.h"

#include <string.h>

extern uint8_t USART_RxFlag;
extern char USART_RxPacket[];

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	// NvicInit();
	USARTInit();
	
	while(1)
	{
		// 如果接收标志位是1
		if (USART_RxFlag == 1)
		{
			// 把字符串发送回
			USART_SendString(USART1, USART_RxPacket);
			
			if (strcmp(USART_RxPacket, "LED1") == 0)
			{
				// 指令匹配操作
			}
			
			USART_RxFlag = 0;
		}
		
	}
}




