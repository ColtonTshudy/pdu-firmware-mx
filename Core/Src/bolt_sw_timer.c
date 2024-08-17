/**
 * @file bolt_sw_timer.c
 * @author Colton Tshudy (coltont@vt.edu)
 * @brief software timer based on HAL system tick timer
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024 BOLT at Virginia Tech
 * 
 */

#include "bolt_sw_timer.h"
#include "stm32g4xx_hal.h"

/**
 * @brief Construct a new timer. All timers must be constrcuted before use.
 *
 * @param waitTime in milliseconds
 * @return SWTimer
 */
SWTimer SWTimer_construct(uint32_t waitTime)
{
	SWTimer timer;

	timer.startCounter = 0;
	timer.waitTime_ms = waitTime;

	return timer;
}

/**
 * @brief Start a timer.
 *
 * @param timer_p pointer to a timer
 */
void SWTimer_start(SWTimer* timer_p)
{
	timer_p->startCounter = HAL_GetTick();
}

/**
 * @brief Returns number of elapsed milliseconds
 *
 * @param timer_p
 * @return uint32_t
 */
uint32_t SWTimer_elapsedTimeMS(SWTimer* timer_p)
{
	uint32_t elapsed_ms = HAL_GetTick() - timer_p->startCounter;
	return elapsed_ms;
}

/**
 * @brief Returns true if the timer is expired
 *
 * @param timer_p
 * @return true
 * @return false
 */
bool SWTimer_expired(SWTimer* timer_p)
{
	uint32_t elapsed_ms = SWTimer_elapsedTimeMS(timer_p);
	return elapsed_ms >= timer_p->waitTime_ms;
}

/**
 * Determines the progress percentage of time expired. A timer starts off at zero percent progress.
 * If, say, a timer needed to wait 10000 ms and 7000 ms have elapsed already since the timer
 * was started, the percentage returned is 0.7. For any timer which has already expired or which was
 * never started, the percentage returned is 1.0.
 *
 * @param timer_p The target timer used in determining the percent progress elapsed
 * @return the percentage of time which has elapsed since the timer was started.
 */
double SWTimer_percentElapsed(SWTimer* timer_p)
{
	if(timer_p->waitTime_ms == 0)
		return 1.0;

	uint32_t elapsed_ms = SWTimer_elapsedTimeMS(timer_p);

	double result = (double)elapsed_ms / (double)timer_p->waitTime_ms;

	if(result > 1.0)
		return 1.0;

	return result;
}