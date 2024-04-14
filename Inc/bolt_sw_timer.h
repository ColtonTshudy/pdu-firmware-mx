/*
 * bolt_sw_timer.h
 *
 *  Created on: 4/15/2022
 *      Author: Colton Tshduy
 */

#ifndef __BOLT_SW_TIMER_H
#define __BOLT_SW_TIMER_H

/* Imports */
#include "stdint.h"
#include "stdbool.h"

/* Macros */
#define MILLIS (SysTick->VAL / 1000)

/* Software Timer Struct*/
struct _SWTimer
{
    // The number of microseconds which must elapse before the timer expires
    uint32_t waitTime_ms;

    // The starting counter value of the hardware timer, set when the timer is started
    uint32_t startCounter;
};
typedef struct _SWTimer SWTimer;

// Constructs a Software timer. All timers must be constructed before starting them.
SWTimer SWTimer_construct(uint32_t waitTime_ms);

// Starts a software timer. All constructed timers must be started before use.
void SWTimer_start(SWTimer *timer);

// A helper function used for determining how many cycles have elapsed since the
// timer was started. You do not need to call this function outside of Timer.c.
uint32_t SWTimer_elapsedTime(SWTimer *timer);

// Returns true if the timer has expired, and false otherwise
bool SWTimer_expired(SWTimer *timer);

// Elapsed percentage of time on current timer
double SWTimer_percentElapsed(SWTimer *timer_p);

#endif /* __BOLT_SW_TIMER_H */