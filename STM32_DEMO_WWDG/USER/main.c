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
	
	// 初始化窗口看门狗
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	// 设置预分频
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	// 设置窗口值-30ms-50ms
	// 超时时间：(1 / 36MHz) X 4096 X 8 X (54 + 1) = 50ms
	// 窗口时间：(1 / 36MHz) X 4096 X 8 X (54 - 33) = 30ms
	WWDG_SetWindowValue(0x40 | 21);
	// 使能，这里就是第一次喂狗了
	// 54只是 T5:0的值，需要把 T6的值置1，因此或上 0x40
	WWDG_Enable(0x40 | 54);
	
	while(1)
	{
		// 超过50ms或者小于30ms，看门狗会产生复位
		Delay_ms(60);
		// Delay_ms(20);
		// 喂狗，和使能看门狗那次喂狗之间不能小于窗口值，否则陷入喂狗死循环
		WWDG_SetCounter(0x40 | 54);
	}
}

