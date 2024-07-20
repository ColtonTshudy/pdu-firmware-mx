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
#include "main.h"
#include "bolt_sw_timer.h"

/* Macros */
#define MS_IN_SECONDS 1000

/* Application Struct */
struct _Application
{
    // Variables used for non-blocking LED
    SWTimer nonblocking_led_timer;

    // Variables used for ADC
    
};
typedef struct _Application Application;

Application applicationSetup();
void applicationLoop(Application* app_p);
void nonBlockingLED();
void printVal(uint32_t val);

#endif /* __APPLICATION_H */