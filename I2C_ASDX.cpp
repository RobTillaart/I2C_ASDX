//
//    FILE: I2C_ASDX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: I2C_asdx library for Arduino.
//     URL: https://github.com/RobTillaart/I2C_ASDX
//
// HISTORY:
// 0.1.0    2013-11-14 initial version
// 0.2.0    2020-03-18 refactor
//

#include "I2C_ASDX.h"

I2C_ASDX::I2C_ASDX(uint8_t address, uint8_t psi)
{
  _address = address;
  if (psi == 100) _maxPressure = 6895;
  if (psi ==  60) _maxPressure = 4137;
  if (psi ==  30) _maxPressure = 2068;
  if (psi ==  15) _maxPressure = 1034;
  _maxPressure = 0;  // force fail in other cases
  reset();
}

#if defined (ESP8266) || defined(ESP32)
void I2C_ASDX::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  reset();
}
#endif

void I2C_ASDX::begin()
{
  Wire.begin();
  reset();
}

void I2C_ASDX::reset()
{
  _state = I2C_ASDX_INIT;
  _errorCount = 0;
  _lastRead = 0;
  _pressure = 0;
}

bool I2C_ASDX::available()
{
  Wire.beginTransmission(_address);
  return (Wire.endTransmission() == 0);
}

int I2C_ASDX::read()
{
  Wire.requestFrom(_address, (uint8_t)2);
  if (Wire.available() != 2)
  {
    _errorCount++;
    _state = I2C_ASDX_READ_ERROR;
    return _state;
  }
  int count = Wire.read() * 256;  // hi byte
  count    += Wire.read();        // lo byte
  if (count & 0xC000)
  {
    _errorCount++;
    _state = I2C_ASDX_C000_ERROR;  // no documentation, bits may not be set?
    return _state;
  }
  _pressure = map(count, 1638, 14746, 0, _maxPressure);
  _state = I2C_ASDX_OK;
  _lastRead = millis();
  return _state;
}

// -- END OF FILE --
