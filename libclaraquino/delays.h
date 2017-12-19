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

#pragma once

#include "claraquino_config.h"  // F_CPU
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