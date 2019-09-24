#include "WebUI.h"

#include "app.js.gz.h"
#include "favicon.ico.gz.h"
#include "icon_128x128.png.gz.h"
#include "index.html.gz.h"
#include "manifest.json.gz.h"

void WebUI::handleIndex() {
    _server.sendHeader("Content-Encoding", "gzip");
    _server.sendHeader("Cache-Control", "max-age=31556926");
    _server.setContentLength(dist_index_html_gz_len);
    _server.send_P(200, PSTR("text/html"), (PGM_P)dist_index_html_gz,
                   dist_index_html_gz_len);
}

void WebUI::handleAppJs() {
    _server.sendHeader("Content-Encoding", "gzip");
    _server.sendHeader("Cache-Control", "max-age=31556926");
    _server.setContentLength(dist_app_js_gz_len);
    _server.send(200, "text/javascript");
    _server.sendContent_P((PGM_P)dist_app_js_gz, dist_app_js_gz_len);
}

void WebUI::handleFavicon() {
    _server.sendHeader("Content-Encoding", "gzip");
    _server.sendHeader("Cache-Control", "max-age=31556926");
    _server.setContentLength(dist_favicon_ico_gz_len);
    _server.send(200, "image/x-icon");
    _server.sendContent_P((PGM_P)dist_favicon_ico_gz, dist_favicon_ico_gz_len);
}

void WebUI::handleIcon128() {
    _server.sendHeader("Content-Encoding", "gzip");
    _server.sendHeader("Cache-Control", "max-age=31556926");
    _server.setContentLength(dist_icon_128x128_png_gz_len);
    _server.send(200, "image/png");
    _server.sendContent_P((PGM_P)dist_icon_128x128_png_gz,
                          dist_icon_128x128_png_gz_len);
}

void WebUI::handleManifest() {
    _server.sendHeader("Content-Encoding", "gzip");
    _server.sendHeader("Cache-Control", "max-age=31556926");
    _server.setContentLength(dist_manifest_json_gz_len);
    _server.send(200, "text/javascript");
    _server.sendContent_P((PGM_P)dist_manifest_json_gz,
                          dist_manifest_json_gz_len);
}

WebUI::WebUI(ESP8266WebServer &server) : _server(server) {}

void WebUI::begin() {
    _server.on("/", HTTP_GET, [&]() { handleIndex(); });
    _server.on("/app.js", HTTP_GET, [&]() { handleAppJs(); });
    _server.on("/favicon.ico", HTTP_GET, [&]() { handleFavicon(); });
    _server.on("/icon_128x128.png", HTTP_GET, [&]() { handleIcon128(); });
    _server.on("/manifest.json", HTTP_GET, [&]() { handleManifest(); });
}
