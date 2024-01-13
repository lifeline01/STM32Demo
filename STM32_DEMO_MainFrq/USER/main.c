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
	
	OLED_ShowString(1, 1, "SYSCLK:");
	// �� system�ļ����޸���Ƶ
	OLED_ShowNum(1, 8, SystemCoreClock, 8);
	
	while(1)
	{
		
	}
}

