/*
 * spi.h
 *
 * Created: 29/10/2017 23:58:20
 *  Author: jlblanco
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
