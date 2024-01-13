#include "stm32f10x.h"
#include "Delay.h"
#include "led.h"
#include "Encoder.h"

int16_t Speed;


/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	LEDInit();
	Encoder_Init();
	// 1s 定时中断，获取编码器 CNT值用来反映速度
	TIM2_IT_Init(10000 -1, 7200 - 1);
	
	while(1)
	{
		
	}
}

