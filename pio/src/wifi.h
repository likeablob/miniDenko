#ifndef INCLUDE_GUARD_WIFI_H
#define INCLUDE_GUARD_WIFI_H

#include "settings.h"
#include <Chrono.h>
#include <ESP8266WiFi.h>

extern IPAddress apIP;

#define WIFI_DEFAULT_TIMEOUT 10000 // 10sec
#define WIFI_TASK_INTERVAL 1000    // 1sec

namespace WiFiService {
static uint64_t modeStartTime = millis();
static uint16_t staTimeout = WIFI_DEFAULT_TIMEOUT;

void startAP(String ssid, String password);
void startSTA(String ssid, String password);
void startAPSTA(String apSSID, String apPassword, String staSSID,
                String staPassword);
void switchMode(WiFiMode mode, String apSSID, String apPassword, String staSSID,
                String staPassword);

void handle(const std::function<const void()> &onConnectionFailed);

String scan();
} // namespace WiFiService

#endif // INCLUDE_GUARD_WIFI_H
