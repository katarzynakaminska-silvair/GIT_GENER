#include "measurement functions.h"
#include "LED.h"
#include "FLASH.h"

#include "HMC624.h"
#include "LED.h"
#include "TIM.h"
#include "ADC.h"

Current_results Current_results_inst;
extern Cali_reglin Cali_reglin_inst;

void Current_result_clear(Current_results* Current_results_struct)
{
	LED_off(LED_RED);
	Current_results_struct->current_error_log_1 = 0;
	Current_results_struct->current_error_log_2 = 0;
	Current_results_struct->current_ADC_ref_voltage = 0;
	Current_results_struct->current_ADC_temperature = 0;
	Current_results_struct->current_ADC_voltage = 0;
}


inline void set_warm_up_state(uint8_t is_warmed_up)
{
	if(is_warmed_up == 0) LED_on(LED_ORANGE);
	else
	{
		LED_off(LED_ORANGE);
		Current_results_inst.current_is_warmed_up = is_warmed_up;
	}
}

void clear_buf(char* buf, int bytes_to_clear)
{
	int k = 0;
	for ( k = 0; k <= bytes_to_clear; k++)
	{
		buf[k] = 0;
	}
}

