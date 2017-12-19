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

/* FILE: UART.h
 PURPOSE: Provide access to USB FIFO interface chip FT245BM / FT232 / standard UART
 Jose Luis Blanco Claraco (C) 2005-2017
 Universidad de Malaga
 Universidad de Almeria
*/

#pragma once

#include <avr/io.h>
#include <stdint.h>

/** Access to UART0 */
namespace UART
{
	/** Pops a byte from the RX queue. Returns false if no data was available. */
	bool ReadByte( uint8_t &data );

	void WriteByte( uint8_t data);
	void Write( const uint8_t *data, uint16_t nBytes);
	void WriteString( const char *str);

	// Resets the received buffer:
	void ResetReceiver();

	// Configure: sel_parity = 0:N,2:even,3:odd
	void Configure(uint32_t baud_rate, char sel_parity = 0, bool rxen = true,bool txen = true,bool twostopbits=false);

	uint8_t AvailableForRead();
}
