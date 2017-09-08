
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
		//GUI_DispStringAt("aa", 5, 5);
		//GUI_DispStringAt("aa", 5, 15);
		//GUI_DispStringAt("aa", 5, 25);

		//GUI_Delay(10);
		//GUI_DrawRect(3, 5, 25, 13);
		//GUI_DrawRect(3, 15, 25, 23);
		//GUI_DrawRect(3, 25, 25, 33);

		//GUI_SetDrawMode(GUI_DM_XOR);

		//while (1) {
		//	GUI_FillRect(4, 6, 24, 12);
			osDelay(2000);
		//	GUI_FillRect(4, 6, 24, 12);

		//	GUI_FillRect(4, 16, 24, 22);
		//	osDelay(2000);
		//	GUI_FillRect(4, 16, 24, 22);

		//	GUI_FillRect(4, 26, 24, 32);
		//	osDelay(2000);
		//	GUI_FillRect(4, 26, 24, 32);
		//}
		MainTask();
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
