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
	
	OLED_ShowString(1, 1, "IWDG Test");
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(2, 1, "IWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(500);
		
		RCC_ClearFlag();
	}
	else
	{
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(3, 1, "       ");
		Delay_ms(500);
	}
	
	// ��ʼ���������Ź�
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	// ����Ԥ��Ƶ
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	// ������װ��
	// (1 / 40Mhz) X 16 X 2499 = 1000ms
	IWDG_SetReload(2499);
	// ι��
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	while(1)
	{
		IWDG_ReloadCounter();
		// ����1000ms�����Ź��������λ
		Delay_ms(1200);
	}
}

