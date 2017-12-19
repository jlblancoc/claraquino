/*
 * leds.cpp
 *
 * Created: 25/10/2017 2:08:50
 *  Author: jlblanco
 */ 

#include "../config.h"
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