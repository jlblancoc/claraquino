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

/* File: claraquino_config.h
 * Configuration of the PCB board and microcontroller
 */

#pragma once

// Default: XTAL frequency: 20 MHz
#ifndef F_CPU
#define F_CPU 20000000UL
#endif


// Where LEDs are connected (They are supposed to be VCC-tied)
#define LED_PIN_NO 0x45   // LED1 = PD5. Port D=4;  pin 5
