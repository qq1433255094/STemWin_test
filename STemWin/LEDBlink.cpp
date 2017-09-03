#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
#include "GUI.h"
#include "oled.h"

extern volatile GUI_TIMER_TIME OS_TimeMS;
extern char dis_buff[128 * 64];

#ifdef __cplusplus
extern "C"
#endif
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	OS_TimeMS++;
	HAL_SYSTICK_IRQHandler();
}

int (*init)(void);

int main(void)
{
	HAL_Init();
	
	OLED_init();

	__HAL_RCC_CRC_CLK_ENABLE();
	
	GUI_Init();
	
	GUI_Clear();

	GUI_DispString("hello");

	oled_img_display(dis_buff);
	
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_13;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	for (;;)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}
