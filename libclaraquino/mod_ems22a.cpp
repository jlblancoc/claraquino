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

#include "mod_ems22a.h"
#include "delays.h"
#include "gpio.h"
#include "millis_timer.h"
#include "uart.h"

/* Absolute encoder EMS22A reading waveforms (from its datasheet) */
//    ____                                                                  ____
// Cs:    |                                                                |    |
//        |________________________________________________________________|    |_____
//    __________   _   _   _   _   _   _   _   _   _   _   _   _   ______________
// Clk:         | | | | | | | | | | | | | | | | | | | | | | | | | |
//              |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_|
//
//                  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _
// DO:__________   / \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \______________
//              |_|\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/
//                  D9-D8-D7-D6-D5-D4-D3-D2-D1-D0-S1-S2-S3-S4-S5-P1
//
// D0-D9: Absolute angular position data.
// S1	: End of offset compensation algorithm.
// S2	: Cordic overflow indicating an error in cordic part.
// S3	: Linearity alarm.
// S4	: Increase in magnitude.
// S5	: Decrease in magnitude.
// P1	: Even parity for detecting bits 1-15 transmission error.

int ENCODER_ABS_CS  = 0x10;
int ENCODER_ABS_CLK = 0x11;
int ENCODER_ABS_DO  = 0x12;
uint16_t       EMS22A_sampling_period_ms_tenths = 2000;

bool init_EMS22A(int8_t init_ENCODER_ABS_CS, int8_t init_ENCODER_ABS_CLK, int8_t init_ENCODER_ABS_DO, uint16_t init_sampling_period_ms_tenths)
{
	ENCODER_ABS_CS  = init_ENCODER_ABS_CS;
	ENCODER_ABS_CLK = init_ENCODER_ABS_CLK;
	ENCODER_ABS_DO  = init_ENCODER_ABS_DO;
	EMS22A_sampling_period_ms_tenths = init_sampling_period_ms_tenths;
	if (ENCODER_ABS_CS<=0 || ENCODER_ABS_CLK<=0 || ENCODER_ABS_DO<=0)
		return false; // error
	
	gpio_pin_mode(ENCODER_ABS_CS, OUTPUT);
	gpio_pin_mode(ENCODER_ABS_CLK, OUTPUT);
	gpio_pin_mode(ENCODER_ABS_DO, INPUT);

	gpio_pin_write(ENCODER_ABS_CLK, true);
	gpio_pin_write(ENCODER_ABS_CS, true);
	
	return true; // all ok
}

uint16_t read_EMS22A()
{
	gpio_pin_mode(ENCODER_ABS_CS, OUTPUT);
	gpio_pin_mode(ENCODER_ABS_CLK, OUTPUT);
	gpio_pin_mode(ENCODER_ABS_DO, INPUT);

	gpio_pin_write(ENCODER_ABS_CS, false);
	delay_us(2);

	uint16_t pos = 0;
	for (int i=0; i<16; i++) {
		gpio_pin_write(ENCODER_ABS_CLK, false);  delay_us(1);
		gpio_pin_write(ENCODER_ABS_CLK, true); delay_us(1);

		pos = pos << 1; // shift 1 bit left
		if (gpio_pin_read(ENCODER_ABS_DO) == true )
		{
			pos |= 0x01;
		}
	}

	gpio_pin_write(ENCODER_ABS_CS, true);
	return pos;
}
