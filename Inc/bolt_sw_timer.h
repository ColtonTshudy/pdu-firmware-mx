/*
 * bolt_sw_timer.h
 *
 *  Created on: 4/15/2022
 *      Author: Colton Tshduy
 */

#ifndef __BOLT_SW_TIMER_H
#define __BOLT_SW_TIMER_H

/* Includes */
#include "stdint.h"
#include "stdbool.h"

/* Software Timer Struct*/
struct _SWTimer
{
    uint32_t waitTime_ms;   
    uint32_t startCounter; //value of systick when the timer starts
};
typedef struct _SWTimer SWTimer;

SWTimer SWTimer_construct(uint32_t waitTime_ms);
void SWTimer_start(SWTimer *timer);
uint32_t SWTimer_elapsedTime(SWTimer *timer);
bool SWTimer_expired(SWTimer *timer);
double SWTimer_percentElapsed(SWTimer *timer_p);

#endif /* __BOLT_SW_TIMER_H */