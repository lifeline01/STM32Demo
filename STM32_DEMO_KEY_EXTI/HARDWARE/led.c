#include "led.h"


/**
 * @brief  Led初始化.
 * @param  None
 * @retval None
 */
void LEDInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED1_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);
}


/**
 * @brief  Led打开.
 * @param  None
 * @retval None
 */
void LED_On(Led_x led)
{
	if (led == LED1)
	{
		GPIO_SetBits(LED1_PORT, LED1_PIN);
	}
}


/**
 * @brief  Led关闭.
 * @param  None
 * @retval None
 */
void LED_Off(Led_x led)
{
	if (led == LED1)
	{
		GPIO_ResetBits(LED1_PORT, LED1_PIN);
	}
}


/**
 * @brief  Led亮灭切换.
 * @param  None
 * @retval None
 */
void LED_Toggle(Led_x led)
{
	if (led == LED1)
	{
		if (GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN) == 0)
		{
			GPIO_SetBits(LED1_PORT, LED1_PIN);
		}
		else
		{
			GPIO_ResetBits(LED1_PORT, LED1_PIN);
		}
	}
}


