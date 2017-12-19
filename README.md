# claraquino
AVR microcontroller prototyping, made better.

# What's this?
An open-source hardware board to prototype with Atmel's AVR8 microcontrollers (ATMEGA164 for now),
including a versatile C library for common peripherals and external sensors:
* Busy-loop delays
* External interrupt inputs
* Internal ADCs
* Interrupt-driven UART communications
* GPIO
* PWM generation with programmable frequency
* SPI bus
* System tick clock with 100 μs resolution

# What's included in this repository?
* Board schematics
* C library. Tested with GNU GCC within Atmel Studio.
* FTDI chip EEPROM XML image, to be grabbed with [FTPROG](http://www.ftdichip.com/Support/Utilities.htm).
