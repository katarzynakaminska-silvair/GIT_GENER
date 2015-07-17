#include "HMC624.h"

inline void HMC624_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin =  HMC624_ATTEN_D2 |HMC624_ATTEN_D3 | HMC624_ATTEN_D4 | HMC624_ATTEN_D5;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  HMC624_ATTEN_D0 | HMC624_ATTEN_D1 ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  HMC624_ATTEN_LE ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


}

//TODO: optimize this function
inline void HMC624_set_attenuation(float attenuation)
{
	uint8_t config_record =  ((int)roundf((attenuation*2.0f)));
	GPIO_ResetBits(GPIOB,HMC624_ATTEN_LE);

	GPIO_SetBits(GPIOC,HMC624_ATTEN_D0 | HMC624_ATTEN_D1);
	GPIO_SetBits(GPIOA,HMC624_ATTEN_D2 |HMC624_ATTEN_D3 | HMC624_ATTEN_D4| HMC624_ATTEN_D5);
	if((config_record & 0b00100000)>>5) GPIO_ResetBits(GPIOA, HMC624_ATTEN_D5);
	if((config_record & 0b00010000)>>4) GPIO_ResetBits(GPIOA, HMC624_ATTEN_D4);
	if((config_record & 0b00001000)>>3) GPIO_ResetBits(GPIOA, HMC624_ATTEN_D3);
	if((config_record & 0b00000100)>>2) GPIO_ResetBits(GPIOA, HMC624_ATTEN_D2);
	if((config_record & 0b00000010)>>1) GPIO_ResetBits(GPIOC, HMC624_ATTEN_D1);
	if((config_record & 0b00000001)   ) GPIO_ResetBits(GPIOC, HMC624_ATTEN_D0);

	GPIO_SetBits(GPIOB,HMC624_ATTEN_LE);

}
