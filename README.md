# I2C_ASDX

Arduino library for I2C ASDX pressure sensor

## Description

TODO

```
    TESTED TYPES - type A 10% - 90% only

    ADDRESS   PRESSURE   RANGE          TYPE      P   A T V
    0x58      100 psi    0..6895 mBar   SSCDANN 100PG 5 A 5
    0x38       60 psi    0..4137 mbar   SSCDANN 060PG 3 A 5
    0x28       30 psi    0..2068 mbar   SSCDANN 030PG 2 A 5

    P = pressure range
    A = I2C address indicator
    T = accuracy range 
    V = voltage (3 volt also supported, not tested)
```

## Operation

See examples
