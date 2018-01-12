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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "gpio.h"
#include "claraquino_config.h"  // F_CPU

// Define hardware SPI pins:

#if defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__)
// atmega{16,32,64,128}4:
//#define PIN_SPI_SS    0x24 // PB4

#else
#error "Unsupported device!"
#endif

void i2c_begin()
{
}

void i2c_beginTransmission(uint8_t addr)
{


}

void i2c_write(uint16_t data)
{

}

void i2c_endTransmission()
{


}
