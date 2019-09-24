# miniDenko/firmware
It's built on top of [esp8266/Arduino](https://github.com/esp8266/Arduino).

## Prerequisites
- Install [PlatformIO](https://platformio.org/)

## Build
- `Ctrl+Alt+B` in your editor, or 
```bash
$ pio run
```

## Upload
- `Ctrl + Alt + U` in your editor, or 
```bash
$ pio run -t upload
```
- ***Tips:*** Don't forget to comment out the lines below to do ISP(UART) programming.
```bash
# platform.ini
upload_port = ${env:main.device_name}.local
upload_protocol = espota
```

## Build WebUI
- All the assets are gziped and included as C headers.
```bash
src/webui/app.js.gz.h
src/webui/favicon.ico.gz.h
src/webui/manifest.json.gz.h
src/webui/index.html.gz.h
...
```
- See [webui/README.md](./webui)