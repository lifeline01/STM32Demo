#include "stm32f10x.h"
#include "Delay.h"
#include "led.h"
#include "timer.h"

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	LEDInit();
	// TIM3 output 
	PWM_SetPrescaler(720 - 1);		// 72000000 / 100 / PSC + 1;
	PWM_SetCompare1(50);
	
	while(1)
	{
		
	}
}

