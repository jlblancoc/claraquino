/*****************************************************************************************
 FILE: UART.h
 PURPOSE: Provide access to USB FIFO interface chip FT245BM / FT232 / standard UART

Jose Luis Blanco Claraco (C) 2005-2017
Universidad de Malaga
Universidad de Almeria
****************************************************************************************/

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
};
