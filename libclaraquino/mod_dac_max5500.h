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

// SPI Interface to MAX5500 DAC chip

#pragma once

#include <stdint.h>  // uint8_t, etc.

void mod_dac_max5500_init();     //!< time: 40 us
void mod_dac_max5500_send_spi_word(uint16_t tx_word);
void mod_dac_max5500_update_single_DAC(uint8_t dac_idx, uint16_t dac_value); //!< time: 11.15 us

extern int PIN_DAC_MAX5500_CS;
