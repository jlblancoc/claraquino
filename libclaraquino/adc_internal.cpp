/*
 * adc_internal.cpp
 *
 * Created: 25/10/2017 1:57:12
 *  Author: jlblanco
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

