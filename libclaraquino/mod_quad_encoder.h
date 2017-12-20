/* libclaraquino (C) Copyright 2016-2018 University of Almeria 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* File: interrupt-driven decoder for quadrature differential encoders
 * with channels A,B and an optional Z (zero).
 *
 * Minimum pulse width: ~3 us (ISR takes 2.8us @ 20MHz)
 * Forward:
 *         +----+      +----+
 *  A:     |    |      |    |
 *     ____|    |______|    |_____
 *           +----+      +----+
 *  B:       |    |      |    |
 *    _______|    |______|    |_____
 * 
 */

#pragma once

#include <stdint.h>  // uint8_t, etc.

#define CLARAQUINO_NUM_ENCODERS 2

struct EncoderStatus
{
	// Config:
	volatile int8_t encA_pin=0;  // =0 means disabled.
	volatile int8_t encB_valid=0,encB_bit=0, encB_port=0;
	volatile int8_t encZ_valid=0,encZ_bit=0, encZ_port=0; // encZ_port=0 means no Z
	
	// Current encoder tick counter value:
	volatile int32_t  COUNTER = 0;
	// Init:
	EncoderStatus()
	{ }
};

extern EncoderStatus ENC_STATUS[CLARAQUINO_NUM_ENCODERS];

void mod_quad_encoder_init(uint8_t encoder_index, uint8_t chA_pin, uint8_t chB_pin, uint8_t chZ_pin = 0 );