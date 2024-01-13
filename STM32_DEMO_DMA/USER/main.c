#include "stm32f10x.h"
#include "Delay.h"
#include "MyDMA.h"


uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};				//�����������DataA��Ϊ����Դ
uint8_t DataB[] = {0, 0, 0, 0};							//�����������DataB��Ϊ����Ŀ�ĵ�


int main(void)
{
	
	MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);
	
	while(1)
	{
		DataA[0] ++;		//�任��������
		DataA[1] ++;
		DataA[2] ++;
		DataA[3] ++;
		
		MyDMA_Transfer();
		Delay_ms(100);
	}
}

