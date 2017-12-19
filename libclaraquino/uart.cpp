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

/* FILE: CUART.cpp
  PURPOSE: Provide access to USB FIFO interface chip FT245BM / FT232 / standard UART
Jose Luis Blanco Claraco (C) 2005-2014
Universidad de Malaga
Universidad de Almeria
*/

// Headers
#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>
#include <string.h>  // strlen()

#include "uart.h"
#include "circular_buffer.h"
#include "claraquino_config.h"

#include <avr/interrupt.h>

#define UART_RX_BUFFER_BITS 6 // 2^6 = 64 bytes

circular_buffer<UART_RX_BUFFER_BITS>  uart_rx_buffer;

// Handle the UART RX events:
ISR(USART0_RX_vect)
{
	const uint8_t rx_b = UDR0;
	uart_rx_buffer.push(rx_b);
}

/** Pops a byte from the RX queue. Returns false if no data was available. */
bool UART::ReadByte( uint8_t &data )
{
	return uart_rx_buffer.pop(data);
}

/*-----------------------------------------------------------------
void CUART::Configure( bool RXEN, bool TXEN, char parity, bool stop_2bits, uint16_t baud_divisor )
	Configure the UART. sel_parity = 0:N,2:even,3:odd
  -----------------------------------------------------------------*/
void UART::Configure(uint32_t USART_BAUDRATE, char sel_parity, bool rxen,bool txen,bool twostopbits)
{
	// Define baud rate
	const uint16_t baud_div = (((F_CPU / (USART_BAUDRATE * 8UL))) - 1);
	
	// A
	UCSR0A = (1<<U2X0); // U2X: Prescaler=8
	
	// B
	uint8_t b = 1 << RXCIE0;	// enable received data interrupt
	if (rxen) b|=1 << RXEN0;
	if (txen) b|=1 << TXEN0;
	UCSR0B = b; 

	// C
	b = 0x86;		// 8 bits words
	b |= ((sel_parity & 0x03) << UPM00);
	if (twostopbits) b|= 1 << USBS0;
	UCSR0C = b;
	
	// Baud rate:
	UBRR0 = baud_div;
}

/*-----------------------------------------------------------------
void 	UART::ResetReceiver()
	Empty received queue
  -----------------------------------------------------------------*/
void UART::ResetReceiver()
{
	uart_rx_buffer.clear();
}

/*-----------------------------------------------------------------
void CUART::WriteByte( unsigned char data)
	Write a byte to UART. 
  -----------------------------------------------------------------*/
void UART::WriteByte( register unsigned char data)
{
	while ( 0 == (UCSR0A & (1 << UDRE0)) ) {};	// wait until free
	UDR0 = data;
}

/*-----------------------------------------------------------------
	Write an array of bytes:
  -----------------------------------------------------------------*/
void UART::Write( const uint8_t *data, uint16_t nBytes)
{
	for (uint16_t i = 0;i<nBytes;i++)
		WriteByte( data[i] );
}

void UART::WriteString( const char *str)
{
	Write((unsigned char*)str, strlen(str));
}

uint8_t UART::AvailableForRead()
{
	return uart_rx_buffer.size();
}


