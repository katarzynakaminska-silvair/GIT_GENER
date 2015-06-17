
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
#include "TIM.h"


__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;
extern uint8_t USB_Rx_Buffer   [CDC_DATA_MAX_PACKET_SIZE];
extern uint32_t APP_Rx_length ;
extern uint16_t USB_Rx_Cnt;


int main(void)
{

	SystemInit();
	LED_init();
	LED_on(LED_GREEN);

	HMC624_init();
	ADC_init();
	ADC_set_ST_values(&ADC_ST_values_inst);

	TIM_warm_up();





  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_cb,
            &USR_cb);



  FLASH_read_reglin(&Cali_reglin_inst);
  Cali_reglin_inst.is_serialnum_set = 1;

  HMC624_set_attenuation(10.0); // to be deleted
  Current_results_inst.current_attenuation = 10;//change to 31,5



  while (1)
  {
	  __WFI();
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
