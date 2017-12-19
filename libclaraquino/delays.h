/*
 * delays.h
 *
 * Created: 25/10/2017 2:14:44
 *  Author: jlblanco
 */ 

#pragma once

#include "../config.h"  // F_CPU
#include <util/delay.h>
#include <stdint.h>

inline void delay_ms(uint16_t count) 
{
	while(count--) {
		_delay_ms(1);

	}
}

inline void delay_us(uint16_t count) 
{
	while(count--) {
		_delay_us(1);
	}
}