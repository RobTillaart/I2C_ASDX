#pragma once
//
//    FILE: I2C_ASDX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library for I2C ASDX pressure sensor.
//     URL: https://github.com/RobTillaart/I2C_ASDX


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


#define I2C_ASDX_VERSION                  (F("0.3.3"))


//  factors to convert PSI to mBar and back
#define PSI2MILLIBAR                      68.9475729
#define MILLIBAR2PSI                      0.01450377377
#define PSI2BAR                           0.0689475729
#define BAR2PSI                           14.503773773

//  factors to convert from mBar to different units
//  note: different sources give slightly different values 
#define MILLIBAR2BAR                      0.001
#define MILLIBAR2ATM                      9.872e-4
#define MILLIBAR2DYNES                    1000
#define MILLIBAR2INHG                     2.9539e-2
#define MILLIBAR2INH2O                    0.4018
#define MILLIBAR2PASCAL                   100
#define MILLIBAR2TORR                     0.75028
#define MILLIBAR2CMHG                     0.075028
#define MILLIBAR2CMH2O                    1.02056
#define MILLIBAR2MSW                      100


#define I2C_ASDX_OK                        1
#define I2C_ASDX_INIT                      0
#define I2C_ASDX_READ_ERROR               -1
#define I2C_ASDX_C000_ERROR               -2
#define I2C_ASDX_CONNECT_ERROR            -3


class I2C_ASDX
{
public:
  //      psi: 100, 60, 30, 15, 5 or 1
  I2C_ASDX(uint8_t address, uint8_t psi, TwoWire *wire = &Wire);


#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl);
#endif
  bool     begin();
  void     reset();
  bool     isConnected();
  uint8_t  getAddress();
  //  bool     available() { return isConnected(); };  // obsolete 0.3.3


  //  returns status OK (0) or ERROR ( not 0 )
  int      read();


  //  returns the pressure of last successful read in mbar
  int      getPressure()  { return round(_pressure); };
  float    getMilliBar()  { return _pressure; };
  float    getBar()       { return _pressure * MILLIBAR2BAR; };
  float    getPSI()       { return _pressure * MILLIBAR2PSI; };

  //  conversions added 0.2.3
  float    getATM()       { return _pressure * MILLIBAR2ATM; }
  float    getDynes()     { return _pressure * MILLIBAR2DYNES; }
  float    getInchHg()    { return _pressure * MILLIBAR2INHG; }
  float    getInchH2O()   { return _pressure * MILLIBAR2INH2O; }
  float    getPascal()    { return _pressure * MILLIBAR2PASCAL; }
  float    getTORR()      { return _pressure * MILLIBAR2TORR; }
  float    getCmHg()      { return _pressure * MILLIBAR2CMHG; }
  float    getCmH2O()     { return _pressure * MILLIBAR2CMH2O; }
  float    getMSW()       { return _pressure * MILLIBAR2MSW; }


  //  # errors since last good read
  uint16_t errorCount()   { return _errorCount; };
  //  timestamp of last good read
  uint32_t lastRead()     { return _lastRead; };
  //  get the last state
  int      state()        { return _state; };


private:
  uint8_t  _address;
  TwoWire*  _wire;

  float    _maxPressure;
  float    _pressure;
  
  uint8_t  _state;
  uint32_t _errorCount;
  uint32_t _lastRead;
};


//  Convertors ==> see https://github.com/RobTillaart/pressure library.
/*
static float MilliBar2PSI( float mbar ) { return mbar * MILLIBAR2PSI; };
static float MilliBar2Bar( float mbar ) { return mbar * 0.001; };
static float Bar2MilliBar( float bar )  { return bar * 1000; };
static float Bar2PSI( float bar )       { return bar * BAR2PSI; };
static float PSI2MilliBar( float PSI )  { return PSI * PSI2MILLIBAR; };
static float PSI2Bar( float PSI )       { return PSI * PSI2BAR; };
*/

// -- END OF FILE --

