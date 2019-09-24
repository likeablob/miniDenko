#include "ota.h"

extern "C" {
#include "user_interface.h"
}

void OTAService::begin() {
    ArduinoOTA.setHostname(DEVICE_NAME);
    ArduinoOTA.onStart([]() {
        denko.drawStr("Start");
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() { denko.drawStr("Done"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        char buff[64];
        uint8_t percent = (progress / (total / 100));
        sprintf(buff, "%u%%", percent);
        denko.drawStr(buff);
        // lc.setLed(3, 0, 0, percent%2);
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if(error == OTA_AUTH_ERROR)
            Serial.println("Auth Failed");
        else if(error == OTA_BEGIN_ERROR)
            Serial.println("Begin Failed");
        else if(error == OTA_CONNECT_ERROR)
            Serial.println("Connect Failed");
        else if(error == OTA_RECEIVE_ERROR)
            Serial.println("Receive Failed");
        else if(error == OTA_END_ERROR)
            Serial.println("End Failed");
    });
    ArduinoOTA.begin();
}

void OTAService::handle() { ArduinoOTA.handle(); }
