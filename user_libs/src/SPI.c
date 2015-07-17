/* Includes ------------------------------------------------------------------*/
#include "SPI.h"

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void SPI_Initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	/* Peripheral Clock Enable -------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13 , GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14 , GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15 , GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13  | GPIO_Pin_14  | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init( GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	GPIO_Init( GPIOB, &GPIO_InitStructure);


	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //NOT SURE
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);

	GPIO_SetBits(GPIOB ,GPIO_Pin_12);
	TIM_delay_ms(3);
	GPIO_ResetBits(GPIOB ,GPIO_Pin_12);
}

void SPI_read( uint8_t address, uint8_t *rxbuff)
{
	int i = 0;
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,(0x80 | (address << 1)));
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI2);

	for(i=0; i<3; i++)
	{
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

		SPI_I2S_SendData(SPI2, 0xFF);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

		rxbuff[i] = SPI_I2S_ReceiveData(SPI2);
	}
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void SPI_write( uint8_t address,  uint8_t *txbuff)
{
	int i = 0;
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,(0x00 | (address << 1) | (*(txbuff+0) >> 7)));
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//	SPI_I2S_ReceiveData(SPI2);


	for(i=0; i<3; i++)
	{
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI2,(txbuff[i] << 1 | (txbuff[i+1] >> 7)));
	}

	SPI_I2S_ReceiveData(SPI2);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void SPI_writetwo( uint8_t address,  uint8_t *txbuff)
{
	int i = 0;
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,(0x00 | (address << 1) | (*(txbuff+0) >> 7)));
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//	SPI_I2S_ReceiveData(SPI2);


	for(i=0; i<2; i++)
	{
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI2,(txbuff[i] << 1 | (txbuff[i+1] >> 7)));
	}

	SPI_I2S_ReceiveData(SPI2);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

