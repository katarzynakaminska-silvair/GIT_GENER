#ifndef __HMC624_H_
#define __HMC624_H_


#include "stm32f4xx_conf.h"
#include "measurement functions.h"


//GPIOB
#define HMC624_ATTEN_LE GPIO_Pin_0
//GPIOC
#define HMC624_ATTEN_D0 GPIO_Pin_5
#define HMC624_ATTEN_D1 GPIO_Pin_4
// GPIOA
#define HMC624_ATTEN_D2 GPIO_Pin_7
#define HMC624_ATTEN_D3 GPIO_Pin_6
#define HMC624_ATTEN_D4 GPIO_Pin_5
#define HMC624_ATTEN_D5 GPIO_Pin_4

//Exported functions
inline void HMC624_init(void);
inline void HMC624_set_attenuation(float attenuation);

#endif
