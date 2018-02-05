/*+-------------------------------------------------------------------------+
  |                             LibreDAQ                                    |
  |                                                                         |
  | Copyright (C) 2015  Jose Luis Blanco Claraco                            |
  | Distributed under GNU General Public License version 3                  |
  |   See <http://www.gnu.org/licenses/>                                    |
  +-------------------------------------------------------------------------+  */
#pragma once

#include <stdint.h>  // uint8_t, etc.

/** \file ADC module with chip AD7606 */

struct ad7606_config_t
{
	uint8_t PIN_CONVST;
	uint8_t PIN_nRD;
	uint8_t PIN_BUSY;
	uint8_t PIN_1stDATA;
	uint8_t PIN_RESET;
	uint8_t PIN_DATA[8];
};

/** Initialize the device */
void mod_ad7606_init(const ad7606_config_t &cfg);

/** Generate a convert start pulse */
void mod_ad7606_convst();

/** Busy loops until the ADC gets out of "busy" (converting) */
void mod_ad7606_wait_busy();

/** Checks whether the ADC is busy during a conversion (returns!=0) or it has done (returns 0) */
bool mod_ad7606_check_busy();

/** Read all 8 channels. Output buffer must be [2*8] bytes long */
void mod_ad7606_read_all(int16_t *buf);

void task_ad7606_start_conversion();
void adc_busy_edge_handler(uint32_t a,uint32_t b);

