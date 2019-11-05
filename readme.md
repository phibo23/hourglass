# hourglass

## hardware

* NodeMCU V2
  * https://www.exp-tech.de/module/wireless/wifi/6534/nodemcu-v2-lua-based-esp8266
* Adafruit LIS3DH
  * https://www.exp-tech.de/sensoren/beschleunigung/6790/adafruit-lis3dh-triple-axis-accelerometer-2g/4g/8g/16g
  * https://learn.adafruit.com/circuitpython-hardware-lis3dh-accelerometer/hardware#i2c-wiring-2-4
  * https://steve.fi/Hardware/nodemcu/default-pins/
  * https://github.com/adafruit/Adafruit_LIS3DH/tree/master/examples
  * https://forum.arduino.cc/index.php?PHPSESSID=3rt4hkdmh5h04eknvenmkp9771&topic=442570.msg3046667#msg3046667
* Adafruit IS31FL3731 LED Matrix Driver + 9x16 LED Matrix
  * https://www.exp-tech.de/module/led-controller/7005/adafruit-16x9-charlieplexed-pwm-led-matrix-driver-is31fl3731
  * https://www.exp-tech.de/displays/led/7006/adafruit-led-charlieplexed-matrix-9x16-leds-red
  * https://learn.adafruit.com/i31fl3731-16x9-charliplexed-pwm-led-driver/assembly
  * https://learn.adafruit.com/i31fl3731-16x9-charliplexed-pwm-led-driver/arduino-wiring-test
  * https://github.com/adafruit/Adafruit_IS31FL3731/tree/master/examples

## software

* Arduino IDE
```shell
brew cask install arduino
```

* driver for NodeMCU V2
```shell
brew tap homebrew/cask-drivers
brew cask install silicon-labs-vcp-driver
# follow manual steps
```
