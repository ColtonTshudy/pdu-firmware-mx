/**
 * @file bolt_application.h
 * @author Colton Tshudy (coltont@vt.edu)
 * @brief header file for most things
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024 BOLT at Virginia Tech
 * 
 */

#ifndef __APPLICATION_H
#define __APPLICATION_H

/* Includes */
#include "bolt_sw_timer.h"
#include "main.h"

/* Macros */
#define MS_IN_SECONDS 1000

/* Structs and Enums */
//!< Application state enum
typedef enum
{
	OK_STATE = 0,
	LOW_POWER_STATE = 1
} PDU_State;

//!< Application state enum
struct Application
{
	PDU_State state;

	// Variables used for non-blocking LED
	struct SWTimer pcan_watchdog;

	// Measured values
	bool observed_accessory_sw;
	bool observed_mc_on;
	bool observed_ignition_sw;
	uint16_t aux_volts;
	int32_t aux_curr;
	int32_t rail_12_curr;
	int32_t rail_5_curr;
	int32_t rail_3v3_curr;
	int pdu_chip_temp;

	// CAN recieved values
	int motor_temp;
	int mc_temp;

	// Pointers to HAL thingies
	ADC_HandleTypeDef* hadc1;
	FDCAN_HandleTypeDef* hfdcan1;
	FDCAN_HandleTypeDef* hfdcan2;
	TIM_HandleTypeDef* htim1;
	TIM_HandleTypeDef* htim3;
};

/* Functions */
//!< Constructs an Application struct
struct Application applicationSetup(ADC_HandleTypeDef*,
									FDCAN_HandleTypeDef*,
									FDCAN_HandleTypeDef*,
									TIM_HandleTypeDef*,
									TIM_HandleTypeDef*);
//!< Executes in main loop
void applicationLoop(struct Application*);
//!< Main state machine
PDU_State applicationFSM(struct Application*);
//!< Measures GPIO and ADC
void measureInputs(struct Application*);
//!< Reads from PCAN (fdcan0)
void readPCAN(struct Application*);

#endif /* __APPLICATION_H */