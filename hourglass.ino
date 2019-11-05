#include <Adafruit_LIS3DH.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
#define FLAT_UP 0
#define FLAT_DOWN 1
#define PORTRAIT_UP 2
#define PORTRAIT_DOWN 3
#define LANDSCAPE_LEFT 4
#define LANDSCAPE_RIGHT 5

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();

void setup() {
  Serial.begin(9600);
  delay(100);

  _initAccel();
  _initLed();
}

void loop() {
  _getOrientation();
  delay(100);
}

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

int _getOrientation() {
  sensors_event_t event;
  lis.getEvent(&event);

  float x, y, z;
  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;

  if (z > 9) {
    return FLAT_UP;
  } else if (z < -9) {
    return FLAT_DOWN;
  } else if (x < -9) {
    return LANDSCAPE_LEFT;
  } else if (x > 9) {
    return LANDSCAPE_RIGHT;
  } else if (y < -9) {
    return PORTRAIT_UP;
  } else if (y > 9) {
    return PORTRAIT_DOWN;
  }
  return -1;
}

void _initLed() {
  Serial.println("IS31 test");
  while (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    yield();
  }
  Serial.println("IS31 found!");
}
