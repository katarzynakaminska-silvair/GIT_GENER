#ifndef __HMC833_H_
#define __HMC833_H_

#include "stm32f4xx_conf.h"


typedef struct
{
	uint8_t VCO_reg02[3];

} Current_HMC833_config;

extern uint8_t  r[3];

#define TRUE 1
#define FALSE 0

#define TWO_POW_24 0x1000000

#define ATTEN1_0 0x00
#define ATTEN1_3 0x01
#define ATTEN1_6 0x02
#define ATTEN1_9 0x03

#define ATTEN2_0 0x00
#define ATTEN2_3 0x01

#define XREFP_DIV_R_FREQ_MHZ 10.0

//PLL REGISTER MAP
#define HMC833_REG_ID				0x00
#define HMC833_REG_OM_RX_ADDR		0x00
#define HMC833_REG_RST				0x01
#define HMC833_REG_REFDIV			0x02
#define HMC833_REG_FREQ				0x03
#define HMC833_REG_FREQ_FRACT		0x04
#define HMC833_REG_SPI				0x05
#define HMC833_REG_SD_CFG			0x06
#define HMC833_REG_LOCK_DETECT 		0x07
#define HMC833_REG_ANALOG_EN 		0x08
#define HMC833_REG_CHARGE_PUMP 		0x09
#define HMC833_REG_VCO_AUTOCAL 		0x0A
#define HMC833_REG_PD 				0x0B
#define HMC833_EXACT_FREQ_MODE	 	0x0C
#define HMC833_REG_GPO_SPI_RDIV		0x0F
#define HMC833_REG_VCO_TUNE			0x10
#define HMC833_REG_SAR				0x11
#define HMC833_REG_GPO2				0x12
#define HMC833_REG_BIST				0x13

// VCO REG MAP ( via 05 register)
#define HMC833_REG_VCO_TUNING		0x00
#define HMC833_REG_VCO_ENABLES		0x01
#define HMC833_REG_VCO_BIASES		0x02
#define HMC833_REG_VCO_CONFIG		0x03
#define HMC833_REG_VCO_CAL_BIAS		0x04
#define HMC833_REG_VCO_CF_CAL		0x05
#define HMC833_REG_VCO_MSB_CAL		0x06

#define HMC833_CEN GPIO_Pin_8 // GPIOD
#define HMC833_SEN GPIO_Pin_12 //GPIOB


inline void HMC833_send_zero_to_05reg(void);
uint8_t HMC833_is_busy(void);
void HMC833_set_frequency(double freq);
void HMC833_set_atten1(uint8_t attenuation1);
void HMC833_set_atten2(uint8_t attenuation1);
void HMC833_set_divider(uint8_t div);


#endif
