/*
 * adc_internal.h
 *
 * Created: 25/10/2017 1:57:23
 *  Author: jlblanco
 */ 

#pragma once

#include <stdint.h>  // uint8_t, etc.

/** Call to power on ADCs and configure them */
void adc_init(bool use_internal_vref = false);

/** Blocking init and read ADC reading */
uint16_t adc_read(uint8_t channel);
