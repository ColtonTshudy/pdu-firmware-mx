/**
 * @file bolt_heartbeat.h
 * @brief Header file for LED heartbeat functionality
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024 BOLT at Virginia Tech
 * 
 */

#ifndef __BOLT_HEARTBEAT_H
#define __BOLT_HEARTBEAT_H

/* Includes */
#include "bolt_sw_timer.h" // For SWTimer functionality
#include "main.h" // For GPIO definitions (LD2_GPIO_Port, LD2_Pin)

/* Function Prototypes */
/**
 * @brief Toggle the LED in a heartbeat pattern
 * 
 * This function should be called repeatedly in the main loop.
 * It will create a heartbeat pattern consisting of two quick blinks
 * followed by a longer pause.
 */
void LED_Heartbeat(bool);

#endif /* __BOLT_HEARTBEAT_H */