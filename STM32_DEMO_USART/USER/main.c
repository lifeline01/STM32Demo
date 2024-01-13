#include "stm32f10x.h"
#include "Delay.h"
#include "USART.h"


extern uint8_t ReceiveByte;

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	// NvicInit();
	USARTInit();
	// 发送字符A，先对A编码，然后发送
	USART_SendByte(USART1, 'A');
	USART_SendByte(USART1, 0x41);
	
	uint8_t Array[] = {0x42, 0x43, 0x44, 0x45};
	USART_SendArray(USART1, Array, 4);
	
	USART_SendString(USART1, "Hello World\r\n");
	
	USART_SendNumber(USART1, 111, 3);
	
	// 只是串口1的打印
	printf("Num = %d\r\n", 666);
	// 多个printf
	Printf("Num = %d\r\n", 666);
	
	// sprintf函数 将 字符串内容保存到 数组中
	char string[100];
	sprintf(string, "Num = %d\r\n", 666);
	USART_SendString(USART1, string);
	
	while(1)
	{
		USART_SendByte(USART1, ReceiveByte);
	}
}

