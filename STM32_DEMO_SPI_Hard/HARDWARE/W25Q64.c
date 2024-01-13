#include "W25Q64.h"


/**
  * ��    ����W25Q64��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void W25Q64_Init(void)
{
	MySpi_Init();					//�ȳ�ʼ���ײ��SPI
}


/**
  * ��    ������ȡID��
  * ��    ����MID ����ID��ʹ�������������ʽ����
  * ��    ����DID �豸ID��ʹ�������������ʽ����
  * �� �� ֵ����
  */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();								//SPI��ʼ
	MySPI_SwapByte(W25Q64_JEDEC_ID);			//�������Ͷ�ȡID��ָ��
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//��������MID��ͨ�������������
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//��������DID��8λ
	*DID <<= 8;									//��8λ�Ƶ���λ
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//���Ͻ�������DID�ĵ�8λ��ͨ�������������
	MySPI_Stop();								//SPI��ֹ
}


/**
  * ��    ����W25Q64дʹ��
  * ��    ������
  * �� �� ֵ����
  */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();								//SPI��ʼ
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);		//��������дʹ�ܵ�ָ��
	MySPI_Stop();								//SPI��ֹ
}


/**
  * ��    ����W25Q64�ȴ�æ
  * ��    ������
  * �� �� ֵ����
  */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	MySPI_Start();								//SPI��ʼ
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);				//�������Ͷ�״̬�Ĵ���1��ָ��
	Timeout = 100000;							//������ʱ����ʱ��
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)	//ѭ���ȴ�æ��־λ
	{
		Timeout --;								//�ȴ�ʱ������ֵ�Լ�
		if (Timeout == 0)						//�Լ���0�󣬵ȴ���ʱ
		{
			/*��ʱ�Ĵ��������룬�������ӵ��˴�*/
			break;								//�����ȴ���������
		}
	}
	MySPI_Stop();								//SPI��ֹ
}


/**
  * ��    ����W25Q64ҳ���
  * ��    ����Address ҳ��̵���ʼ��ַ����Χ��0x000000~0x7FFFFF
  * ��    ����DataArray	����д�����ݵ�����
  * ��    ����Count Ҫд�����ݵ���������Χ��0~256
  * �� �� ֵ����
  * ע�����д��ĵ�ַ��Χ���ܿ�ҳ
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	
	W25Q64_WriteEnable();						//дʹ��
	
	MySPI_Start();								//SPI��ʼ
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);		//��������ҳ��̵�ָ��
	MySPI_SwapByte(Address >> 16);				//�������͵�ַ23~16λ
	MySPI_SwapByte(Address >> 8);				//�������͵�ַ15~8λ
	MySPI_SwapByte(Address);					//�������͵�ַ7~0λ
	for (i = 0; i < Count; i ++)				//ѭ��Count��
	{
		MySPI_SwapByte(DataArray[i]);			//��������ʼ��ַ��д������
	}
	MySPI_Stop();								//SPI��ֹ
	
	W25Q64_WaitBusy();							//�ȴ�æ
}

/**
  * ��    ����W25Q64����������4KB��
  * ��    ����Address ָ�������ĵ�ַ����Χ��0x000000~0x7FFFFF
  * �� �� ֵ����
  */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();						//дʹ��
	
	MySPI_Start();								//SPI��ʼ
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);	//������������������ָ��
	MySPI_SwapByte(Address >> 16);				//�������͵�ַ23~16λ
	MySPI_SwapByte(Address >> 8);				//�������͵�ַ15~8λ
	MySPI_SwapByte(Address);					//�������͵�ַ7~0λ
	MySPI_Stop();								//SPI��ֹ
	
	W25Q64_WaitBusy();							//�ȴ�æ
}

/**
  * ��    ����W25Q64��ȡ����
  * ��    ����Address ��ȡ���ݵ���ʼ��ַ����Χ��0x000000~0x7FFFFF
  * ��    ����DataArray ���ڽ��ն�ȡ���ݵ����飬ͨ�������������
  * ��    ����Count Ҫ��ȡ���ݵ���������Χ��0~0x800000
  * �� �� ֵ����
  */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();								//SPI��ʼ
	MySPI_SwapByte(W25Q64_READ_DATA);			//�������Ͷ�ȡ���ݵ�ָ��
	MySPI_SwapByte(Address >> 16);				//�������͵�ַ23~16λ
	MySPI_SwapByte(Address >> 8);				//�������͵�ַ15~8λ
	MySPI_SwapByte(Address);					//�������͵�ַ7~0λ
	for (i = 0; i < Count; i ++)				//ѭ��Count��
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//��������ʼ��ַ���ȡ����
	}
	MySPI_Stop();								//SPI��ֹ
}





