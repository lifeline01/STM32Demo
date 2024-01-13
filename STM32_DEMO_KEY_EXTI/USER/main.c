#include "stm32f10x.h"
#include "Delay.h"
#include "led.h"
#include "key.h"

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	LEDInit();
	KeyInit();
	
	Key_x keytemp1, keytemp2;
	
	while(1)
	{
		// 按键消抖
		keytemp1 = KeyDetect();
		Delay_ms(20);
		keytemp2 = KeyDetect();
		if ((keytemp1 & keytemp2) == 1)
		{
			LED_Toggle(LED1);
		}
	}
}

