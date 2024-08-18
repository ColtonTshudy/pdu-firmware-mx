#include "status_led_control.h"
#include "bolt_sw_timer.h"

#define SHORT_BLINK_DURATION 100 // Duration of short blink in ms
#define LONG_PAUSE_DURATION 1000 // Duration of long pause in ms

typedef enum
{
	BLINK_ON_1,
	BLINK_OFF_1,
	BLINK_ON_2,
	BLINK_OFF_2,
	LONG_PAUSE
} BlinkState;

void LED_Heartbeat(bool healthy)
{
	static struct SWTimer blinkTimer = {0};
	static BlinkState state = BLINK_ON_1;

	if(SWTimer_expired(&blinkTimer))
	{
		// Advance state
		if(healthy)
		{
			state = (state + 1) % 5;
		}
		else
		{
			state = (state == LONG_PAUSE) ? BLINK_ON_1 : LONG_PAUSE;
		}

		// Set timer duration
		uint32_t duration = (state == LONG_PAUSE) ? LONG_PAUSE_DURATION : SHORT_BLINK_DURATION;
		blinkTimer = SWTimer_construct(duration);
		SWTimer_start(&blinkTimer);

		// Set LED state
		bool ledOn = (state == BLINK_ON_1 || (healthy && state == BLINK_ON_2));
		HAL_GPIO_WritePin(GPIO_PDU_STATUS_GPIO_Port, GPIO_PDU_STATUS_Pin, ledOn);
	}
}