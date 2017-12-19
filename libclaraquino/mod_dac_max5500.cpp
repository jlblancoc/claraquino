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

#include "gpio.h"
#include "spi.h"
#include "delays.h"
#include "mod_dac_max5500.h"

#warning: Make this configurable
int PIN_DAC_MAX5500_CS = 0x24;

/* SPI frames for the MAX5500 chip
           16 bits
     MSB --- LSB (MSB first)
|A1 A0  |  C1 C0 | D11 ... D0 |

Commands C1.C0:
 * 0 1: Load DAC, do NOT update DAC output.
 * 1 1: Load DAC, update ALL DAC outputs.

- POLARITY: CPOL=0 (inactive SCK=low level)
- PHASE: CPHA=1 (master changes data on the falling edge of clock)
 ==> SPI_MODE_0 (1?)

*/

void mod_dac_max5500_init()
{
	// start the SPI library:
	spi_begin();
	spi_settings(8000000, SPI_MSB_FIRST, SPI_MODE0);
	
	gpio_pin_write(PIN_DAC_MAX5500_CS, true);  // /CS=1
	gpio_pin_mode(PIN_DAC_MAX5500_CS, OUTPUT);
	// Set all chip outputs to 0V
	mod_dac_max5500_send_spi_word(0x8000);
}

void mod_dac_max5500_send_spi_word(uint16_t tx_word)
{
	// Send HiByte:
	spi_begin_transaction();

	// nCS -> 0
	gpio_pin_write(PIN_DAC_MAX5500_CS, false);
	delay_us(1); // Min. 40ns: nCS->0 to SCK

	spi_transfer16(tx_word);

	delay_us(1);

	// nCS -> 1
	gpio_pin_write(PIN_DAC_MAX5500_CS, true);

	spi_end_transaction();
}

void mod_dac_max5500_update_single_DAC(uint8_t dac_idx, uint16_t dac_value)
{
	// See word format at the top of this file
	const uint16_t tx_word =
	(((uint16_t)dac_idx) << 14) |
	(((uint16_t)0x03)    << 12) |
	(dac_value & 0x0fff);

	mod_dac_max5500_send_spi_word(tx_word);
}
