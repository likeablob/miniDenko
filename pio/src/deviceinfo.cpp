#include "deviceinfo.h"

extern "C" {
#include "user_interface.h"
}

void DeviceInfo::begin() { deviceId = String(ESP.getChipId(), HEX); }
