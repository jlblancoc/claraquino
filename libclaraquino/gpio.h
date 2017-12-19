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
#include <avr/pgmspace.h> // pgm_read_*()

enum pin_mode_t
{
	INPUT = 0,
	OUTPUT,
	INPUT_PULLUP
};

/** GPIO pin numbers use this convention:
  * pin_no = 0xXY in hexadecimal, with:
  * X: 1=PORTA, 2=PORTB, 3=PORTC,...
  * Y: [0,7] pin number within the given port.
  */
void gpio_pin_mode(const uint8_t pin_no, pin_mode_t pin_mode);

/** See gpio_pin_mode() for pin number convention.
  * Sets pin to HIGH if value=true, to LOW otherwise. */
void gpio_pin_write(const uint8_t pin_no, bool value);

/** See gpio_pin_mode() for pin number convention.
  * returns true if pin is HIGH. */
bool gpio_pin_read(const uint8_t pin_no);

enum interrupt_event_type_t
{
	INTERRUPT_ON_LOW_LEVEL    = 0,
	INTERRUPT_ON_ANY_EDGE     = 1,
	INTERRUPT_ON_FALLING_EDGE = 2,
	INTERRUPT_ON_RISING_EDGE = 3
};

/** See gpio_pin_mode() for pin number convention.
  * Attaches an arbitrary function to an external-driven interrupt on one of the available pins
  */
bool gpio_attach_interrupt(const uint8_t pin_no, void (*func_ptr)(void), interrupt_event_type_t  int_event );

extern const uint16_t PROGMEM port_to_mode_PGM[];
extern const uint16_t PROGMEM port_to_input_PGM[];
extern const uint16_t PROGMEM port_to_output_PGM[];

// Pin numbers: PORTA: 0x10-0x17; PORTB: 0x20-0x27, etc.
inline uint8_t digitalPinToPort(const uint8_t pin_no)
{
	if (!pin_no)
	     return 0;
	else return (0xf0 & pin_no) >> 4;
}

inline uint8_t digitalPinToBitMask(const uint8_t pin_no)
{
	if (!pin_no)
	     return 0;
	else return 1<< (0x0f & pin_no);
}

#define portOutputRegister(port_no) ( (volatile uint8_t *)( pgm_read_word( port_to_output_PGM + (port_no))) )
#define portInputRegister(port_no) ( (volatile uint8_t *)( pgm_read_word( port_to_input_PGM + (port_no))) )
#define portModeRegister(port_no) ( (volatile uint8_t *)( pgm_read_word( port_to_mode_PGM + (port_no))) )

