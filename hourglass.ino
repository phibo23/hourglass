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

#include <math.h>

long startmillis;
long duration = 1000 * 10;

void setup() {
  Serial.begin(9600);
  delay(100);

  _initAccel();
  _initLed();

  startmillis = millis();
}

void loop() {
  _getOrientation();

  ledmatrix.setRotation(1);
  ledmatrix.clear();

  _drawHourglassShape();

  float progress = (float) (millis() - startmillis) / duration;
  if (progress > 1.0) {
    progress = 1;
  }
  _drawSand(progress);
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


void _drawHourglassShape() {
  #define shapeBrightness 72
  ledmatrix.drawFastHLine(0, 0, 9, shapeBrightness);
  ledmatrix.drawFastVLine(0, 0, 3, shapeBrightness);
  ledmatrix.drawFastVLine(8, 0, 3, shapeBrightness);
  ledmatrix.drawLine(0, 3, 4, 7, shapeBrightness);
  ledmatrix.drawLine(8, 3, 4, 7, shapeBrightness);
  ledmatrix.drawLine(0, 12, 4, 8, shapeBrightness);
  ledmatrix.drawLine(8, 12, 4, 8, shapeBrightness);
  ledmatrix.drawFastVLine(0, 13, 3, shapeBrightness);
  ledmatrix.drawFastVLine(8, 13, 3, shapeBrightness);
  ledmatrix.drawFastHLine(0, 15, 9, shapeBrightness);
}

void _drawSand(float progress) {
  #define sandBrightness 32
  #define EULER 2.718281828459045235360287471352
  if (progress < 1) {
    // upper
    // triangle flows through neck -> exponentially decrease height
    int upperTop = 3 + 4 * pow(EULER, 3 * progress - 3);
    int upperLeft = upperTop / 2;
    int upperRight = 8 - upperTop / 2;
    ledmatrix.fillTriangle(upperLeft, upperTop, upperRight, upperTop, 4, 7, sandBrightness);
    // lower
    // triangle grows -> logarithmic increase height 
    int lowerTop = 15 - 4 * ((1.0/2.0) * log(progress) + 1);
    int lowerBottom = lowerTop + 4;
    ledmatrix.fillTriangle(0, lowerBottom, 8, lowerBottom, 4, lowerTop, sandBrightness);
    // stream
    ledmatrix.drawLine(4, 8, 4, 15, sandBrightness);

  } else {
    ledmatrix.fillTriangle(0, 15, 8, 15, 4, 11, sandBrightness);
  }
}
