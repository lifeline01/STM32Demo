#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	OLED_Init();
	
	// BKP��ʼ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	// PWR���ݷ��ʿ���
	PWR_BackupAccessCmd(ENABLE);
	
	BKP_WriteBackupRegister(BKP_DR1, 0x1234);
	uint16_t data = BKP_ReadBackupRegister(BKP_DR1);
	
	while(1)
	{
		
	}
}

