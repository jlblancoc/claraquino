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

#include "adc_internal.h"
#include <avr/io.h>

void adc_init(bool use_internal_vref)
{
	if (use_internal_vref)
	{
		//Volt. ref= internal 2.56V
		ADMUX |= (1<<REFS0);
		ADMUX |= ~(1<<REFS1);
	}
	else
	{
		//Avcc(+5v) as voltage reference
		ADMUX |= (1<<REFS0);
		ADMUX &= ~(1<<REFS1);
	}
	
	//Prescaler at 128 -> 20Mhz/128 = 156.25Khz ADC clock
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));

	// Power up
	ADCSRA |= (1<<ADEN);
}

uint16_t adc_read(uint8_t channel)
{
	// Channel selection:
	ADMUX = (ADMUX & ~(0x0F)) | channel;
	
	// Start:
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC))
	{
	}
	return ADC;
}

