#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

uint8_t MID;							//�������ڴ��MID�ŵı���
uint16_t DID;							//�������ڴ��DID�ŵı���

uint8_t ArrayWrite[] = {0x01, 0x02, 0x03, 0x04};	//����Ҫд�����ݵĲ�������
uint8_t ArrayRead[4];								//����Ҫ��ȡ���ݵĲ�������

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	OLED_Init();
	W25Q64_Init();						//W25Q64��ʼ��
	
	/*��ʾ��̬�ַ���*/
	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	/*��ʾID��*/
	W25Q64_ReadID(&MID, &DID);			//��ȡW25Q64��ID��
	OLED_ShowHexNum(1, 5, MID, 2);		//��ʾMID
	OLED_ShowHexNum(1, 12, DID, 4);		//��ʾDID
	
	/*W25Q64���ܺ�������*/
	W25Q64_SectorErase(0x000000);					//��������
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);	//��д�����ݵĲ�������д�뵽W25Q64��
	
	W25Q64_ReadData(0x000000, ArrayRead, 4);		//��ȡ��д��Ĳ������ݵ���ȡ���ݵĲ���������
	
	/*��ʾ����*/
	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);		//��ʾд�����ݵĲ�������
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);
	
	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);			//��ʾ��ȡ���ݵĲ�������
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
	
	while(1)
	{
		
	}
}

