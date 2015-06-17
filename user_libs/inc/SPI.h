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
 void SPI_read_write( uint8_t *initbuff, uint16_t quantity, uint8_t *rxbuff, uint8_t *txbuff, uint8_t read);
 uint8_t  SPI_readOC(uint8_t opcode);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_IT_H */
