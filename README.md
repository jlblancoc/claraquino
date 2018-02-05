# claraquino
Frustrated with Arduino debugging capabilities? This is your place ;-)

Copyright (C) 2016-2017 Jose Luis Blanco Claraco, University of Almería
Copyright (C) 2017      Francisco José Mañas, University of Almería
Licensed under: GNU GPL v3 License

![Claraquino board pic](https://jlblancoc.github.io/claraquino/imgs/claraquino-pic1-thumb.jpg)

# What's this?
An open-source hardware board to prototype with Atmel's **AVR8 microcontrollers** (ATMEGA164 for now),
**JTAG live-debuggable**, including a **versatile C library** for common peripherals and external sensors.

Core features:
* Busy-loop delays
* External interrupt inputs
* Internal ADCs
* Interrupt-driven UART communications
* GPIO
* PWM generation with programmable frequency
* SPI bus
* System tick clock with 100 μs resolution

Additional modules:
* Absolute encoder EMS22A
* Decoder for differential quadrature encoder (Interrupt-driven, up to ~300 K pulses/s)
* Digital-to-Analog (DAC) converter MAX5500
* `imu_lsm9ds1`: SparkFun LSM9DS1 9DOF IMU. Forked and adapted from [here](https://github.com/sparkfun/LSM9DS1_Breakout).
* `lcd`: Support for LCD displays via a I2C port expander. Forked and adapted from [here](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library).
* `ad7606`: Support for the Analog-to-Digital (ADC) chip AD7606.

# What's included in this repository?
* [Board schematics](https://github.com/jlblancoc/claraquino/tree/master/board)
* C library: [sources](https://github.com/jlblancoc/claraquino/tree/master/board), Doxygen HTML reference. Tested with GNU GCC within Atmel Studio.
* FTDI chip EEPROM XML image, to be grabbed with [FTPROG](http://www.ftdichip.com/Support/Utilities.htm).
