/*
 * pwm.cpp
 *
 * Created: 30/10/2017 0:13:28
 *  Author: jlblanco
 */

#include "pwm.h"
#include "gpio.h"
#include <avr/io.h>

uint8_t pwm_timer_to_pin_id(pwm_timer_t timer_id,pwm_pin_t pin_id)
{
#if defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__)
	switch (timer_id)
	{
		case PWM_TIMER0:
			switch (pin_id) {
				case PWM_PIN_OCnA: return 0x23;
				case PWM_PIN_OCnB: return 0x24;
				default: return 0x00;
			};
		break;

		case PWM_TIMER1:
		switch (pin_id) {
			case PWM_PIN_OCnA: return 0x45;
			case PWM_PIN_OCnB: return 0x44;
			default: return 0x00;
		};
		break;

		case PWM_TIMER2:
		switch (pin_id) {
			case PWM_PIN_OCnA: return 0x47;
			case PWM_PIN_OCnB: return 0x46;
			default: return 0x00;
		};
		break;

		case PWM_TIMER3:
		switch (pin_id) {
			case PWM_PIN_OCnA: return 0x26;
			case PWM_PIN_OCnB: return 0x27;
			default: return 0x00;
		};
		break;

		default: return 0x00;
	};
#else
#error "Unsupported device!"
#endif
}

void pwm_init(pwm_timer_t timer_id, pwm_timer_prescaler_t pwm_prescaler)
{
	// ensure PWM outputs are outputs:
	const uint8_t pinA = pwm_timer_to_pin_id(timer_id,PWM_PIN_OCnA);
	const uint8_t pinB = pwm_timer_to_pin_id(timer_id,PWM_PIN_OCnB);
	gpio_pin_write(pinA, false);
	gpio_pin_mode(pinA, OUTPUT);
	gpio_pin_write(pinB, false);
	gpio_pin_mode(pinB, OUTPUT);

	// init timer:
	switch (timer_id)
	{
		case PWM_TIMER0: // 8bit counter
		{
			OCR0A = 0;
			OCR0B = 0;
			// See datasheet page 103
			// Mode(WGM2:0)=1: phase correct PWM. TOP=0xff
			TCCR0A = 
				_BV(COM0A1) |
				_BV(COM0B1) |
				_BV(WGM00);
			TCCR0B = (pwm_prescaler & 0x03) << CS00;
		}
		break;
		
		case PWM_TIMER2: // 8bit counter
		{
			OCR2A = 0;
			OCR2B = 0;
			// See datasheet page 103
			// Mode(WGM2:0)=1: phase correct PWM. TOP=0xff
			TCCR2A =
			_BV(COM2A1) |
			_BV(COM2B1) |
			_BV(WGM20);
			TCCR2B = (pwm_prescaler & 0x03) << CS20;
		}
		break;
		
	default:
		// Do nothing for other timers
		break;
	};
}

/** Sets the PWM cycle. First, call pwm_init(). 
  * value is between 0 (always off) and 255 (always on) */
void pwm_set_duty_cycle(pwm_timer_t timer_id,pwm_pin_t pin_id, uint8_t value)
{
	switch (timer_id)
	{
		case PWM_TIMER0: // 8bit counter
			switch (pin_id) {
				case PWM_PIN_OCnA: OCR0A=value; break;
				case PWM_PIN_OCnB: OCR0B=value; break;
			};
		break;

		case PWM_TIMER2: // 8bit counter
		switch (pin_id) {
			case PWM_PIN_OCnA: OCR2A=value; break;
			case PWM_PIN_OCnB: OCR2B=value; break;
		};
		break;
		default:
		// Do nothing for other timers
		break;
	};

}
