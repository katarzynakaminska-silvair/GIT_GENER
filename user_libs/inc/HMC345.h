#ifndef __HMC345_H_
#define __HMC345_H_


#include "stm32f4xx_conf.h"

//GPIOE
#define HMC345_1_CTLA GPIO_Pin_12
#define HMC345_1_CTLB GPIO_Pin_13

#define HMC345_2_CTLA GPIO_Pin_15
#define HMC345_2_CTLB GPIO_Pin_14

// Path 1 - LPF 2,75GHz
#define HMC345_PATH_1 0b00001100
// Path 2 - BPF 2,7 - 5Ghz
#define HMC345_PATH_2 0b00000110
// Path 3 - BPF 4,7 - 6GHz
#define HMC345_PATH_3 0b00001001
// Path 4 - 4x multiplier, BPF 5,5 - 10,6GHz
#define HMC345_PATH_4 0b00000011

void HMC345_init(void);
void HMC345_set_path(uint8_t path);
#endif
