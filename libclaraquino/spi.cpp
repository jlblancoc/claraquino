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
#include "spi.h"
#include "gpio.h"
#include "claraquino_config.h"  // F_CPU

// Define hardware SPI pins:

#if defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__)
// atmega{16,32,64,128}4:
#define PIN_SPI_SS    0x24 // PB4
#define PIN_SPI_MOSI  0x25 // PB5
#define PIN_SPI_MISO  0x26 // PB6
#define PIN_SPI_SCK   0x27 // PB7
#else
#error "Unsupported device!"
#endif

// SPI status
uint8_t spi_initialized = 0;

void spi_begin()
{
	const uint8_t sreg = SREG;
	cli();
	if (!spi_initialized)
	{
		// Set SS to high so a connected chip will be "deselected" by default
		uint8_t port = digitalPinToPort(PIN_SPI_SS);
		uint8_t bit = digitalPinToBitMask(PIN_SPI_SS);
		volatile uint8_t *reg = portModeRegister(port);

		// if the SS pin is not already configured as an output
		// then set it high (to enable the internal pull-up resistor)
		if(!(*reg & bit))
		{
			gpio_pin_write(PIN_SPI_SS, true);
		}

		// When the SS pin is set as OUTPUT, it can be used as
		// a general purpose output port (it doesn't influence
		// SPI operations).
		gpio_pin_mode(PIN_SPI_SS, OUTPUT);

		SPCR0 |= _BV(MSTR0); // Master mode
		SPCR0 |= _BV(SPE0);  // SPI Enable

		// Set direction register for SCK and MOSI pin.
		// See: http://code.google.com/p/arduino/issues/detail?id=888
		gpio_pin_mode(PIN_SPI_SCK, OUTPUT);
		gpio_pin_mode(PIN_SPI_MOSI, OUTPUT);
	}
	spi_initialized++; // reference count
	SREG = sreg;
	
	// Default settings:
	spi_settings(4000000, SPI_MSB_FIRST, SPI_MODE0);
}

uint8_t settings_spcr=0;
uint8_t settings_spsr=0;

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

void spi_settings(uint32_t clock, spi_bit_order_t bit_order, spi_data_mode_t data_mode)
{
	// Clock settings are defined as follows. Note that this shows SPI2X
	// inverted, so the bits form increasing numbers. Also note that
	// fosc/64 appears twice
	// SPR1 SPR0 ~SPI2X Freq
	//   0    0     0   fosc/2
	//   0    0     1   fosc/4
	//   0    1     0   fosc/8
	//   0    1     1   fosc/16
	//   1    0     0   fosc/32
	//   1    0     1   fosc/64
	//   1    1     0   fosc/64
	//   1    1     1   fosc/128

	// We find the fastest clock that is less than or equal to the
	// given clock rate. The clock divider that results in clock_setting
	// is 2 ^^ (clock_div + 1). If nothing is slow enough, we'll use the
	// slowest (128 == 2 ^^ 7, so clock_div = 6).
	uint8_t clockDiv;

	uint32_t clockSetting = F_CPU / 2;
	clockDiv = 0;
	while (clockDiv < 6 && clock < clockSetting) {
		clockSetting /= 2;
		clockDiv++;
	}

	// Compensate for the duplicate fosc/64
	if (clockDiv == 6)
	clockDiv = 7;

	// Invert the SPI2X bit
	clockDiv ^= 0x1;

	// Pack into the SPISettings class
	settings_spcr =
	_BV(SPE0) |
	_BV(MSTR0) |
	((bit_order == SPI_LSB_FIRST) ? _BV(DORD0) : 0) |
	(data_mode & 0x0C) |
	((clockDiv >> 1) & SPI_CLOCK_MASK);
	settings_spsr = clockDiv & SPI_2XCLOCK_MASK;
}

void spi_begin_transaction()
{
	SPCR0 = settings_spcr;
	SPSR0 = settings_spsr;
}

uint16_t spi_transfer16(uint16_t data)
{
	union
	{
		uint16_t val;
		struct word16_t
		{
			uint8_t lsb;
			uint8_t msb;
		} w16;
	} in, out;
	
	in.val = data;
	if (!(SPCR0 & _BV(DORD0))) {
		SPDR0 = in.w16.msb;
		asm volatile("nop"); // See transfer(uint8_t) function
		while (!(SPSR0 & _BV(SPIF0))) ;
		out.w16.msb = SPDR0;
		SPDR0 = in.w16.lsb;
		asm volatile("nop");
		while (!(SPSR0 & _BV(SPIF0))) ;
		out.w16.lsb = SPDR0;
		} else {
		SPDR0 = in.w16.lsb;
		asm volatile("nop");
		while (!(SPSR0 & _BV(SPIF0))) ;
		out.w16.lsb = SPDR0;
		SPDR0 = in.w16.msb;
		asm volatile("nop");
		while (!(SPSR0 & _BV(SPIF0))) ;
		out.w16.msb = SPDR0;
	}
	return out.val;
}

void spi_end_transaction()
{
	// Does nothing, since we don't support calling SPI from within interrupt code
}
