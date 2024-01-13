#include "stm32f10x_it.h"

extern uint8_t USART_RxFlag;
extern uint8_t USART_RxPacket[4];

/**
  * ��    ����USART1�жϺ���
  * ��    ������
  * �� �� ֵ����
  */ 
void USART1_IRQHandler(void)
{
	// ״̬��������־״̬��λ��
	static uint8_t RxState = 0;
	static uint8_t pRxData = 0;
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		// ���հ�ͷ
		if (RxState == 0)
		{
			if (RxData == 0xFF)
			{
				RxState = 1;
				pRxData = 0;
			}
		}
		// ��������
		else if (RxState == 1)
		{
			USART_RxPacket[pRxData] = RxData;
			pRxData++;
			if (pRxData >= 4)
			{
				RxState = 2;
			}
		}
		// ���հ�β
		else if (RxState == 2)
		{
			if (RxData == 0xFE)
			{
				RxState = 0;
				USART_RxFlag = 1;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//���USART1��RXNE��־λ
	}
}



