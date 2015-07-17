#include "TIM.h"

void TIM_delay_ms(uint16_t time)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 		// TIM4 clock enable
	TIM4->PSC = 41999;							// TIM4 prescaler: 84MHZ/(PSC+1)
	TIM4->CR1 &= ~TIM_CR1_DIR;					// Counter used as upcounter
	TIM4->CR1 |= TIM_CR1_ARPE;					// Auto-reload preload enable
	TIM4->ARR = 65535;	///max time=65535		// TIM4 auto-reload value
	TIM4->EGR |= TIM_EGR_UG;					// Update generation
	TIM4->CR1 |= TIM_CR1_CEN;					//Counter enable

	TIM4->CNT = 0;						// counter reset
	TIM4->CR1 |= TIM_CR1_CEN;			//Counter enable
	while (TIM4->CNT <= 2*time); 		// delay time ms
	TIM4->CR1 &= ~TIM_CR1_CEN;			//Counter disable
}

void TIM_delay_us(uint16_t time)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 		// TIM4 clock enable
	TIM4->PSC = 42;								// TIM4 prescaler: 84MHZ/(PSC+1)
	TIM4->CR1 &= ~TIM_CR1_DIR;					// Counter used as upcounter
	TIM4->CR1 |= TIM_CR1_ARPE;					// Auto-reload preload enable
	TIM4->ARR = 65535;	///max time=65535		// TIM4 auto-reload value
	TIM4->EGR |= TIM_EGR_UG;					// Update generation
	TIM4->CR1 |= TIM_CR1_CEN;					//Counter enable

	TIM4->CNT = 0;						// counter reset
	TIM4->CR1 |= TIM_CR1_CEN;			//Counter enable
	while (TIM4->CNT <= 2*time); 		// delay time ms
	TIM4->CR1 &= ~TIM_CR1_CEN;			//Counter disable
}

inline void TIM_warm_up(void)
{
	set_warm_up_state(0);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_Prescaler = 41999; //84M/42k = 2k
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 2000-1;  //2kHz down to 1Hz (1s)
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_InitStruct);

 	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
 	TIM_Cmd(TIM3,ENABLE);

}

//void TIM2_init(void)
//{
//	RCC->AHB1ENR |= 0x01; // Clock for PortA
//	RCC->APB1ENR |= 0x01; // Clock for Timer2
//	RCC->APB1ENR |= 0x08; // Clock for Timer5
//
//	GPIOA->MODER |= 0x00000008; // all inputs but: PA1 => AF mode
//	GPIOA->AFR[0] |= 0x00000010; // select AF1 (TIM2) for PA01 -> TIM2_CH2
//
//
//	TIM2->CCMR1 |= 0x0100; // Ch. 2 as TI2 //CC2S = 01
//	TIM2->SMCR |= 0x0007; // Ext. clk mode 1 //SMS = 111
//	TIM2->SMCR |= 0x0060; // TI2FP2 as ext. clock //TS = 110
//	TIM2->SMCR |= 0x0080;// MSM = 1
//	TIM2->CR2  |= 0x0010; //send enable of tim2 as trigger to tim5 //MMS = 001
//
//	TIM5->SMCR |= 0x0006; //TIM5 in trig mode
//
//	TIM2->CR1 |= 0x0001; // enable counting
//
//}










