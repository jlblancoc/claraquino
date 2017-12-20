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

/* File: interrupt-driven decoder for quadrature differential encoders
 * with channels A,B and an optional Z (zero).
 */

#include "mod_quad_encoder.h"
#include "gpio.h"

EncoderStatus ENC_STATUS[CLARAQUINO_NUM_ENCODERS];

// Minimum pulse width: ~3 us (ISR takes 2.8us @ 20MHz)

// Forward:
//        ------      ------
// A:     |    |      |    |
//    ____|    |______|    |_____
//          ------      ------
// B:       |    |      |    |
//   _______|    |______|    |_____
//
//
template <uint8_t index>  // Generic template to generate N functions for different index of encoder=0,1,...
static void onEncoder_Raising_A()
{
	#ifdef USE_ENCODER_DEBUG_LED
	ENC_STATUS[index].led = !ENC_STATUS[index].led;
	#endif

	// Avoid: gpio_pin_read() "slow" call
	if (ENC_STATUS[index].encB_valid)
	{
		const bool B = (*portInputRegister(ENC_STATUS[index].encB_port) & ENC_STATUS[index].encB_bit);
		if (B) ENC_STATUS[index].COUNTER--;
		else ENC_STATUS[index].COUNTER++;
	}
	else
	{
		ENC_STATUS[index].COUNTER++;
	}

	if (ENC_STATUS[index].encZ_valid)
	{
		const bool Z = (*portInputRegister(ENC_STATUS[index].encZ_port) & ENC_STATUS[index].encZ_bit);
		if (Z) {
			ENC_STATUS[index].COUNTER=0;
		}
	}
}

// List of function pointers, required by Arduino attachInterrupt() and also
// to be able to dynamically get a pointer by index, which is not directly allowed
// with template arguments.
typedef void (*func_ptr)(void);
func_ptr my_encoder_ISRs[CLARAQUINO_NUM_ENCODERS] =
{
	&onEncoder_Raising_A<0>,
	&onEncoder_Raising_A<1>
	//... Add more if needed in the future
};

void mod_quad_encoder_init(uint8_t i, uint8_t chA_pin, uint8_t chB_pin, uint8_t chZ_pin)
{
	if (i>=CLARAQUINO_NUM_ENCODERS)
		return;
		
	ENC_STATUS[i] = EncoderStatus();
	ENC_STATUS[i].encA_pin = chA_pin;
		
	// Is it enabled by the user?
	if (chA_pin>0)
	{
		gpio_pin_mode(chA_pin, INPUT_PULLUP);
		if (chB_pin>0)
		{
			gpio_pin_mode(chB_pin, INPUT_PULLUP);

			// Cache these calls to avoid repeating them in readDigital() inside the interrupt vector ;-)
			ENC_STATUS[i].encB_bit = digitalPinToBitMask( chB_pin );
			ENC_STATUS[i].encB_port = digitalPinToPort(chB_pin);
			ENC_STATUS[i].encB_valid = true;
		}
		else
		ENC_STATUS[i].encB_valid = false;

		if (chZ_pin>0)
		{
			ENC_STATUS[i].encZ_bit = digitalPinToBitMask(chZ_pin);
			ENC_STATUS[i].encZ_port = digitalPinToPort(chZ_pin);
			ENC_STATUS[i].encZ_valid = true;
		}
		else
		{
			ENC_STATUS[i].encZ_valid = false;
			ENC_STATUS[i].encZ_bit = ENC_STATUS[i].encZ_port = 0;
		}

		gpio_attach_interrupt(chA_pin,my_encoder_ISRs[i], INTERRUPT_ON_RISING_EDGE);
	}
}
