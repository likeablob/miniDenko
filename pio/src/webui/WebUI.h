#ifndef INCLUDE_GUARD_WEBUI_H
#define INCLUDE_GUARD_WEBUI_H

#include <ESP8266WebServer.h>
#include <WiFiClient.h>

class WebUI {
  private:
    /* data */
    ESP8266WebServer &_server;
    void handleIndex();
    void handleAppJs();
    void handleFavicon();
    void handleIcon128();
    void handleManifest();

  public:
    WebUI(ESP8266WebServer &server);
    void begin();
};

#endif // INCLUDE_GUARD_WEBUI_H