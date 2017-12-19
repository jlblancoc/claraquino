# claraquino
Frustrated with Arduino debugging capabilities? This is your place ;-)

Copyright (C) 2017 Jose Luis Blanco Claraco, University of Almería
GNU GPL v3 License

![Claraquino board pic](https://jlblancoc.github.io/claraquino/imgs/claraquino-pic1-thumb.jpg)

# What's this?
An open-source hardware board to prototype with Atmel's **AVR8 microcontrollers** (ATMEGA164 for now),
**JTAG live-debuggable**, including a **versatile C library** for common peripherals and external sensors:
* Busy-loop delays
* External interrupt inputs
* Internal ADCs
* Interrupt-driven UART communications
* GPIO
* PWM generation with programmable frequency
* SPI bus
* System tick clock with 100 μs resolution

# What's included in this repository?
* [Board schematics](https://github.com/jlblancoc/claraquino/tree/master/board)
* C library: [sources](https://github.com/jlblancoc/claraquino/tree/master/board), Doxygen HTML reference. Tested with GNU GCC within Atmel Studio.
* FTDI chip EEPROM XML image, to be grabbed with [FTPROG](http://www.ftdichip.com/Support/Utilities.htm).
