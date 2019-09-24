#pragma once
#ifndef INCLUDE_GUARD_OTA_H
#define INCLUDE_GUARD_OTA_H

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include <denko.h>
extern Denko denko;

namespace OTAService {
void begin();
void handle();
} // namespace OTAService

#endif // INCLUDE_GUARD_OTA_H
