/* Exposes the PWM pins of uC timers
 * pwm.h
 *
 * Created: 30/10/2017 0:13:35
 *  Author: jlblanco
 */ 

#pragma once

#include <stdint.h>

enum pwm_timer_t
{
	PWM_TIMER0,
	PWM_TIMER1,
	PWM_TIMER2,
	PWM_TIMER3,
};

enum pwm_timer_prescaler_t
{
	PWM_PRESCALER_1   = 0x01,
	PWM_PRESCALER_8   = 0x02,
	PWM_PRESCALER_64  = 0x03,
	PWM_PRESCALER_256 = 0x04
};


enum pwm_pin_t
{
	PWM_PIN_OCnA = 0,
	PWM_PIN_OCnB
};

/** Allows changing the period of the PWM signal. 
  *  freq_PWM = F_CPU / (prescaler*510)  */
void pwm_init(pwm_timer_t timer_id, pwm_timer_prescaler_t pwm_prescaler);

/** Sets the PWM cycle. First, call pwm_init(). 
  * value is between 0 (always off) and 255 (always on) */
void pwm_set_duty_cycle(pwm_timer_t timer_id,pwm_pin_t pin_id, uint8_t value);

/** returns an 0xNM pin ID code, or 0x00 if not a valid PWM pin */
uint8_t pwm_timer_to_pin_id(pwm_timer_t timer_id,pwm_pin_t pin_id);
