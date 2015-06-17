#include "HMC345.h"

void HMC345_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin =  HMC345_1_CTLA |HMC345_1_CTLB | HMC345_2_CTLA| HMC345_2_CTLB;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void HMC345_set_path(uint8_t path)
{
	if((path & 0b00001000)>>3) GPIO_SetBits(GPIOD, HMC345_1_CTLA);
	else GPIO_ResetBits(GPIOD, HMC345_1_CTLA);
	if((path & 0b00001000)>>2) GPIO_SetBits(GPIOD, HMC345_1_CTLA);
	else GPIO_ResetBits(GPIOD, HMC345_1_CTLB);
	if((path & 0b00001000)>>1) GPIO_SetBits(GPIOD, HMC345_2_CTLB);
	else GPIO_ResetBits(GPIOD, HMC345_2_CTLA);
	if((path & 0b00001000))    GPIO_SetBits(GPIOD, HMC345_2_CTLB);
	else GPIO_ResetBits(GPIOD, HMC345_2_CTLB);
}
