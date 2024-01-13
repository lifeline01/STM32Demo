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


void MySpi_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//����SPI1��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA4���ų�ʼ��Ϊ�������
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA5��PA7���ų�ʼ��Ϊ�����������
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA6���ų�ʼ��Ϊ��������
	
	/*SPI��ʼ��*/
	SPI_InitTypeDef SPI_InitStructure;						//����ṹ�����
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//ģʽ��ѡ��ΪSPI��ģʽ
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//����ѡ��2��ȫ˫��
	SPI_InitStructure.SPI_DataSize =  SPI_DataSize_8b;		//���ݿ�ȣ�ѡ��Ϊ8λ
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		//����λ��ѡ���λ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	//�����ʷ�Ƶ��ѡ��128��Ƶ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				//SPI���ԣ�ѡ��ͼ���
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;			//SPI��λ��ѡ���һ��ʱ�ӱ��ز��������Ժ���λ����ѡ��SPIģʽ0
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//NSS��ѡ�����������
	SPI_InitStructure.SPI_CRCPolynomial = 7;				//CRC����ʽ����ʱ�ò�������Ĭ��ֵ7
	SPI_Init(SPI1, &SPI_InitStructure);						//���ṹ���������SPI_Init������SPI1
	
	/*SPIʹ��*/
	SPI_Cmd(SPI1, ENABLE);									//ʹ��SPI1����ʼ����
	
	/*����Ĭ�ϵ�ƽ*/
	MySPI_W_SS(1);											//SSĬ�ϸߵ�ƽ
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
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);	//�ȴ��������ݼĴ�����
	
	// д�� DRʱ �Զ���� TXE��־λ
	SPI_I2S_SendData(SPI1, ByteSend);								//д�����ݵ��������ݼĴ�������ʼ����ʱ��
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);	//�ȴ��������ݼĴ����ǿ�
	
	// ��ȡ DRʱ �Զ���� RXE��־λ
	return SPI_I2S_ReceiveData(SPI1);								//��ȡ���յ������ݲ�����
}






