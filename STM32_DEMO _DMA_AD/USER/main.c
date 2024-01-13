#include "stm32f10x.h"
#include "Delay.h"
#include "ADC.h"

extern uint16_t AD_Value[4];


/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	
	ADC1Init();
	
	while(1)
	{
		ADC1_GetValue();
	}
}

