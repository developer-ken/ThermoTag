#ifndef _H_M1820_
#define _H_M1820_

#include <Arduino.h>
#include <OneWire.h>

class M1820
{
public:
    M1820(OneWire *oneWire);
    bool Valid = false;
    static OneWire *oneWire;
    static void SampleNow();
    static float receiveTemperatureSkipRom();
    float receiveTemperature();
    byte Address[8];
};

#endif