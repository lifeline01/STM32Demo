#include "MyDMA.h"

uint16_t MyDMA_Size;					//����ȫ�ֱ��������ڼ�סInit������Size����Transfer����ʹ��

/**
  * ��    ����DMA��ʼ��
  * ��    ����AddrA ԭ������׵�ַ
  * ��    ����AddrB Ŀ��������׵�ַ
  * ��    ����Size ת�˵����ݴ�С��ת�˴�����
  * �� �� ֵ����
  */

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
	MyDMA_Size = Size;
	
	/*����ʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);						//����DMA��ʱ��
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;						//�������ַ�������β�AddrA
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ�ȣ�ѡ���ֽ�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;			//�����ַ������ѡ��ʹ��
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;							//�洢������ַ�������β�AddrB
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�洢�����ݿ�ȣ�ѡ���ֽ�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//�洢����ַ������ѡ��ʹ��
	// ������Ϊ����Դ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//���ݴ��䷽��ѡ�������赽�洢��
	DMA_InitStructure.DMA_BufferSize = Size;								//ת�˵����ݴ�С��ת�˴�����
	// ����Ĵ������Զ���װ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//ģʽ��ѡ������ģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;								//�洢�����洢����ѡ��ʹ��
	// ���ͨ��ָ�����ȼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;					//���ȼ���ѡ���е�
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	/*DMAʹ��*/
	DMA_Cmd(DMA1_Channel1, DISABLE);	//�����Ȳ���ʹ�ܣ���ʼ���󲻻����̹������Ⱥ�������Transfer���ٿ�ʼ
}


/**
  * ��    ��������DMA����ת��
  * ��    ������
  * �� �� ֵ����
  */
void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);					//DMAʧ�ܣ���д�봫�������֮ǰ����ҪDMA��ͣ����
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);	//д�봫���������ָ����Ҫת�˵Ĵ���
	DMA_Cmd(DMA1_Channel1, ENABLE);						//DMAʹ�ܣ���ʼ����
	
	// ת����ɱ�־λ
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);	//�ȴ�DMA�������
	DMA_ClearFlag(DMA1_FLAG_TC1);						//���������ɱ�־λ
}




