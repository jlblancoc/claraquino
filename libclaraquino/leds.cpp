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

#include "claraquino_config.h"
#include "leds.h"
#include "gpio.h"
#include "delays.h"
#include <avr/io.h>

void LED_ON()
{
	gpio_pin_mode(LED_PIN_NO, OUTPUT);
	gpio_pin_write(LED_PIN_NO, false);
}

void LED_OFF()
{
	gpio_pin_mode(LED_PIN_NO, OUTPUT);
	gpio_pin_write(LED_PIN_NO, true);
}

void flash_led(int ntimes, int nms)
{
	for (int i=0;i<ntimes;i++)
	{
		if (i>0) delay_ms(nms);
		LED_ON();  delay_ms(nms);
		LED_OFF();
	}
}