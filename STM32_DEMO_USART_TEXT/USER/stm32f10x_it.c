#include "stm32f10x_it.h"
#include "USART.h"

extern uint8_t USART_RxFlag;
extern char USART_RxPacket[];

void USART1_IRQHandler(void)
{
	// ״̬��������־״̬��λ��
	static uint8_t RxState = 0;
	static uint8_t pRxData = 0;
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		// ���հ�ͷ
		if (RxState == 0 && USART_RxFlag == 0)
		{
			if (RxData == '@')
			{
				RxState = 1;
				pRxData = 0;
			}
		}
		// ��������
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
		// ���հ�β
		else if (RxState == 2)
		{
			if (RxData == '\n')
			{
				RxState = 0;
				USART_RxFlag = 1;
				USART_RxPacket[pRxData] = '\0';
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//���USART1��RXNE��־λ
	}
}

