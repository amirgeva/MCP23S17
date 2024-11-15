# MCP23S17
MCP23S17 IO Expander chip library


This library is based on code from:
https://github.com/RobTillaart/MCP23S17


The changes in design and details are large enough to make me choose to make it independent and not simply a fork.

The main change I saw needed was the encapsulation of the SPI details out of the library, so that the code could be used in a non-Arduino project, as was the case I was working on, using the RaspberryPi Pico SDK.

I therefore made a generic SPI interface class and use it from the MCP23S17 class.  I also include an implementation of the SPI class for the Pico SDK case.