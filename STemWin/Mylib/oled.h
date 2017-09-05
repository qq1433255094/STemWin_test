#ifndef __OLED_H__
#define __OLED_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system_stm32f4xx.h" 

#define LCD_SCL_PIN GPIO_PIN_0  //DO
#define LCD_SDA_PIN GPIO_PIN_1  //DI
#define LCD_RST_PIN GPIO_PIN_2
#define LCD_DC_PIN  GPIO_PIN_3

#define LCD_GPIO			  GPIOE
#define __OLED_CLK_ENABLE() __GPIOE_CLK_ENABLE()
	
#define  OLED_Configuration() OLED_init()  

void OLED_init(void);
void OLED_Print(unsigned char x, unsigned char y, char ch[]);
void OLED_Printf(unsigned char x,unsigned char y,const char *fmt,...);
void LCD_P8x16Str(unsigned char x,unsigned char y,char ch[]);
void oled_delay_us(unsigned int t);
void oled_delay_ms(unsigned int t);
void OLED_PrintN(unsigned char x, unsigned char y, char *fmt, int num);

void OLED_Clear(void);
void plot(unsigned char data[]);
void plot1(unsigned char data[]);
void line(unsigned char x);
void plot_128(unsigned char data[]);
void oled_img_display(char *buff);
void Set_Display_On_Off(unsigned char d);
void oled_img_apart_display(uint8_t *buff_in);
void LCD_WrDat(unsigned char data);
void buff_format_conversion(uint8_t *buff_in, uint8_t *buff_out);
void buff_format_conversion_8(uint8_t *buff_in, uint8_t *buff_out);
void buff_format_conversion_128(uint8_t *buff_in, uint8_t *buff_out, uint16_t index);

#ifdef __cplusplus
}
#endif

#endif 
