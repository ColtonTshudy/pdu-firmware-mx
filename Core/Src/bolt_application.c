/**
 * @file bolt_application.c
 * @author Colton Tshudy (coltont@vt.edu)
 * @brief 
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024 BOLT at Virginia Tech
 * 
 */

#include "bolt_application.h"
#include "bolt_communications.h"
#include "bolt_config.h"
#include "bolt_measurements.h"
#include "debug.h"
#include "main.h"
#include "status_led_control.h"
#include <stdio.h>

/**
 * @brief Set up the application struct
 * 
 * @return struct Application 
 */
struct Application applicationSetup()
{
	struct Application app;
	app.pcan_watchdog = SWTimer_construct(CONFIG_PCAN_TIMEOUT);

	SWTimer_start(&app.pcan_watchdog);
	// PCAN_Config_Reception(app.hfdcan1);

	return app;
}

/**
 * @brief Called once per loop of main
 * 
 * @param app_p 
 */
void applicationLoop(struct Application* app_p)
{
	// Code to run always
	measureInputs(app_p);
	readPCAN(app_p);
	LED_Heartbeat(!SWTimer_expired(&(app_p->pcan_watchdog)));

	// (inside FSM) Code to run state-dependently
	PDU_State next_state = applicationFSM(app_p);
	app_p->state = next_state;

	// Send CAN messages
	// sendPCAN(app_p);

	HAL_TIM_PWM_Start(app_p->htim1, TIM_CHANNEL_1);
}

/**
 * @brief Main finite state machine
 * 
 * @param app_p 
 * @return PDU_State 
 */
PDU_State applicationFSM(struct Application* app_p)
{
	PDU_State state = app_p->state;

	// Code to run conditionally
	switch(state)
	{
	case OK_STATE:
		break;
	case LOW_POWER_STATE:
		break;
		// Add more states if needed
	}

	return state;
}

/**
 * @brief Measures ADC, GPIO
 * 
 * @param app_p 
 */
void measureInputs(struct Application* app_p)
{
	// Buffers
	struct ADC_Vals* adc;
	uint16_t buf[6];

	// Take the raw measurement
	measure_all_adc_channels(app_p->hadc1, buf);
	adc = (struct ADC_Vals*)buf;

	// Value conversion
	app_p->pdu_chip_temp =
		(int)__HAL_ADC_CALC_TEMPERATURE(CONFIG_ADC_CALIB_VREF, adc->tempsense, ADC_RESOLUTION_12B);
	app_p->aux_volts = CONVERT_TO_MV((uint16_t)(adc->aux_vcc)) * CONFIG_AUX_VCC_VDIV;
	app_p->aux_curr = ADC_TO_40A_CURRENT((int32_t)(adc->curr_vcc), CONFIG_AUX_CURR_CAL);
	app_p->rail_12_curr = ADC_TO_40A_CURRENT((int32_t)(adc->curr_12), CONFIG_12_CURR_CAL);
	app_p->rail_5_curr = ADC_TO_10A_CURRENT((int32_t)(adc->curr_5), CONFIG_5_CURR_CAL);
	app_p->rail_3v3_curr = ADC_TO_10A_CURRENT((int32_t)(adc->curr_3v3), CONFIG_3V3_CURR_CAL);

	LOG_DBG("aux_v: %d,\t aux_c: %ld, \t12_c: %ld, \t5_c: %ld, \t3v3_c: %ld, \ttemp: %d ",
			app_p->aux_volts,
			app_p->aux_curr,
			app_p->rail_12_curr,
			app_p->rail_5_curr,
			app_p->rail_3v3_curr,
			app_p->pdu_chip_temp);

	// LOG_DBG("%d, %u, %d, %d, %d",
	// 		(ADC_TO_10A_CURRENT((int)(adc->curr_3v3))),
	// 		(ADC_TO_MV(adc->vcc) * 16),
	// 		(ADC_TO_40A_CURRENT((int)(adc->curr_vcc))),
	// 		(ADC_TO_10A_CURRENT((int)(adc->curr_12))),
	// 		(ADC_TO_10A_CURRENT((int)(adc->tempsense))));

	return;
}

/**
 * @brief Tries to read from PCAN, feeds its watchdog if successful
 * 
 * @param app_p 
 */
void readPCAN(struct Application* app_p)
{
	(void)app_p;
	return;
}