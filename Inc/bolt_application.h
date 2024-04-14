/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef __APPLICATION_H
#define __APPLICATION_H

/* Includes */
#include "main.h"
#include "bolt_sw_timer.h"

/* Macros */
#define MS_IN_SECONDS 1000

/* Application Struct */
struct _Application
{
    // Variables used in main.cpp Timers
    SWTimer nonblocking_led_timer;
};
typedef struct _Application Application;

/* Setup the application struct */
Application applicationSetup();

/* Code to run continuously */
void applicationLoop(Application* app_p);

/* Blinks an LED based on nonblocking_led_timer */
void nonBlockingLED();

#endif /* __APPLICATION_H */