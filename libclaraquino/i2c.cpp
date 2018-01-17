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
#include "i2c.h"
#include "gpio.h"
#include "claraquino_config.h"  // F_CPU

#include "twi.h"


#define BUFFER_LENGTH 32
//static uint8_t rxBuffer[BUFFER_LENGTH];
static uint8_t rxBufferIndex = 0;
static uint8_t rxBufferLength = 0;

static uint8_t txAddress = 0;
static uint8_t txBuffer[BUFFER_LENGTH];
static uint8_t txBufferIndex = 0;
static uint8_t txBufferLength = 0;
bool transmitting = 0;


void i2c_begin()
{
	rxBufferIndex = 0;
	rxBufferLength = 0;

	txBufferIndex = 0;
	txBufferLength = 0;

	twi_init();
}

void i2c_end()
{
	twi_disable();
}

void i2c_setClock(uint32_t clock)
{
	twi_setFrequency(clock);
}

void i2c_beginTransmission(uint8_t addr)
{
  // indicate that we are transmitting
  transmitting = 1;
  // set address of targeted slave
  txAddress = addr;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
}

bool i2c_write(uint16_t data)
{
	if(transmitting)
	{
		// in master transmitter mode
		// don't bother if buffer is full
		if(txBufferLength >= BUFFER_LENGTH)
		{
			//setWriteError();
			return false;
		}
		// put byte in tx buffer
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		// update amount in buffer
		txBufferLength = txBufferIndex;
	}
	else
	{
		// in slave send mode
		// reply to master
		twi_transmit((const uint8_t*)&data, 1);
	}
	return true;
}

uint8_t i2c_endTransmission(bool sendStop)
{
	// transmit buffer (blocking)
	uint8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, sendStop);
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	return ret;
}
