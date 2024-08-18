/**
 * @file bolt_sw_timer.h
 * @author Colton Tshudy (coltont@vt.edu)
 * @brief header file for software timer
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024 BOLT at Virginia Tech
 * 
 */

#ifndef __BOLT_SW_TIMER_H
#define __BOLT_SW_TIMER_H

/* Includes */
#include <stdbool.h>
#include <stdint.h>

/* Software Timer Struct*/
struct SWTimer
{
	uint32_t waitTime_ms;
	uint32_t startCounter; //value of systick when the timer starts
};

struct SWTimer SWTimer_construct(uint32_t waitTime_ms);
void SWTimer_start(struct SWTimer* timer);
uint32_t SWTimer_elapsedTime(struct SWTimer* timer);
bool SWTimer_expired(struct SWTimer* timer);
double SWTimer_percentElapsed(struct SWTimer* timer_p);

#endif /* __BOLT_SW_TIMER_H */