/*
 * Encoder_EMS22A.h
 *
 * Created: 20/07/2017 10:18:11
 *  Author: Francisco José Mañas
 */ 


#ifndef ENCODER_EMS22A_H_
#define ENCODER_EMS22A_H_

#pragma once

#include <stdint.h>  // uint8_t, etc.

extern bool EMS22A_active;
extern bool ENCODERS_active;

/** Returns false on any error in the parameters. */
bool init_EMS22A(int8_t ENCODER_ABS_CS, int8_t ENCODER_ABS_CLK, int8_t ENCODER_ABS_DO, uint16_t sampling_period_ms);
uint16_t read_EMS22A();  // 193us @ 20MHz


#endif /* ENCODER_EMS22A_H_ */