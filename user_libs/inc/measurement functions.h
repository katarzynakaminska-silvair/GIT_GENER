#ifndef __MEASUREMENT_FUNCTIONS_H_
#define __MEASUREMENT_FUNCTIONS_H_

#include "stm32f4xx_conf.h"

#define ERROR_V_REF 		0b00000001
#define ERROR_TEMPERATURE 	0b00000010
#define ERROR_CALIBRATION 	0b00000100
#define ERROR_WARM_UP	 	0b00001000
#define ERROR_SERIAL_NUM	0b00010000

typedef struct
{
	float current_ADC_voltage;
	float current_attenuation;
	float current_ADC_temperature;
	float current_detector_temperature;
	float current_ADC_ref_voltage;
	uint8_t current_error_log_1;
	uint8_t current_error_log_2;
	uint8_t current_is_warmed_up;

} Current_results;

extern Current_results Current_results_inst;

inline void set_warm_up_state(uint8_t is_warmed_up);

#endif
