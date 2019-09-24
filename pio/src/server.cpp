#include "server.h"

ESP8266WebServer server(80);
WebUI webUI(server);

void handleMessage() {
    String body = server.arg("plain");

    StaticJsonDocument<CONFIG_JSON_MAX> doc;
    DeserializationError err = deserializeJson(doc, body);
    if(err) {
    };
    auto messageValue = doc["value"];
    if(messageValue.is<String>()) {
        denko.drawStr(doc["value"].as<String>(), doc["monospace"].as<bool>());
        denko.enableScroll = doc["scroll"].as<bool>();
        denko.draw();
    }

    server.send(200, "text/plain", "OK");
}

void onNotFound_() {
    String message = "404: No such file\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for(uint8_t i = 0; i < server.args(); i++) {
        message +=
            " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

#define BAT_RRATE (4.21) // (10k+33k)/(10k)
void handleDeviceInfo() {
    uint16_t batv = system_adc_read();

    StaticJsonDocument<512> doc;
    doc["name"] = DEVICE_NAME;
    doc["batv"] = batv * BAT_RRATE;
    doc["uptime"] = millis() / 1000;
    doc["ip_c"] = WiFi.localIP().toString();
    doc["ip_h"] = WiFi.softAPIP().toString();
    doc["wifi_c"] = WiFi.isConnected();
    doc["chip_id"] = ESP.getChipId();
    doc["cpu_f"] = ESP.getCpuFreqMHz();
    doc["vcc"] = ESP.getVcc();
    doc["flash_rs"] = ESP.getFlashChipRealSize();
    doc["heap_f"] = ESP.getFreeHeap();
    doc["board_rev"] = BOARD_REVISION;

    String res = "";
    serializeJson(doc, res);
    server.send(200, "text/plain", res);
}

void handleGetSettings() {
    File file = SPIFFS.open("/config.json", "r");
    if(!file) {
        Serial.println("Failed to open config file");
        server.send(500, "text/plain", "err");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleSaveConfig() {
    String body = server.arg("plain");
    bool ok = settingsService.save(body);
    if(ok) {
        ok = settingsService.load();
    }
    if(!ok) {
        settingsService.initialize();
    }

    denko.setBrightness(settingsService.brightness);
    denko.setRefreshInterval(settingsService.scrollWait);

    if(ok) {
        server.send(200, "text/json", body);
    } else {
        server.send(500, "text/json", "{\"ok\":false}");
    }
}

void handleGetWiFiScan() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    int n = WiFi.scanNetworks();
    const int capacity = JSON_OBJECT_SIZE(32) + (32 + 4) * 32;
    StaticJsonDocument<capacity> doc;
    JsonArray array = doc.to<JsonArray>();
    int len = max(n, 32);
    for(int i = 0; i < len; i++) {
        JsonObject nested = array.createNestedObject();
        nested["ssid"] = WiFi.SSID(i);
        nested["rssi"] = WiFi.RSSI(i);
    }
    String res;
    serializeJson(doc, res);
    server.send(200, "text/json", res);
}

void handleCaptivePortal() {
    server.sendHeader("Location",
                      String("http://") + WiFi.softAPIP().toString(), true);
    server.send(302, "text/plain", "302");
}

void ServerService::begin() {
    webUI.begin();
    server.onNotFound(onNotFound_);
    server.on("/api/message", HTTP_POST, handleMessage);
    server.on("/api/device", HTTP_GET, handleDeviceInfo);
    server.on("/api/settings", HTTP_GET, handleGetSettings);
    server.on("/api/settings", HTTP_POST, handleSaveConfig);
    server.on("/api/wifi/scan", HTTP_GET, handleGetWiFiScan);
    server.on("/gen_204", HTTP_GET, handleCaptivePortal);
    server.begin();
}

void ServerService::handle() { server.handleClient(); }