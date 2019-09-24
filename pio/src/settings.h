#ifndef INCLUDE_GUARD_SETTINGS_H
#define INCLUDE_GUARD_SETTINGS_H

#define CONFIG_FILE_PATH "/config.json"
#define CONFIG_JSON_MAX 1024 // TODO: calclulate
#define CONFIG_VERSION 0
#define CONFIG_MSGS_NUM 3

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <denko.h>

class SettingsService {
  private:
    uint8_t currentMessageIdx;

  public:
    bool begin();
    bool load();
    void initialize();
    void forceReset();
    bool save(String json);
    void nextMessage(DenkoMessage &msg);
    DenkoMessage messages[CONFIG_MSGS_NUM];
    String hApName; // Host AP Name (SSID)
    String hApPass; // Host AP Password
    String cApName; // Client AP Name (SSID)
    String cApPass; // Client AP Password
    WiFiMode wifiMode;
    uint8_t scrollWait;
    uint8_t brightness;
};

#endif // INCLUDE_GUARD_SETTINGS_H
