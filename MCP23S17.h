#pragma once

#include "ISPI.h"

class MCP23S17
{
public:
  enum Error { OK, PIN_ERROR, SPI_ERROR, VALUE_ERROR, PORT_ERROR, REGISTER_ERROR, INVALID_READ };

  MCP23S17(ispi::SPI* spi, int address = 0x00);

  bool     begin(bool pullup = true);
  bool     isConnected();
  uint8_t  getAddress();   //  default returns 0x00


  enum PinMode { INPUT, INPUT_PULLUP, OUTPUT };
  enum InterruptMode { CHANGE, RISING, FALLING };
  //       single pin interface
  //       mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
  //             do not use 0, 1 for mode.
  bool     pinMode1(uint8_t pin, PinMode mode);
  bool     write1(uint8_t pin, uint8_t value);
  uint8_t  read1(uint8_t pin);

  bool     setPolarity(uint8_t pin, bool reversed);
  bool     getPolarity(uint8_t pin, bool &reversed);
  bool     setPullup(uint8_t pin, bool pullup);
  bool     getPullup(uint8_t pin, bool &pullup);


  //       8 pins interface
  //       port  = 0..1
  //       mask  = 0x00..0xFF  bit pattern, 
  //               bit 0 = output mode, bit 1 = input mode
  //       value = bit pattern.
  bool     pinMode8(uint8_t port, uint8_t mask);
  bool     write8(uint8_t port, uint8_t value);
  int      read8(uint8_t port);

  bool     setPolarity8(uint8_t port, uint8_t mask);
  bool     getPolarity8(uint8_t port, uint8_t &mask);
  bool     setPullup8(uint8_t port, uint8_t mask);
  bool     getPullup8(uint8_t port, uint8_t &mask);


  //       16 pins interface
  //       mask = 0x0000..0xFFFF bit pattern
  //              bit 0 = output mode, bit 1 = input mode
  //       value = bit pattern.
  bool     pinMode16(uint16_t mask);
  bool     write16(uint16_t value);
  uint16_t read16();

  bool     setPolarity16(uint16_t mask);
  bool     getPolarity16(uint16_t &mask);
  bool     setPullup16(uint16_t mask);
  bool     getPullup16(uint16_t &mask);


  //       INTERRUPTS (experimental)
  //       pin = 0..15, mode = { RISING, FALLING, CHANGE }
  bool     enableInterrupt(uint8_t pin, InterruptMode mode);
  bool     disableInterrupt(uint8_t pin);
  
  //       mask = 0x0000..0xFFFF  (overrides all earlier settings.
  bool     enableInterrupt16(uint16_t mask, InterruptMode mode);
  bool     disableInterrupt16(uint16_t mask);

  //       which pins caused the INT?
  uint16_t getInterruptFlagRegister();
  uint16_t getInterruptCaptureRegister();

  //       polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
  bool     setInterruptPolarity(uint8_t polarity);
  uint8_t  getInterruptPolarity();

  //       merge INTA and INTB
  bool     mirrorInterrupts(bool on);
  bool     isMirroredInterrupts();

  int      lastError();

  //       set/clear IOCR bit fields
  bool     enableControlRegister(uint8_t mask);
  bool     disableControlRegister(uint8_t mask);
  //       0.2.5 experimental
  bool     enableHardwareAddress();
  bool     disableHardwareAddress();

protected:
  //       access to low level registers (just make these functions public).
  //       USE WITH CARE !!!
  bool     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);
  bool     writeReg16(uint8_t reg, uint16_t value);
  uint16_t readReg16(uint8_t reg);

  uint8_t  _address = 0;
  uint8_t  _select  = 0;
  uint8_t  _dataOut = 0;
  uint8_t  _dataIn  = 0;
  uint8_t  _clock   = 0;
  uint8_t  _error;

  ispi::SPI* _mySPI;
};


//  -- END OF FILE --

