<p align="center">
  <img align="center" width="60%" height="auto" src="./logo/minidenko-logo-r2-dark.png">
</p>

# miniDenko - A portable messaging device
`miniDenko` (Denko = 電光 is from "an electric scoreboard" in Japanese) is a portable messaging device.

Or LED Matrix + ESP8266 + MPU6050 + Modern Web framework(Vue.js + Buefy) = A hackable LED messaging platform

<p align="center">
  <img align="center" width="30%" height="auto" src="./images/md_2_sd.gif">
</p>

## Features
- Edit & save your message and show it up instantly.(Sub-second booting)
  - Also supports Japanese characters thanks to [Arduino-misakiUTF16](https://github.com/Tamakichi/Arduino-misakiUTF16) lib written by [[Tamakichi]](https://github.com/Tamakichi) san.
- Easily connectable with Phones, Laptops, etc. via WiFi.
  - Supports `STA`, `AP`, `AP_STA` modes to collaborate with the devices.
- Made from easily-obtainable parts. (See [#BOM](#BOM))
- Its [portable and slim shape](./openscad/minidenko-case-body-opaque.stl) fits in your (large) pocket.

- And as a latest gadget should be, equipped with the **Type-C** charging port.

## Project structure
- [`pio/`](./pio) - code for the firmware(PlatformIO)
- [`pio/webui/`](./pio/webui) - code for the WebUI(Vue.js + Buefy)
- [`kicad/`](./kicad) - PCB design (KiCad)
- [`gerber/`](./gerber) - PCB gerber files (KiCad)
- [`openscad/`](./openscad) - models for the 3D-printable case. (OpenSCAD)

## Gallery
|                                                                                                                                                                   | Descriptions              |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------- |
| <img align="center" width="auto" height="200px" src="./images/md_photo_duo_1.jpg">                                                                                | Front view                |
| <img align="center" width="auto" height="200px" src="./images/md_photo_side_port.jpg">                                                                            | Side view (Charging port) |
| <img align="center" width="auto" height="200px" src="./images/md_photo_side_sw.jpg">                                                                              | Side view (Power SW)      |
| <img align="center" width="auto" height="200px" src="./images/md_photo_pcb.jpg">                                                                                  | PCB                       |
| <img align="center" width="auto" height="200px" src="./images/md_webui_1_s.png"> <img align="center" width="auto" height="200px" src="./images/md_webui_2_s.png"> | Web UI                    |


## BOM
| Name                                    | Quantity | Descriptions |
| --------------------------------------- | :------: | ------------ |
| ESP-12F (ESP8266 module)                |    1     |              |
| 32x8 LED matrix module (MAX7219)        |    1     |              |
| GY-521 (MPU6050 module)                 |    1     | 8 pins       |
| 350mAh LiPo battery                     |    1     | 19x36x8.5 mm |
| Type-C LiPo charging board (TP4056)     |    1     | 28x17.3 mm   |
| 10k ohm resistor (0805_2012Metric)      |    4     |              |
| 33k ohm resistor (0805_2012Metric)      |    1     |              |
| 1uF ceramic capacitor (0805_2012Metric) |    1     |              |
| 3.3V LDO xc6206p332mr (SOT-23)          |    1     |              |
| SPDT rocker switch (10x15 mm)           |    1     |              |
| M1.2 x 5 mm self tapping screw          |    4     |              |
| M2 x 6 mm self tapping screw            |    2     |              |


## Build instructions
https://hackaday.io/project/167747/instructions

## Refs
- https://www.thingiverse.com/thing:3876563
- https://hackaday.io/project/167747-minidenko
  
## License
MIT