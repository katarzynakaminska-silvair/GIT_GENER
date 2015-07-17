#include "HMC833.h"
#include "SPI.h"

void HMC833_read_ID(uint8_t* ID)
{
	SPI_read( HMC833_REG_ID, ID );
}

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

