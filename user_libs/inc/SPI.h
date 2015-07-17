/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
 #include "stm32f4xx_spi.h"

/* Exported functions ------------------------------------------------------- */
 void SPI_Initialize(void);
 void SPI_read( uint8_t address, uint8_t *rxbuff);
 void SPI_write( uint8_t address,  uint8_t *txbuff);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_IT_H */
