
/**
  ******************************************************************************
  * @file    app.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    19-March-2012
  * @brief   This file provides all the Application firmware functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "core_cm4.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "usbd_cdc_vcp.h"
#include "HMC624.h"
#include "HMC345.h"
#include "HMC833.h"
#include "TIM.h"

#define PREPEND0
//#define APPEND0
//#define SEND2_ONLY

__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;
extern uint8_t USB_Rx_Buffer   [CDC_DATA_MAX_PACKET_SIZE];
extern uint32_t APP_Rx_length ;
extern uint16_t USB_Rx_Cnt;


int main(void)
{

	SystemInit();
	LED_init();
	LED_on(LED_GREEN);
	SPI_Initialize();

	HMC624_init();
	HMC345_init();
	ADC_init();
	ADC_set_ST_values(&ADC_ST_values_inst);
	HMC345_set_path(HMC345_PATH_4);
	HMC624_set_attenuation(0);
	HMC833_set_clockout();

	TIM_warm_up();

//	uint8_t tempbuf[3];
//	uint8_t tempbuf5[3] = {0};
//
//	//configure delta sigma modulator
//	uint8_t zeros[3] = {0};
//	uint8_t delta_sigma[3];
//	delta_sigma[0] = 0x03;
//	delta_sigma[1] = 0x07;
//	delta_sigma[2] = 0xca;
//	SPI_write( HMC833_REG_SD_CFG, delta_sigma );
//	SPI_read( HMC833_REG_SD_CFG, tempbuf );
//
////charge_pump
//	uint8_t chpump[3];
//	SPI_read( HMC833_REG_CHARGE_PUMP, chpump );
//	chpump[0] = 0x00;
//	chpump[1] = 0x00;
//	chpump[2] = 0x80;
//	SPI_write( HMC833_REG_CHARGE_PUMP, chpump);
////vco registers
//
//	uint8_t vco[3];
//#ifdef PREPEND0
//	//reg04
//	vco[2] = 0b10100000;
//	vco[1] = 0b01100000;
//	vco[0] = 0;
//	SPI_write( HMC833_REG_SPI,vco);
//	//reg05
//	vco[2] = 0b00101000;
//	vco[1] = 0b00010110;
//	vco[0] = 0;
//	SPI_write( HMC833_REG_SPI,vco);
//#endif
//
//#ifdef APPEND0
//	//reg04
//	vco[1] = 0b10100000;
//	vco[0] = 0b01100000;
//	vco[2] = 0;
//	SPI_write( HMC833_REG_SPI,vco);
//	//reg05
//	vco[1] = 0b00101000;
//	vco[0] = 0b00010110;
//	vco[2] = 0;
//	SPI_write( HMC833_REG_SPI,vco);
//#endif
//
//#ifdef SEND2_ONLY
//	vco[1] = 0b10100000;
//	vco[0] = 0b01100000;
//	SPI_writetwo( HMC833_REG_SPI,vco);
//	vco[1] = 0b00101000;
//	vco[0] = 0b00010110;
//	SPI_writetwo( HMC833_REG_SPI,vco);
//#endif
//	SPI_read( 0x05, tempbuf5 );
//	zeros[1] = 0x00;
//	SPI_write( HMC833_REG_SPI,zeros);
//	//SPI_writetwo( HMC833_REG_SPI,zeros);
//
//
//	/////////temp
//	uint8_t tempbufa[3];
//	tempbufa[2] = 0x61;
//	tempbufa[1] = 0x80;
//	tempbufa[0] = 0x0f;
//	SPI_write(0x0B,tempbufa);
//
//	uint8_t freqreg[3] = {0};
//	freqreg[2] = 0x72;
//	SPI_write(HMC833_REG_FREQ , freqreg);


	// SKOPIOWANE REJESTRY OD NICH
	uint8_t  r[3] = {0};
	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x02;
	SPI_write(0x01 , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x01;
	SPI_write(0x02 , r);

//	r[0] = 0x00;
//	r[1] = 0x00;
//	r[2] = 0x72;
//	SPI_write(0x03 , r);

//	r[0] = 0x00;
//	r[1] = 0x00;
//	r[2] = 0x00;
//	SPI_write(0x04 , r);

	r[0] = 0x00;
	r[1] = 0x16;
	r[2] = 0x28;
	SPI_write(0x05 , r);

	r[0] = 0x00;
	r[1] = 0x60;
	r[2] = 0xa0;
	SPI_write(0x05 , r);

	/////////////////////////////
//	r[0] = 0x00;
//	r[1] = 0x2A;
//	r[2] = 0x98;
//	SPI_write(0x05 , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x00;
	SPI_write(0x05 , r);

	r[0] = 0x20;
	r[1] = 0x03;
	r[2] = 0xca;
	SPI_write(0x06 , r);

	r[0] = 0x00;
	r[1] = 0x01;
	r[2] = 0x4d;
	SPI_write(0x07 , r);


	r[0] = 0xc1;
	r[1] = 0xbe;
	r[2] = 0xff;
	SPI_write(0x08 , r);

	r[0] = 0x00;
	r[1] = 0x3f;
	r[2] = 0xff;
	SPI_write(0x09 , r);

	r[0] = 0x00;
	r[1] = 0x20;
	r[2] = 0x46;
	SPI_write(0x0a , r);

	r[0] = 0x0f;
	r[1] = 0x80;
	r[2] = 0x61;
	SPI_write(0x0b , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x00;
	SPI_write(0x0c , r);
	SPI_write(0x0d , r);
	SPI_write(0x0e , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0x81;
	SPI_write(0x0f , r);

	r[0] = 0x00;
	r[1] = 0x00;
	r[2] = 0xf0;
	SPI_write(0x03 , r);


  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_cb,
            &USR_cb);



  FLASH_read_reglin(&Cali_reglin_inst);
  Cali_reglin_inst.is_serialnum_set = 1;

//  HMC624_set_attenuation(10.0); // to be deleted
//  Current_results_inst.current_attenuation = 10;//change to 31,5



  while (1)
  {
	  __WFI();
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
