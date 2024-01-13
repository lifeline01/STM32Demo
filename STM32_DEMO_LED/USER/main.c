#include "stm32f10x.h"
#include "Delay.h"
#include "led.h"

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	LEDInit();
	while(1)
	{
		LED_On(LED1);
		Delay_ms(100);
		LED_Off(LED1);
		Delay_ms(100);
	}
}

