#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"


/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	OLED_Init();
	MyRTC_Init();
	
	// 开启PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "CNT:");
	OLED_ShowString(2, 1, "ALR:");
	OLED_ShowString(3, 1, "ALRF:");
	
	uint32_t Alarm = RTC_GetCounter() + 10;
	RTC_SetAlarm(Alarm);
	
	while(1)
	{
		OLED_ShowNum(1, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(2, 6, Alarm, 10);
		// 闹钟标志位
		OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 10);
		
		// 进入待机模式之前。外部模块断电
		OLED_Clear();
		
		// 进入待机模式
		PWR_EnterSTANDBYMode();
	}
}

