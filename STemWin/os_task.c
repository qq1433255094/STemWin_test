
#include "os_task.h"
#include "tim3.h"
#include <math.h>
#include "arm_math.h"
#include "oled.h"
#include "GUI.h"
#include "LCDConf.h"
#include "FreeRTOSConfig.h"
#include "spi1.h"

CREATE_TASK_DEFINE(TEST);
CREATE_TASK_DEFINE(DISPLAY);


void os_task_init(void)
{
	CREATE_TASK_HANDLE(TEST, osPriorityNormal);
	CREATE_TASK_HANDLE(DISPLAY, osPriorityNormal);
}

void os_task_start ( void )
{
	/* Start scheduler */
	//osThreadSuspend(os_ThreadHandle(TEST));
	osKernelStart ();
}

GUI_POINT point[] = {
	{10,10},
	{20,15},
	{15,20}
};


os_exec(TEST){
	(void)argument;
	int32_t tick = 0,i=2;
	GUI_Clear();
	for (; ; )
	{
		//GUI_DrawRect(10, 10, i++, 15);
		//if (i == 100)
		//{
		//	i = 10;
		//	GUI_ClearRect(10, 10, 100, 15);
		//	GUI_DrawRect(10, 10, 100, 15);
		//}

		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		GUI_SetColor(GUI_BLACK);
		GUI_DrawRect(10, 10, 50, 50);



		osDelay(100);

//		GUI_SetBkColor(GUI_INVALID_COLOR);

		//MainTask();
	}
}

os_exec(DISPLAY) {
	(void)argument;

	for (; ; )
	{
		
		for (uint8_t i=0;i<8;i++)
		{
			oled_img_apart_display(GUI_GET_VRAM_ADDR());
			while (DMA_Status() != 1)
				osDelay(1);
		}

		osDelay(5);
	}
}
