#pragma once
//
//    FILE: I2C_ASDX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for I2C ASDX pressure sensor
//     URL: https://github.com/RobTillaart/I2C_ASDX
//
// HISTORY: See I2C_ASDX.cpp

// TESTED TYPES - type A 10% - 90% only
//
// ADDRESS   PRESSURE   RANGE          TYPE      P   A T V
// 0x58      100 psi    0..6895 mBar   SSCDANN 100PG 5 A 5
// 0x38       60 psi    0..4137 mbar   SSCDANN 060PG 3 A 5
// 0x28       30 psi    0..2068 mbar   SSCDANN 030PG 2 A 5
// 
// P = pressure range
// A = I2C address indicator
// T = accuracy range 
// V = voltage (3 volt also supported, not tested)
// 


#include "Wire.h"
#include "Arduino.h"

// factors to convert PSI to mBar and back
#define PSI2MBAR       68.9475729
#define MBAR2PSI       0.01450377377

#define I2C_ASDX_VERSION "0.2.0"

#define I2C_ASDX_OK              1
#define I2C_ASDX_INIT            0
#define I2C_ASDX_READ_ERROR     -1
#define I2C_ASDX_C000_ERROR     -2

class I2C_ASDX
{
public:
  //      psi: 100, 60, 30, 15
  I2C_ASDX(uint8_t address, uint8_t psi);

#if defined (ESP8266) || defined(ESP32)
  void     begin(uint8_t sda, uint8_t scl);
#endif
  void     begin();
  void     reset();
  bool     available();

  // returns status OK or ERROR
  int      read();
  // returns the pressure of last succesfull read
  // in mbar
  int      getPressure()  { return _pressure; };
  // # errors since last good read
  uint16_t errorCount()   { return _errorCount; };
  // timestamp of last good read
  uint32_t lastRead()     { return _lastRead; };
  // get the last state
  int      state()        { return _state; };
    
private:
  uint8_t  _address;
  uint16_t _maxPressure;
  uint8_t  _state;
  uint32_t _errorCount;
  uint32_t _pressure;
  uint32_t _lastRead;
};

// -- END OF FILE --
