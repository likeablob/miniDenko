#pragma once
#ifndef INCLUDE_GUARD_DEVICEINFO_H
#define INCLUDE_GUARD_DEVICEINFO_H

#include <Arduino.h>

class DeviceInfo {
  public:
    String deviceId;
    void begin();
};

#endif // INCLUDE_GUARD_DEVICEINFO_H
