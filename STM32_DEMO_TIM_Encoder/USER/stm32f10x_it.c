#include "stm32f10x_it.h"
#include "Encoder.h"

extern int16_t Speed;

/**
  * @brief  处理按键2中断
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == 1)
	{
		//
		EXTI_ClearFlag(EXTI_Line1);
	}
}



/**
  * @brief  处理定时器2中断
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == 1)
	{
		Speed = EncoderGet();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}



