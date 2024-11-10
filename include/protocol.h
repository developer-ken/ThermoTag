#ifndef _H_PROTOCOL_
#define _H_PROTOCOL_

#include <Arduino.h>

struct ReportPack{
    float Temperature;
    uint8_t BatteryLevel;
    bool Charging;
};

#endif