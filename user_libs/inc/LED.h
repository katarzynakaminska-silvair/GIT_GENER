#ifndef __LED_H_
#define __LED_H_

#include "stm32f4xx_conf.h"

//GPIOD
#define LED_GREEN	 GPIO_Pin_12
#define LED_BLUE	 GPIO_Pin_11
#define LED_ORANGE 	 GPIO_Pin_10
#define LED_RED 	 GPIO_Pin_9

inline void LED_init();
inline void LED_on(uint16_t LED);
inline void LED_off(uint16_t LED);
inline void LED_toggle(uint16_t LED);


#endif
