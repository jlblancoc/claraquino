/*
 * millis_timer.h
 * Defines a 100 microseconds system clock using 16-bit TIMER1
 *
 * Created: 25/10/2017 1:51:17
 *  Author: jlblanco
 */ 

#pragma once

#include <stdint.h>  // uint8_t, etc.

/** Returns the elapsed tenths of milliseconds since boot */
uint32_t millis();

/** Must be called at program startup */
void millis_init();

