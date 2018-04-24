/*+-------------------------------------------------------------------------+
  |                             LibreDAQ                                    |
  |                                                                         |
  | Copyright (C) 2015  Jose Luis Blanco Claraco                            |
  | Distributed under GNU General Public License version 3                  |
  |   See <http://www.gnu.org/licenses/>                                    |
  +-------------------------------------------------------------------------+  */

#include "ad7606.h"
#include <libclaraquino/gpio.h>
#include <libclaraquino/delays.h>

static ad7606_config_t adc_cfg;

void mod_ad7606_init(const ad7606_config_t &cfg)
{
	adc_cfg = cfg;

	// CONVST: default=1
	gpio_pin_mode(cfg.PIN_CONVST, OUTPUT);
	gpio_pin_write(cfg.PIN_CONVST, true);

	// RD: default=1
	gpio_pin_mode(cfg.PIN_nRD, OUTPUT);
	gpio_pin_write(cfg.PIN_nRD, true);

	// DAQ_BUSY: input
	gpio_pin_mode(cfg.PIN_BUSY, INPUT_PULLUP);

	// DAQ_1STDATA: input
	gpio_pin_mode(cfg.PIN_1stDATA, INPUT_PULLUP);

	// DATA BUS:
	for (uint8_t i=0;i<8;i++)
		gpio_pin_mode(cfg.PIN_DATA[i], INPUT);

	// Send reset pulse: (min 50ns)
	gpio_pin_write(cfg.PIN_RESET, false);
	gpio_pin_mode(cfg.PIN_RESET, OUTPUT);

	gpio_pin_write(cfg.PIN_RESET, true);
	delay_us(100);
	gpio_pin_write(cfg.PIN_RESET, false);
}

void mod_ad7606_convst()
{
	// minimum low pulse: 25 ns
	gpio_pin_write(adc_cfg.PIN_CONVST, false);
	delay_us(1);
	gpio_pin_write(adc_cfg.PIN_CONVST, true);
}

void mod_ad7606_wait_busy()
{
	while (gpio_pin_read(adc_cfg.PIN_BUSY))
	{}
}

/** Checks whether the ADC is busy during a conversion (returns!=0) or it has done (returns 0) */
bool mod_ad7606_check_busy()
{
	return gpio_pin_read(adc_cfg.PIN_BUSY);
}

static uint8_t ad7606_read_byte()
{
	uint8_t b = 0;
	for (uint8_t k=0;k<8;k++)
		b = b | ((gpio_pin_read(adc_cfg.PIN_DATA[k]) ? 1:0) << k);
	return b;
}

/** Read all 8 channels. Output buffer must be [2*8] bytes long */
void mod_ad7606_read_all(int16_t *buf)
{
	// nCS: linked to nRD:

	// Store int16_t as little endian.
	// high-byte sent first.
	for (int8_t i=0;i<8;i++)
	{
		bool read_1st;
		// /RD low pulse: should be ~25ns (+ delay in propagation until PIO_PDSR)
		gpio_pin_write(adc_cfg.PIN_nRD, false); // nRD=0
		asm ("nop");asm ("nop");
		const uint8_t bh = ad7606_read_byte();
		read_1st = gpio_pin_read(adc_cfg.PIN_1stDATA);
		gpio_pin_write(adc_cfg.PIN_nRD, true); // nRD=1
		asm ("nop");asm ("nop");

		gpio_pin_write(adc_cfg.PIN_nRD, false); // nRD=0
		asm ("nop");asm ("nop");
		const uint8_t bl = ad7606_read_byte();
		gpio_pin_write(adc_cfg.PIN_nRD, true); // nRD=1

		// If we missed a channel, iterate until we re-synchronize again:
		if (i==0 && !read_1st)
		{
			i--;
			continue;
		}
		*buf++ = (((uint16_t)bh) << 8) | bl;
	}
}
