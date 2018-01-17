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

#include <stdint.h>

/** Initialize the I2C bus of the uC */
void i2c_begin();

void i2c_beginTransmission(uint8_t addr);
bool i2c_write(uint16_t data);
uint8_t i2c_endTransmission(bool sendStop = true);
void i2c_end();
void i2c_setClock(uint32_t clock);


