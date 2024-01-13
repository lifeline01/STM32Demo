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
	uint16_t AD0, AD1;
	
	ADC1Init();
	
	while(1)
	{
		AD0 = ADC1_GetValue(ADC_Channel_0);
		AD1 = ADC1_GetValue(ADC_Channel_1);
		
	}
}

