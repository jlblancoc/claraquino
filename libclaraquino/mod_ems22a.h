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

/* File created: 20/07/2017 10:18:11
 *  Author: Francisco José Mañas
 */ 

#pragma once

#include <stdint.h>  // uint8_t, etc.

extern bool EMS22A_active;
extern bool ENCODERS_active;

/** Returns false on any error in the parameters. */
bool init_EMS22A(int8_t ENCODER_ABS_CS, int8_t ENCODER_ABS_CLK, int8_t ENCODER_ABS_DO, uint16_t sampling_period_ms);
uint16_t read_EMS22A();  // 193us @ 20MHz
