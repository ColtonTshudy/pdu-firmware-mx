#include "bolt_led_control.h"
#include "bolt_sw_timer.h"

#define SHORT_BLINK_DURATION 100 // Duration of short blink in ms
#define LONG_PAUSE_DURATION	 1000 // Duration of long pause in ms

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

void LED_AuxLow(uint16_t value)
{
	static struct SWTimer timer = {0};
	static bool ledState = true; // Start with LED on
	uint32_t fullInterval, onTime, offTime;

	if(value < 18000)
	{
		fullInterval = 200; // Fast blinking
		onTime = offTime = fullInterval / 2; // 50% duty cycle
	}
	else if(value < 20400)
	{
		fullInterval = 1000; // Slow blinking
		onTime = (fullInterval * 3) / 4; // 75% duty cycle
		offTime = fullInterval / 4;
	}
	else
	{
		HAL_GPIO_WritePin(GPIO_AUX_LOW_GPIO_Port, GPIO_AUX_LOW_Pin, GPIO_PIN_RESET);
		return;
	}

	if(timer.waitTime_ms != (ledState ? onTime : offTime))
	{
		timer = SWTimer_construct(ledState ? onTime : offTime);
		SWTimer_start(&timer);
	}

	if(SWTimer_expired(&timer))
	{
		ledState = !ledState;
		HAL_GPIO_WritePin(
			GPIO_AUX_LOW_GPIO_Port, GPIO_AUX_LOW_Pin, ledState ? GPIO_PIN_SET : GPIO_PIN_RESET);
		timer = SWTimer_construct(ledState ? onTime : offTime);
		SWTimer_start(&timer);
	}
}