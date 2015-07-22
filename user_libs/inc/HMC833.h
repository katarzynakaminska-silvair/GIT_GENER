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

//PLL REGISTER MAP
#define HMC833_REG_ID				0x00
#define HMC833_REG_OM_RX_ADDR		0x00
#define HMC833_REG_RST				0x01
	#define PLL_VIA_CEN_EN			0x01
	#define PLL_VIA_SPI_EN			0x00
	#define PLL_SPI_EN				0x02
	#define PLL_BIAS_ON				0x04
	#define PLL_PD_ON				0x08
	#define PLL_CP_ON				0x10
	#define PLL_REF_BUF_ON			0x20
	#define PLL_VCO_ON				0x40
	#define PLL_GPIO_DRIVER_ON		0x80


#define HMC833_REG_REFDIV			0x02
	#define PLL_REFERENCE_DIV(N)	N
#define HMC833_REG_FREQ				0x03
	#define PLL_DIV_INT_PART(N)		N
#define HMC833_REG_FREQ_FRACT		0x04
	#define PLL_DIV_FRACT_PART(N)	N
#define HMC833_REG_SPI				0x05
	#define PLL_SUBSYS_ID(N)		N & 0x07
	#define	PLL_REG_ADDR(VCO_ADD)	VCO_ADD
#define PLL_DATA(N)					N

#define HMC833_REG_SD_CFG			0x06
	#define PLL_SEED_0				0x00
	#define PLL_SEED_LSB			0x01
	#define PLL_SEED_B29D08			0x02
	#define PLL_SEED_50F1CD			0x03
	#define PLL_MODUL_1_ORD			0x00
	#define PLL_MODUL_2_ORD			0x04
	#define PLL_MODE_B				0x08
	#define PLL_MODE_A				0x0C
	#define PLL_USE_MODULATOR		0x00
	#define PLL_BYPASS_MODULATOR	0x80
	#define PLL_LOAD_SEED			0x100
	#define PLL_PREVIOUS			0x00
	#define PLL_CLK_VCO_DIV			0x200
	#define PLL_CLK_REF_DIV			0x00
	#define PLL_MODUL_CLK_SELECT	0x400
	#define PLL_FRAC_CORE_DIS		0x00
	#define PLL_FRAC_CORE_EN		0x800
	#define PLL_RDiv_BIST_CYC_1032	0x00
	#define PLL_RDiv_BIST_CYC_2047	0x80000
	#define PLL_RDiv_BIST_CYC_3071	0x100000
	#define PLL_RDIV_BIST_CYC_4095	0x180000
	#define PLL_AUTO_CLK_CONFIG		0x200000

#define HMC833_REG_LOCK_DETECT 		0x07
	#define	PLL_WINCNT_5			0x00
	#define	PLL_WINCNT_32			0x01
	#define	PLL_WINCNT_96			0x02
	#define	PLL_WINCNT_256			0x03
	#define	PLL_WINCNT_512			0x04
	#define	PLL_WINCNT_2048			0x05
	#define	PLL_WINCNT_8192			0x06
	#define	PLL_WINCNT_65535		0x07
	#define	PLL_INT_LOCK_DET_EN		0x08
	#define PLL_LOCK_DET_DIGITAL	0x40
	#define PLL_LOCK_DET_ANALOG		0x00
	#define PLL_WIN_DURATION_0_5	0x00
	#define PLL_WIN_DURATION_1		0x80
	#define PLL_WIN_DURATION_2		0x100
	#define PLL_WIN_DURATION_4		0x180
	#define PLL_WIN_DURATION_8		0x200
	#define PLL_WIN_DURATION_16		0x280
	#define PLL_WIN_DURATION_32		0x300
	#define PLL_WIN_DURATION_64		0x380
	#define PLL_TIMER_FREQ_FASTEST 	0x00
	#define PLL_TIMER_FREQ_FAST 	0x400
	#define PLL_TIMER_FREQ_LOW 		0x800
	#define PLL_TIMER_FREQ_LOWEST 	0xC00
	#define PLL_TEST_MODE_ON		0x1000
	#define PLL_AUTO_RELOCK			0x2000

#define HMC833_REG_ANALOG_EN 		0x08
	#define PLL_BIAS_EN				0x01
	#define PLL_CHARGE_PUMP_EN		0x02
	#define PLL_PD_EN				0x04
	#define PLL_REF_CH_PUMP_EN		0x08
	#define PLL_VCO_BUFF_EN			0x10
	#define PLL_GPO_PAD_EN			0x20
	#define PLL_VCO_DIV_CLK_TO_DIG	0x80
	#define PLL_PRESC_CLK_EN		0x100
	#define PLL_BUF_PRESC_BIAS_EN	0x200
	#define PLL_INT_OP_CH_PUMP_EN	0x400
	#define PLL_RESERVED			0x1B000
	#define PLL_HIGH_F_REF_UP_200M	0x200000
	#define PLL_HIGH_F_REF_DOWN_200M 0x00

#define HMC833_REG_CHARGE_PUMP 		0x09
	#define PLL_CP_DN_GAIN_20UX(N) 	N
	#define PLL_CP_UP_GAIN_20UX(N) 	(N&0x7F)<<7
	#define PLL_OFFSET_MAG_5UX(N) 	(N&0x7F)<<14
	#define PLL_OFFSET_UP_EN		0x200000
	#define PLL_OFFSET_DN_EN		0x400000
	#define PLL_HIGH_CURRENT_PUMP	0x800000

