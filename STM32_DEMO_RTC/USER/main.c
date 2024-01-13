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
	
	
	while(1)
	{
		MyRTC_ReadTime();
		
		OLED_ShowNum(1, 6, MyRTC_Time[0], 4);
		OLED_ShowNum(1, 11, MyRTC_Time[1], 2);
		OLED_ShowNum(1, 12, MyRTC_Time[2], 2);
		OLED_ShowNum(2, 6, MyRTC_Time[3], 2);
		OLED_ShowNum(2, 9, MyRTC_Time[4], 2);
		OLED_ShowNum(2, 12, MyRTC_Time[5], 2);
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
	}
}

