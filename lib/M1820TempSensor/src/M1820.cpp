#include <Arduino.h>
#include "M1820.h"

OneWire *M1820::oneWire;

M1820::M1820(OneWire *oneWire)
{
    M1820::oneWire = oneWire;
}

float M1820::receiveTemperature()
{
    oneWire->reset();         // Reset the 1-Wire bus
    oneWire->select(Address); // Select the sensor
    oneWire->write(0xBE);     // Read data without using scratchpad

    byte data[2];
    // Read two bytes of data
    data[0] = oneWire->read();
    data[1] = oneWire->read();

    if (data[0] == 0xFF && data[1] == 0xFF)
    {
        return -256; // Return -256 if the sensor is not connected
    }

    // Combine the two bytes into a 16-bit raw temperature value
    unsigned short rawTemperature = (data[1] << 8) | data[0];

    // Convert raw temperature value to Celsius
    float temperature = (((short)rawTemperature) / 256.0 + 40.0);
    return temperature;
}

void M1820::SampleNow()
{
    oneWire->reset();
    oneWire->write(0xCC); // SkipRom     广播
    oneWire->write(0x44); // Convert T   现在采集温度
    delay(150);           //            等待转换完成
}

float M1820::receiveTemperatureSkipRom()
{
    oneWire->reset();         // Reset the 1-Wire bus
    oneWire->write(0xCC);     // SkipRom
    oneWire->write(0xBE);     // Read data without using scratchpad

    byte data[2];
    // Read two bytes of data
    data[0] = oneWire->read();
    data[1] = oneWire->read();

    if (data[0] == 0xFF && data[1] == 0xFF)
    {
        return -256; // Return -256 if the sensor is not connected
    }

    // Combine the two bytes into a 16-bit raw temperature value
    unsigned short rawTemperature = (data[1] << 8) | data[0];

    // Convert raw temperature value to Celsius
    float temperature = (((short)rawTemperature) / 256.0 + 40.0);
    return temperature;
}