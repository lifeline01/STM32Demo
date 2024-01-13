#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

uint8_t ID;								//�������ڴ��ID�ŵı���
int16_t AX, AY, AZ, GX, GY, GZ;			//�������ڴ�Ÿ������ݵı���

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	OLED_Init();
	MPU6050_Init();
	
	/*��ʾID��*/
	OLED_ShowString(1, 1, "ID:");		//��ʾ��̬�ַ���
	ID = MPU6050_GetID();				//��ȡMPU6050��ID��
	OLED_ShowHexNum(1, 4, ID, 2);		//OLED��ʾID��
	
	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);		//��ȡMPU6050������
		OLED_ShowSignedNum(2, 1, AX, 5);					//OLED��ʾ����
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
}

