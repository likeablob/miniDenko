#include <Arduino.h>
#include <LedControl.h>

extern "C" {
#include "user_interface.h"
}

#include "config.h"
#include "denko.h"
#include "motion.h"
#include "ota.h"
#include "server.h"
#include "settings.h"
#include "wifi.h"

#include "DNSServer.h"

#define DNS_PORT 53
DNSServer dnsServer;

SettingsService settingsService;
LedControl lc = LedControl(PIN_LED_DATA, PIN_LED_CLK, PIN_LED_CS, NUM_DISP);
Denko denko(lc);

void setup() {
    Serial.begin(115200);
    Serial.println("Booting");

    denko.begin();
    OTAService::begin();
    if(!settingsService.begin()) {
        denko.drawStr("Reset");
        delay(1000);
        settingsService.forceReset();
    }
    MotionService::begin();
    ServerService::begin();
    WiFiService::switchMode(settingsService.wifiMode, settingsService.hApName,
                            settingsService.hApPass, settingsService.cApName,
                            settingsService.cApPass);

    // dnsServer.start(DNS_PORT, "*", apIP);
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    DenkoMessage msg("No suitable message found.", false, true);
    settingsService.nextMessage(msg);
    denko.drawMsg(msg);
    denko.setBrightness(settingsService.brightness);
    denko.setRefreshInterval(settingsService.scrollWait);
}

void loop() {
    // dnsServer.processNextRequest();
    OTAService::handle();
    ServerService::handle();
    MotionService::handle();
    denko.handle();
}
