#include "HMC833.h"
#include "SPI.h"

uint8_t r[3] = {0};
Current_HMC833_config Current_HMC833_config_inst;

void HMC833_set_clockout()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9 , GPIO_AF_MCO);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init( GPIOC, &GPIO_InitStructure);
	RCC_MCO2Config(RCC_MCO2Source_HSE, RCC_MCO2Div_1);

	// No need for register config. In case of changing MCO2 reg do it before HSE enabling.
	//MCO2[1:0] = 00 SYSCLK
	//MCO2PRE = 000 DIV = NO
}

void HMC833_initial_config(void)
{
	Current_HMC833_config_inst.VCO_reg02[0] = 0x00;
	Current_HMC833_config_inst.VCO_reg02[1] = 0x60;
	Current_HMC833_config_inst.VCO_reg02[2] = 0x90;

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x02;
	SPI_write(HMC833_REG_RST , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x01;
	SPI_write(HMC833_REG_REFDIV , r);

	r[0] = 0x00;
	r[1] = 0x16;
	r[2] = 0x28;
	SPI_write(HMC833_REG_SPI , r);

	r[0] = 0x00;
	r[1] = 0x60;
	r[2] = 0xa0;
	SPI_write(HMC833_REG_SPI , r);

	/////////////////////////////
//	r[0] = 0x00;
//	r[1] = 0x2A;
//	r[2] = 0x98;
//	SPI_write(0x05 , r);

	HMC833_send_zero_to_05reg();
//intiger
//	r[0] = 0x20;
//	r[1] = 0x03;
//	r[2] = 0xca;
//fractional
	r[0] = 0x20;
	r[1] = 0x0b;
	r[2] = 0x4a;
	SPI_write(HMC833_REG_SD_CFG , r);

	r[0] = 0x00;
	r[1] = 0x01;
	r[2] = 0x4d;
	SPI_write(HMC833_REG_LOCK_DETECT , r);


	r[0] = 0xc1;
	r[1] = 0xbe;
	r[2] = 0xff;
	SPI_write(HMC833_REG_ANALOG_EN , r);
//intiger mode
//	r[0] = 0x00;
//	r[1] = 0x3f;
//	r[2] = 0xff;

	//fractional
	r[0] = 0x54;
	r[1] = 0x7f;
	r[2] = 0xff;
	SPI_write(HMC833_REG_CHARGE_PUMP , r);

	r[0] = 0x00;
	r[1] = 0x20;
	r[2] = 0x46;
	SPI_write(HMC833_REG_VCO_AUTOCAL , r);
//intiger mode
//	r[0] = 0x0f;
//	r[1] = 0x80;
//	r[2] = 0x61;

	//fractional
	r[0] = 0x07;
	r[1] = 0xc0;
	r[2] = 0x21;
	SPI_write(HMC833_REG_PD  , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x00;
	SPI_write(HMC833_EXACT_FREQ_MODE , r);
	SPI_write(0x0d , r);
	SPI_write(0x0e , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x81;
	SPI_write(HMC833_REG_GPO_SPI_RDIV , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0xf0;
	SPI_write(HMC833_REG_FREQ , r);

	r[0] = 0x33;
	r[1] = 0x33;
	r[2] = 0x33;
	SPI_write(0x04 , r);
}

void HMC833_set_frequency(double freq)
{
	uint8_t *temp_ptr;
	long int number = (long int)floor(freq);
	double fraction = freq - (double)number;
	number/=10;
	temp_ptr = &number;
	r[2] = temp_ptr[0];
	r[1] = temp_ptr[1];
	r[0] = temp_ptr[2];
	SPI_write(HMC833_REG_FREQ , r);
	fraction = fraction * TWO_POW_24;
	number = lround(fraction);
	if(number < 16) number = 16;
	r[2] = temp_ptr[0];
	r[1] = temp_ptr[1];
	r[0] = temp_ptr[2];
	SPI_write(HMC833_REG_FREQ_FRACT , r);
}

void HMC833_set_multiplier(uint8_t doubler_not_fundamental)
{
	if(doubler_not_fundamental == TRUE)
	{
		r[0] = 0x00;
		r[1] = 0x00;
		r[2] = 0x18;
	}
	else
	{
		r[0] = 0x00;
		r[1] = 0x08;
		r[2] = 0x98;
	}
	SPI_write(HMC833_REG_SPI , r);

	HMC833_send_zero_to_05reg();
}

void HMC833_set_mute()
{

}

void HMC833_set_atten1(uint8_t attenuation1)
{
	switch (attenuation1)
	{
		case ATTEN1_0:
			Current_HMC833_config_inst.VCO_reg02[1] |= 0b01100000 ;
			break;
		case ATTEN1_3:
			Current_HMC833_config_inst.VCO_reg02[1] |= 0b01000000 ;
			Current_HMC833_config_inst.VCO_reg02[1] &= 0b11011111 ;
			break;
		case ATTEN1_6:
			Current_HMC833_config_inst.VCO_reg02[1] |= 0b00100000 ;
			Current_HMC833_config_inst.VCO_reg02[1] &= 0b10111111 ;
			break;
		case ATTEN1_9:
			Current_HMC833_config_inst.VCO_reg02[1] &= 0b10011111 ;
			break;
	}
	SPI_write(HMC833_REG_SPI , Current_HMC833_config_inst.VCO_reg02);
	HMC833_send_zero_to_05reg();
}

void HMC833_set_atten2(uint8_t attenuation1)
{
	switch (attenuation1)
	{
		case ATTEN2_0:
			Current_HMC833_config_inst.VCO_reg02[1] |= 0x80;
			break;
		case ATTEN2_3:
			Current_HMC833_config_inst.VCO_reg02[1] &= (~0x80);
			break;
	}
	SPI_write(HMC833_REG_SPI , Current_HMC833_config_inst.VCO_reg02);
	HMC833_send_zero_to_05reg();
}

inline void HMC833_send_zero_to_05reg(void)
{
	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x00;
	SPI_write(HMC833_REG_SPI , r);
}

uint8_t HMC833_is_busy(void)
{
	SPI_read( HMC833_REG_VCO_TUNE , r);
	if(r[1]&0b00000001)return TRUE;
	else return FALSE;
}

