# esp32-acqi-clock

Go to <https://spezifisch.codeberg.page/posts/2023-06-20/gt-acqi-22wo-digital-alarm-clock-hack/> for a write-up of this project.

## Files

* `acqi-clock.yaml` is the configuration file to be [used with ESPHome](https://esphome.io/guides/getting_started_command_line.html)
* `components` is an ESPHome C++ module to control the AiP1640 display controller.
* `espboard` is a KiCAD schematic of the perfboard and button matrix. See write-up for details.

## Credits

* `components/tm1640` is based on <https://github.com/realthk/esphome_tm1640>, which is based on <https://github.com/esphome/esphome/tree/dev/esphome/components/tm1637> (GPLv3). 

