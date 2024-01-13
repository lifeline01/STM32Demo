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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	
	while(1)
	{
		// 停止模式配置，外部中断唤醒
		// EXTI不需要时钟
		
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		// 重新配置系统时钟
		SystemInit();
	}
}

