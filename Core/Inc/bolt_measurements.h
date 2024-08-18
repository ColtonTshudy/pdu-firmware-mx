#include "bolt_config.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_adc.h"

struct ADC_Vals
{
	uint16_t curr_vcc;
	uint16_t curr_12;
	uint16_t curr_5;
	uint16_t curr_3v3;
	uint16_t aux_vcc;
	uint16_t tempsense;
};

#define CONVERT_TO_MV(adc_raw) ((adc_raw) * (CONFIG_ADC_CALIB_VREF) / (CONFIG_ADC_MAX_VAL))
#define ADC_TO_40A_CURRENT(adc_raw, offset)                                                        \
	(((CONVERT_TO_MV(adc_raw)) * 1000 - offset * 1000) / (CONFIG_mV_PER_A_40))
#define ADC_TO_10A_CURRENT(adc_raw, offset)                                                        \
	(((CONVERT_TO_MV(adc_raw)) * 1000 - offset * 1000) / (CONFIG_mV_PER_A_10))

HAL_StatusTypeDef measure_all_adc_channels(ADC_HandleTypeDef*, uint16_t*);
