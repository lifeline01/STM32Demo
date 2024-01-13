#include "stm32f10x.h"
#include "Delay.h"
#include "USART.h"

extern uint8_t USART_TxPacket[4];
extern uint8_t USART_RxPacket[4];


/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void) 
{
	// NvicInit();
	USARTInit();
	USART_TxPacket[0] = 0x01;
	USART_TxPacket[1] = 0x02;
	USART_TxPacket[2] = 0x03;
	USART_TxPacket[3] = 0x04;
	USART_SendPacket();
	
	while(1)
	{
		if (USART_GetRxFlag() == 1)
		{
			USART_SendArray(USART1, USART_RxPacket, 4);
		}
	}
}




