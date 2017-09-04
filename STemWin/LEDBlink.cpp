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
void setSystemClock(void);

int main(void)
{
	int16_t main_tick = 0,oled_tick;

	setSystemClock();
	SystemCoreClockUpdate();
	HAL_Init();

	__HAL_RCC_CRC_CLK_ENABLE();
	
	GUI_Init();
	
	GUI_Clear();

	GUI_DispString(" hello");

	GUI_DrawRect(10, 10, 100, 15);

	oled_img_display(dis_buff);

	
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_13;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	int i = 10;
	uint8_t data;
	uint32_t time_test = HAL_GetTick();

	for (uint32_t i = 0; i < 1000; i++)
	{
		oled_img2_display(dis_buff);
	}

	time_test = HAL_GetTick() - time_test;
	HAL_Delay(1);


	for (;;)
	{
		main_tick = HAL_GetTick() % 50;
		if (main_tick == 10)
		{
			
			GUI_DrawRect(10, 10, i++, 15);
			if (i == 100)
			{
				i = 10;
				GUI_ClearRect(10, 10, 100, 15);
				GUI_DrawRect(10, 10, 100, 15);
			}
		}


		for (uint32_t i = 0; i < 3; i++)
		{
			oled_img2_display(dis_buff);
		}


	}
}


void setSystemClock(void)
{
	/******************************************************************************/
	/*            PLL (clocked by HSE) used as System clock source                */
	/*            System clock source = HSE / PLL_M *  PLL_N / PLL_P              */
	/******************************************************************************/

#ifndef HSE_STARTUP_TIMEOUT
	uint32_t HSE_STARTUP_TIMEOUT = 1000;
#endif // !HSE_STARTUP_TIMEOUT

	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	uint16_t	PLL_M = 8,
		PLL_N = 336,
		PLL_P = 2,
		PLL_Q = 7,
		PLLI2S_N = 302,
		PLLI2S_R = 2;

	/* Enable HSE */
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);

	/* Wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while (HSEStatus == 0);// && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
	{
		HSEStatus = (uint32_t)0x01;
	}
	else
	{
		HSEStatus = (uint32_t)0x00;
	}

	if (HSEStatus == (uint32_t)0x01)
	{
		/* Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz */
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR |= PWR_CR_VOS;

		/* HCLK = SYSCLK / 1*/
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

		/* PCLK2 = HCLK / 2*/
		RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

		/* PCLK1 = HCLK / 4*/
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

		/* Configure the main PLL */
		RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) - 1) << 16) |
			(RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

		RCC->PLLI2SCFGR = (PLLI2S_R << 28) + (PLLI2S_N << 6);

		/* Enable the main PLL and PLLI2S*/
		RCC->CR |= RCC_CR_PLLON | RCC_CR_PLLI2SON;

		/* Wait till the main PLL is ready */
		while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		{
		}

		/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

		/* Select the main PLL as system clock source */
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= RCC_CFGR_SW_PLL;

		/* Wait till the main PLL is used as system clock source */
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
			;
		{
		}
	}
	else
	{ /* If HSE fails to start-up, the application will have wrong clock
	  configuration. User can add here some code to deal with this error */
	}

}
