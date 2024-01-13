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
	
	OLED_ShowString(1, 1, "WWDG Test");
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		OLED_ShowString(2, 1, "WWDGRST");
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
	
	// ��ʼ�����ڿ��Ź�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	// ����Ԥ��Ƶ
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	// ���ô���ֵ-30ms-50ms
	// ��ʱʱ�䣺(1 / 36MHz) X 4096 X 8 X (54 + 1) = 50ms
	// ����ʱ�䣺(1 / 36MHz) X 4096 X 8 X (54 - 33) = 30ms
	WWDG_SetWindowValue(0x40 | 21);
	// ʹ�ܣ�������ǵ�һ��ι����
	// 54ֻ�� T5:0��ֵ����Ҫ�� T6��ֵ��1����˻��� 0x40
	WWDG_Enable(0x40 | 54);
	
	while(1)
	{
		// ����50ms����С��30ms�����Ź��������λ
		Delay_ms(60);
		// Delay_ms(20);
		// ι������ʹ�ܿ��Ź��Ǵ�ι��֮�䲻��С�ڴ���ֵ����������ι����ѭ��
		WWDG_SetCounter(0x40 | 54);
	}
}

