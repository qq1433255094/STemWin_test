#ifndef __SPI1_H__
#define __SPI1_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system_stm32f4xx.h"  

#define Accel_CS_HIGH() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET)
#define Accel_CS_LOW()  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET)

#define Si4332_CS_HIGH() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET)
#define Si4332_CS_LOW()  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET)

HAL_StatusTypeDef spi1_init(void);
uint8_t SPI1_WriteRead(uint8_t Byte);
void SPI_Write(uint8_t *buff, uint16_t size);
void SPI1_DMA_Write(uint8_t *buff, uint16_t size);
uint8_t DMA_Status();

#ifdef __cplusplus
}
#endif

#endif
