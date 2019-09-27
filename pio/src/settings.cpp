#include "settings.h"

bool SettingsService::begin() {
    bool ok = SPIFFS.begin();
    if(!ok) {
        return false;
    }
    ok = load();
    return ok;
}

void SettingsService::forceReset() {
    SPIFFS.format();
    initialize();
    load();
}

void SettingsService::initialize() {
    File file = SPIFFS.open(CONFIG_FILE_PATH, "w");
    if(!file) {
        Serial.println(F("Failed to create file"));
        return;
    }

    StaticJsonDocument<CONFIG_JSON_MAX> doc;
    auto msgsArray = doc.createNestedArray("messages");
    for(size_t i = 0; i < CONFIG_MSGS_NUM; i++) {
        auto msg = msgsArray.createNestedObject();
        msg["value"] = i == 0 ? "こんにちは! Hello! [miniDenko]" : "";
        msg["monospace"] = false;
        msg["scroll"] = true;
    }
    doc["hApName"] = "miniDenko-" + String(ESP.getChipId(), HEX);
    doc["hApPass"] = "";
    doc["cApName"] = "";
    doc["cApPass"] = "";
    doc["wifiMode"] = static_cast<int>(WiFiMode::WIFI_AP);
    doc["scrollWait"] = 50;
    doc["brightness"] = 10;
    doc["version"] = CONFIG_VERSION;

    if(serializeJson(doc, file) == 0) {
        Serial.println(F("Failed to write to file"));
    }

    file.close();
}

bool SettingsService::load() {
    File configFile = SPIFFS.open("/config.json", "r");
    if(!configFile) {
        Serial.println("Failed to open config file");
        return false;
    }

    size_t size = configFile.size();
    if(size > CONFIG_JSON_MAX) {
        Serial.println("Config file size is too large");
        return false;
    }

    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonDocument<CONFIG_JSON_MAX> doc;
    DeserializationError err = deserializeJson(doc, buf.get());
    if(err)
        return false;
    // TODO: error handling

    if(doc["version"].as<int>() != CONFIG_VERSION) {
        return false;
    }

    auto msgArray = doc["messages"].as<JsonArray>();
    for(size_t i = 0; i < CONFIG_MSGS_NUM; i++) {
        messages[i].value = msgArray[i]["value"].as<String>();
        messages[i].monospace = msgArray[i]["monospace"].as<bool>();
        messages[i].scroll = msgArray[i]["scroll"].as<bool>();
    }
    hApName = doc["hApName"].as<String>();
    hApPass = doc["hApPass"].as<String>();
    cApName = doc["cApName"].as<String>();
    cApPass = doc["cApPass"].as<String>();
    wifiMode = static_cast<WiFiMode>(doc["wifiMode"].as<int>());
    if(wifiMode == WIFI_OFF || wifiMode > WIFI_AP_STA) {
        wifiMode = WIFI_AP;
    }
    brightness = doc["brightness"].as<uint8_t>();
    scrollWait = doc["scrollWait"].as<uint8_t>();

    return true;
}

bool SettingsService::save(String json) {
    File file = SPIFFS.open("/config.json", "w");
    if(!file) {
        Serial.println("Failed to open config file");
        return false;
    }
    file.print(json);

    file.close();
}

void SettingsService::nextMessage(DenkoMessage &msg) {
    for(size_t i = 1; i <= CONFIG_MSGS_NUM; i++) {
        size_t idx = (currentMessageIdx + i) % CONFIG_MSGS_NUM;
        auto _msg = messages[idx];
        if(_msg.value.length()) {
            currentMessageIdx = idx;
            msg = _msg;
            return;
        }
    }
    return;
}
