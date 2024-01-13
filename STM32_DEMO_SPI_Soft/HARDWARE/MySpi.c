#include "MySpi.h"


/*�������ò�*/

/**
  * ��    ����SPIдSS���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��SS�ĵ�ƽ����Χ0~1
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��SSΪ�͵�ƽ����BitValueΪ1ʱ����Ҫ��SSΪ�ߵ�ƽ
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);		//����BitValue������SS���ŵĵ�ƽ
}

/**
  * ��    ����SPIдSCK���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��SCK�ĵ�ƽ����Χ0~1
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��SCKΪ�͵�ƽ����BitValueΪ1ʱ����Ҫ��SCKΪ�ߵ�ƽ
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);		//����BitValue������SCK���ŵĵ�ƽ
}

/**
  * ��    ����SPIдMOSI���ŵ�ƽ
  * ��    ����BitValue Э��㴫��ĵ�ǰ��Ҫд��MOSI�ĵ�ƽ����Χ0~0xFF
  * �� �� ֵ����
  * ע������˺�����Ҫ�û�ʵ�����ݣ���BitValueΪ0ʱ����Ҫ��MOSIΪ�͵�ƽ����BitValue��0ʱ����Ҫ��MOSIΪ�ߵ�ƽ
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);		//����BitValue������MOSI���ŵĵ�ƽ��BitValueҪʵ�ַ�0��1������
}

/**
  * ��    ����I2C��MISO���ŵ�ƽ
  * ��    ������
  * �� �� ֵ��Э�����Ҫ�õ��ĵ�ǰMISO�ĵ�ƽ����Χ0~1
  * ע������˺�����Ҫ�û�ʵ�����ݣ���ǰMISOΪ�͵�ƽʱ������0����ǰMISOΪ�ߵ�ƽʱ������1
  */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);			//��ȡMISO��ƽ������
}


void MySpi_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/*GPIO��ʼ��*/
	//��PA4��PA5��PA7���ų�ʼ��Ϊ�������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//��PA6���ų�ʼ��Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*����Ĭ�ϵ�ƽ*/
	MySPI_W_SS(1);											//SSĬ�ϸߵ�ƽ,��ѡ��
	MySPI_W_SCK(0);											//SCKĬ�ϵ͵�ƽ
}


/*Э���*/

/**
  * ��    ����SPI��ʼ
  * ��    ������
  * �� �� ֵ����
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);				//����SS����ʼʱ��
}

/**
  * ��    ����SPI��ֹ
  * ��    ������
  * �� �� ֵ����
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);				//����SS����ֹʱ��
}

/**
  * ��    ����SPI��������һ���ֽڣ�ʹ��SPIģʽ0
  * ��    ����ByteSend Ҫ���͵�һ���ֽ�
  * �� �� ֵ�����յ�һ���ֽ�
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;					//������յ����ݣ�������ֵ0x00���˴����븳��ֵ0x00��������õ�
	
	for (i = 0; i < 8; i ++)						//ѭ��8�Σ����ν���ÿһλ����
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));		//ʹ������ķ�ʽȡ��ByteSend��ָ��һλ���ݲ�д�뵽MOSI��
		MySPI_W_SCK(1);								//����SCK���������Ƴ�����
		if (MySPI_R_MISO() == 1){ByteReceive |= (0x80 >> i);}	//��ȡMISO���ݣ����洢��Byte����
																//��MISOΪ1ʱ���ñ���ָ��λΪ1����MISOΪ0ʱ����������ָ��λΪĬ�ϵĳ�ֵ0
		MySPI_W_SCK(0);								//����SCK���½�����������
	}
	
	return ByteReceive;								//���ؽ��յ���һ���ֽ�����
}






