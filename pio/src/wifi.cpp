#include "wifi.h"

IPAddress apIP(192, 168, 5, 1);
Chrono wifiTask;

void WiFiService::startAP(String ssid, String password) {
    WiFi.disconnect();
    WiFi.softAPdisconnect();

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, password);
};

void WiFiService::startSTA(String ssid, String password) {
    WiFi.disconnect();
    WiFi.softAPdisconnect();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
};

void WiFiService::startAPSTA(String apSSID, String apPassword, String staSSID,
                             String staPassword) {
    WiFi.disconnect();
    WiFi.softAPdisconnect();

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(apSSID, apPassword);
    WiFi.begin(staSSID, staPassword);
};

void WiFiService::switchMode(WiFiMode mode, String apSSID, String apPassword,
                             String staSSID, String staPassword) {
    modeStartTime = millis();
    if(mode == WIFI_AP) {
        WiFiService::startAP(apSSID, apPassword);
    } else if(mode == WIFI_STA) {
        WiFiService::startSTA(staSSID, staPassword);
    } else if(mode == WIFI_AP_STA) {
        WiFiService::startAPSTA(apSSID, apPassword, staSSID, staPassword);
    } else if(mode == WIFI_OFF) {
        WiFi.mode(WIFI_OFF);
    }
}

void WiFiService::handle(
    const std::function<const void()> &onConnectionFailed) {
    if(WiFi.getMode() == WIFI_STA && wifiTask.hasPassed(WIFI_TASK_INTERVAL)) {
        wifiTask.restart();
        if(modeStartTime + staTimeout < millis() && !WiFi.isConnected()) {
            onConnectionFailed();
        }
    }
}
