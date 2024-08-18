/**
 * @file bolt_config.h
 * @author Colton Tshudy (coltont@vt.edu)
 * @brief Quick macros to affect important settings
 * @version 0.1
 * @date 2024-08-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "main.h"

#define CONFIG_PCAN_TIMEOUT		250 //!< Maximum time (ms) between PCAN messages
#define CONFIG_ADC_CALIB_VREF	3410 //!< Calibrated VREF (mV) from adc1_in7 measurement
#define CONFIG_ADC_MAX_VAL		4095 //!< Maximum value of an ADC read
#define CONFIG_CURRSENS_V_AT_0A 1500 //!< Voltage (mV) output of current sensors at 0A
#define CONFIG_AUX_VCC_VDIV		16 //!< Voltage divider value for measuring aux pack voltage
#define CONFIG_mV_PER_A_10		132 //!< V per mA for +/-10A current sensor
#define CONFIG_mV_PER_A_40		33 //!< V per mA for +/-10A current sensor

#define CONFIG_AUX_CURR_CAL 1450 //!< Output voltage of Aux's current sensor at 0A
#define CONFIG_12_CURR_CAL	1500 //!< Output voltage of 12V rail's current sensor at 0A
#define CONFIG_5_CURR_CAL	1500 //!< Output voltage of 5V rail's current sensor at 0A
#define CONFIG_3V3_CURR_CAL 1470 //!< Output voltage of 3V3 rail's current sensor at 0A
