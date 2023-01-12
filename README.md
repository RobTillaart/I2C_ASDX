
[![Arduino CI](https://github.com/RobTillaart/I2C_ASDX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_ASDX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_ASDX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_ASDX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_ASDX/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_ASDX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_ASDX.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_ASDX/releases)


# I2C_ASDX

Arduino library for I2C ASDX pressure sensor.


## Description

The ASDX sensor of Honeywell exist in many variations.
Check the datasheet of your type for all the details.

The I2C_ASDX library can read the sensor and give the pressure in millibar, 
bar or PSI or many other units. See below.

#### Links

Related library: https://github.com/RobTillaart/pressure


#### Hardware connection

Always check datasheet for the exact pins.

```
        ASDX              ARDUINO
    +----------+        +----------+
    |          |        |          |
    |     GND o|--------|o GND     |
    |     VCC o|--------|o VCC     |
    |     SDA o|--------|o SDA     |
    |     SCL o|--------|o SCL     |
    |          |        |          |
    +----------+        +----------+
```



## Interface


#### Constructor

- **I2C_ASDX(uint8_taddress, uint8_t psi, TwoWire \*wire = &Wire)** Constructor, 
I2C address and maximum pressure. Optional the wire interface can be defined.
- **bool begin(uint8_t sda, uint8_t scl)** I2C parameters for ESP32 a.o. 
Returns true if address can be found  on I2C bus.
- **bool begin()** for UNO and other boards supporting Wire. 
Returns true if address can be found  on I2C bus.
- **void reset()** resets internal variables, including pressure.
- **bool isConnected()** tests if address can be found on I2C bus.
- **uint8_t getAddress()** returns I2C address used.
Mainly for debug message.


#### Read

Before any call to **getPressure()** one need to call **read()** unless one wants the last value read.

- **int read()** actually reads the sensor, checks for errors, 
calculates the pressure and set the lastRead timestamp. 
Returns **I2C_ASDX_OK** or an error code.


#### Units

- **int getPressure()** returns pressure in milliBar.
(rounded integer!).
Returns 0 after a reset() and no read() done yet.
Calling **getPressure()** multiple times without read() will return the same value again.
- **float getMilliBar()** returns pressure in milliBar (float).
- **float getBar()** returns pressure in bar.
- **float getPSI()** returns pressure in PSI = Pounds per Square Inch.
- **float getATM()** returns pressure in Atmosphere.
- **float getDynes()** returns pressure in Dynes.
- **float getInchHg()** returns pressure in inches mercury.
- **float getInchH2O()** returns pressure in inches water.
- **float getPascal()** returns pressure in Pascal. Note this is the SI unit.
- **float getTORR()** returns pressure in TORR.
- **float getCmHg()** returns pressure in centimetre mercury.
- **float getCmH2O()** returns pressure in centimetre water.
- **float getMSW()** returns pressure in Meters of Sea Water. (under water pressure unit).

Related library: https://github.com/RobTillaart/pressure


#### State

- **uint16_t errorCount()** total counter for the number of errors occurred.
- **uint32_t lastRead()** time in milliseconds of last successful read of the sensor.
- **int state()** last known state of read, also returned by **read()**

| state                   | meaning            |
|:------------------------|:-------------------|
| I2C_ASDX_OK             | no error           |
| I2C_ASDX_INIT           | begin() not called |
| I2C_ASDX_READ_ERROR     | I2C error          |
| I2C_ASDX_C000_ERROR     | sensor error       |
| I2C_ASDX_CONNECT_ERROR  | I2C error          |


#### Obsolete 0.3.3

- **bool available()** wrapper around isConnected.


## Testing

The library is tested with only 3 different sensors, all of the PG type.

Code is prepared but not tested for 15, 5 and 1 PSI too.

```
    ID    UNIT       TYPE   DESCRIPTION
                              output is proportional to difference
    PG    PSI        Gage   * between applied pressure and atmospheric pressure
    MG    mBar       Gage   * idem
    BG    Bar        Gage   * idem
    KG    KiloPascal Gage   * idem
     D    Differential      * between pressure applied to each of the ports.
     A    Absolute          * between applied pressure and built-in reference to vacuum.


    ADDRESS   PRESSURE   RANGE          TYPE      P   A T V
    0x58      100 psi    0..6895 mBar   SSCDANN 100PG 5 A 5
    0x38       60 psi    0..4137 mbar   SSCDANN 060PG 3 A 5
    0x28       30 psi    0..2068 mbar   SSCDANN 030PG 2 A 5

    P = pressure range
    A = I2C address indicator
    T = accuracy range
    V = voltage (3 volt also supported, not tested)
```

That said it is expected that the library is modifiable to support many
more as long as they have the following raw read values.

```
    1638  =   0 PSI
    14746 = max PSI
```


## Tested types

| Type number        |  result  |  notes  |
|:-------------------|:--------:|:--------|
|  SSCDANN 100PG 5A5 |    OK    |  type A 10% - 90% only
|  SSCDANN 060PG 3A5 |    OK    |
|  SSCDANN 030PG 2A5 |    OK    |

(elaborate test table)


## Operation

See examples


## Future

#### Must
- update documentation

#### Should
- add real life examples if possible
- add error/state code for after reset() and before read()
  - I2C_ASDX_NO_READ or I2C_ASDX_RESET

#### Could
- remove less common pressure formats from lib
  - are covered in pressure lib.
- move code from .h to .cpp
- **getPressure()** obsolete ? 
  - **getMillibar()**  ==> 0.4.0 ??


#### Wont
- find a good reference for conversion formula constants.

