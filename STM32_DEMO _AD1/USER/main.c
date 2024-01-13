#include "stm32f10x.h"
#include "Delay.h"
#include "ADC.h"


/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	uint16_t ADValue;
	float Voltage;
	
	ADC1Init();
	
	while(1)
	{
		ADValue = ADC1_GetValue();
		// 均值滤波，设置两个阈值（施密特触发器），减少数据波动。
		
		Voltage = (float)ADValue / 4095  * 3.3;
	}
}

