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

/* File: millis_timer.h
 * Defines a 100 microseconds system clock using 16-bit TIMER1
 */ 

#pragma once

#include <stdint.h>  // uint8_t, etc.

/** Returns the elapsed tenths of milliseconds since boot */
uint32_t millis();

/** Must be called at program startup */
void millis_init();

