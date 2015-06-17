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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13 , GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14 , GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15 , GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13  | GPIO_Pin_14  | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed =   GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

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
}

void SPI_read_write( uint8_t *initbuff, uint16_t quantity, uint8_t *rxbuff, uint8_t *txbuff, uint8_t read)
{
	int i = 0;
	int j = 0;


	for(j=0; j<4; j++)
		{
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
			SPI_I2S_SendData(SPI2,initbuff[j]);
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
			SPI_I2S_ReceiveData(SPI2);
		}

	for(i=0; i<quantity; i++)
	{
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		if(!read)
		{
			SPI_I2S_SendData(SPI2,txbuff[i]);
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
			SPI_I2S_ReceiveData(SPI2);
		}
		else
		{
			SPI_I2S_SendData(SPI2, 0xFF);
		}

		if(read)
		{
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

			rxbuff[i] = SPI_I2S_ReceiveData(SPI2);
		}
	}
}

uint8_t SPI_readOC(uint8_t opcode)
{
	uint8_t temp;
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, opcode);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		SPI_I2S_ReceiveData(SPI1);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, 0xFF);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		temp = SPI_I2S_ReceiveData(SPI1);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	return temp;
}
