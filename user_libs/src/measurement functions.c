#include "measurement functions.h"
#include "LED.h"
#include "FLASH.h"

#include "HMC624.h"
#include "LED.h"
#include "TIM.h"
#include "ADC.h"
#include "HMC833.h"
#include "HMC345.h"

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

void select_frequency(double freq)
{
	if(freq < 3011)//f podstawowa mno¿nik wyjciowy ustawiæ na 1
	{
		HMC345_set_path(HMC345_PATH_1);
		HMC833_set_multiplier(FALSE);
		HMC833_set_frequency(freq);
	}

	else if(freq < 4700)//ustawiæ f podstawow¹ na 1/2freq; mno¿nik na 2
	{
		HMC345_set_path(HMC345_PATH_2);
		HMC833_set_frequency(freq/2.0);
		TIM_delay_ms(1);
		while(HMC833_is_busy()){}
		HMC833_set_multiplier(TRUE);
	}
	else if(freq < 6000)// ustawiæ f podstawow¹ na 1/2freq; mno¿nik na 2
	{
		HMC345_set_path(HMC345_PATH_3);
		HMC833_set_frequency(freq/2.0);
		TIM_delay_ms(1);
		while(HMC833_is_busy()){}
		HMC833_set_multiplier(TRUE);
	}
	else// ustawiæ f/4 mno¿nik na 1
	{
		HMC345_set_path(HMC345_PATH_4);
		HMC833_set_multiplier(FALSE);
		HMC833_set_frequency(freq/4.0);
	}
}
