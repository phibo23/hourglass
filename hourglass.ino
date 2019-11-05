#include <Adafruit_LIS3DH.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup() {
  Serial.begin(9600);
  delay(100);

  _initAccel();
}

void loop() {
}

/**
 * https://github.com/adafruit/Adafruit_LIS3DH/blob/master/examples/acceldemo/acceldemo.ino
 */
void _initAccel() {
  Serial.println("LIS3DH test!");
  while (!lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    yield();
  }
  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");
}
