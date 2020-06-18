//
//    FILE: asdx_minimal.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-06-18
//    (c) : MIT
//

#include "I2C_ASDX.h"

// adjust to type of sensor
I2C_ASDX sensor(0x58, 100);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  sensor.begin();
}

void loop()
{
  int state = sensor.read();
  if (state == I2C_ASDX_OK)
  {
    Serial.print("P:\t");
    Serial.println(sensor.getPressure());
  }
}

// =- END OF FILE --