#define HMC833_REG_VCO_AUTOCAL 		0x0A
	#define PLL_V_TUNE_RESOL2POW(N)	N
	#define PLL_VCO_CURVE_ADJ_DIS	0x00
	#define PLL_VCO_CURVE_ADJ_P1	0x08
	#define PLL_VCO_CURVE_ADJ_P2	0x10
	#define PLL_VCO_CURVE_ADJ_P3	0x18
	#define PLL_VCO_CURVE_ADJ_1		0x20
	#define PLL_VCO_CURVE_ADJ_2		0x30
	#define PLL_VCO_CURVE_ADJ_3		0x38
	#define PLL_WAIT_STARTUP		0x00
	#define PLL_WAIT_1T				0x40
	#define PLL_WAIT_2T				0x80
	#define PLL_WAIT_3T				0xC0
	#define PLL_SAR_VCO_8			0x00
	#define	PLL_FSM_CLK_XTAL		0x00
	#define	PLL_FSM_CLK_XTAL_4		0x2000
	#define	PLL_FSM_CLK_XTAL_16		0x4000
	#define	PLL_FSM_CLK_XTAL_32		0x6000
	#define	PLL_XTAL_EDGE_BIST		0x8000
	#define PLL_RDIVIDER_BYPASS		0x10000

#define HMC833_REG_PD 				0x0B
	#define PLL_DELAY(N)			N&0x07
	#define PLL_SHORT_INPUTS		0x08
	#define PLL_INVERT_PD_POLARITY	x10
	#define PLL_ENABLE_PD_UP		0x20
	#define PLL_ENABLE_PD_DOWN		0x40
	#define PLL_CSPM_DISABLE		0x00
	#define PLL_CSPM_4_4NS			0x80
	#define PLL_CSPM_14_4NS			0x100
	#define PLL_CSPM_24_1NS			0x180
	#define	PLL_FORCE_CP_UP			0x200
	#define	PLL_FORCE_CP_DOWN		0x400
	#define	PLL_FORCE_CP_MLD		0x800
	#define PLL_MCOUNTER_OFF		0x00
	#define PLL_MCOUNTER_LESS128	0x20000
	#define PLL_MCOUNTER_LESS1023	0x40000
	#define PLL_MCOUNTER_ALL_CLK_ON	0x80000

#define HMC833_EXACT_FREQ_MODE	 	0x0C
//	#define PLL_GPO_REG_0F			0x
//	#define PLL_GPO_LD_OUT			0x
//	#define PLL_GPO_LD_TRIG			0x
//	#define PLL_GPO_LD_WIN_OUT		0x
//	#define PLL_GPO_RING_OSC_TEST	0x
//	#define PLL_GPO_PU_CSP			0x
//	#define PLL_GPO_PD_CSP			0x
//	#define PLL_GPO_REF_BUF_OUT		0x
//	#define PLL_GPO_REF_DIV_OUT		0x
//	#define PLL_GPO_VCO_DIV_OUT		0x
//	#define PLL_GPO_MOD_CLK			0x
//	#define PLL_GPO_AUX_CLK			0x
//	#define PLL_GPO_AUX_SPI_CLK		0x
//	#define PLL_GPO_AUX_SPI_EN		0x
//	#define PLL_GPO_AUX_SPI_OUT		0x
//	#define PLL_GPO_PD_DN			0x
//	#define PLL_GPO_PD_UP			0x


#define HMC833_REG_GPO_SPI_RDIV			0x0F
	#define HMC833_REG_VCO_TUNE			0x10
	#define HMC833_REG_SAR				0x11
	#define HMC833_REG_GPO2				0x12
	#define HMC833_REG_BIST				0x13

// VCO REG MAP ( via 05 register)
#define HMC833_REG_VCO_TUNING		0x00
	#define VCO_CAL_0				0x00
	#define VCO_CAL_1				0x01
	#define SUB_BAND(N)				N<<1

#define HMC833_REG_VCO_ENABLES		0x01
	#define VCO_BLOCK_SUBSYS		0x00
	#define VCO_MASTER_EN			0x01
	#define VCO_PLL_MANUAL_EN		0x02
	#define VCO_RF_MANUAL_EN		0x04
	#define VCO_MANUAL_DIV_1		0x08
	#define VCO_RF_DIV_EN			0x10

#define HMC833_REG_VCO_BIASES		0x02
	#define VCO_DIV_RATIO(N)		N
	#define VCO_RF_MAX_GAIN			0xC0
	#define VCO_RF_MAX_GAIN_3DB		0x80
	#define VCO_RF_MAX_GAIN_6DB		0x40
	#define VCO_RF_MAX_GAIN_9DB		0x00
	#define VCO_DIV_MAX_GAIN		0x100
	#define VCO_DIV_MAX_GAIN_3DB	0x00

#define HMC833_REG_VCO_CONFIG		0x03
	#define VCO_FREQ_DOUBLER_EN		0x00
	#define	VCO_FUNDAMENTAL_EN		0x01
	#define VCO_AUTO_RFO			0x00
	#define VCO_MANUAL_RFO			0x04
	#define VCO_OVER_3G				0x10
	#define VCO_UNDER_3G			0x00

#define HMC833_REG_VCO_CAL_BIAS		0x04
#define HMC833_REG_VCO_CF_CAL		0x05
#define HMC833_REG_VCO_MSB_CAL		0x06



#define HMC833_CEN GPIO_Pin_8 // GPIOD
#define HMC833_SEN GPIO_Pin_12 //GPIOB


inline void HMC833_send_zero_to_05reg(void);
void HMC833_set_frequency(double freq);


#endif
