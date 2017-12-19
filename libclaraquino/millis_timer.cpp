/*
 * millis_timer.cpp
 *
 * Created: 25/10/2017 1:51:29
 *  Author: jlblanco
 */ 

#include "millis_timer.h"

#include <avr/interrupt.h>
#include "claraquino_config.h"

volatile uint32_t timer_ms=0;

// Handle the Timer 1 events:
ISR(TIMER1_COMPA_vect)
{
	++timer_ms;
}

/** Returns the elapsed tenths of milliseconds since boot */
uint32_t millis()
{
	uint8_t oldSREG = SREG;
	cli();
	const uint32_t ret = timer_ms;
	SREG = oldSREG;
	return ret;
}


/** Must be called at program startup */
void millis_init()
{
	timer_ms=0;
	// Timer1: 16bits,
	const unsigned int prescaler = 8;
	// 1 overflow with compare = (1+n): prescaler* (1+n) / FREQ_CPU = period

	// 0.1ms period compare value:
	OCR1A = ((F_CPU/10000)/prescaler)-1;

	// Mode 2: WGM12=1 (clear on compare)
	TCCR1B = (1<<WGM12) | (2 /*prescaler=8*/);

	// Enable interrupt:
	TIMSK1 |= (1<<OCIE1A);
}
