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

/** Initialize the SPI bus of the uC */
void spi_begin();

enum spi_bit_order_t
{
	SPI_LSB_FIRST,
	SPI_MSB_FIRST
};

enum spi_data_mode_t
{
	SPI_MODE0 = 0x00,
	SPI_MODE1 = 0x04,
	SPI_MODE2 = 0x08,
	SPI_MODE3 = 0x0C
};

void spi_settings(uint32_t clock, spi_bit_order_t bit_order, spi_data_mode_t data_mode);

/** Start SPI transaction. Call spi_settings() first. */
void spi_begin_transaction();
void spi_end_transaction();

uint16_t spi_transfer16(uint16_t data);
