#pragma once
#ifndef INCLUDE_GUARD_SERVER_H
#define INCLUDE_GUARD_SERVER_H

#include "config.h"
#include "denko.h"
#include "settings.h"
#include "webui/WebUI.h"
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

extern ESP8266WebServer server;
extern Denko denko;
extern SettingsService settingsService;

namespace ServerService {
void begin();
void handle();

} // namespace ServerService

#endif // INCLUDE_GUARD_SERVER_H
