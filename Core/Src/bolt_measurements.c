#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_adc.h"

#define ADC_TIMEOUT 100 // Timeout for ADC conversion in milliseconds

/**
 * @brief Measures 5 adc channels, requires a uint16_t buffer of length 5
 * 
 * @param adc_p 
 * @param buf 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef measure_all_adc_channels(ADC_HandleTypeDef* adc_p, uint16_t* buf)
{
	static const uint32_t channels[] = {ADC_CHANNEL_1,
										ADC_CHANNEL_2,
										ADC_CHANNEL_5,
										ADC_CHANNEL_6,
										ADC_CHANNEL_7,
										ADC_CHANNEL_TEMPSENSOR_ADC1};
	ADC_ChannelConfTypeDef sConfig = {0};
	HAL_StatusTypeDef status;

	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	for(int i = 0; i < 6; i++)
	{
		sConfig.Channel = channels[i];

		// Use longer sampling time for temperature sensor
		if(channels[i] == ADC_CHANNEL_TEMPSENSOR_ADC1)
		{
			sConfig.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
		}
		else
		{
			sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
		}

		if((status = HAL_ADC_ConfigChannel(adc_p, &sConfig)) != HAL_OK)
			return status;

		HAL_ADC_Start(adc_p);
		if((status = HAL_ADC_PollForConversion(adc_p, ADC_TIMEOUT)) != HAL_OK)
			return status;

		buf[i] = HAL_ADC_GetValue(adc_p);
	}

	HAL_ADC_Stop(adc_p);

	return HAL_OK;
}
