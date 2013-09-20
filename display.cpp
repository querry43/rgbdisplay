#include <Arduino.h>

#include "LPD8806.h"
#include "SPI.h"
#include "display.h"

const uint16_t yx_to_index[6][6] = {
  {-1,  0,  1,  2,  3, -1},
  { 4,  5,  6,  7,  8,  9},
  {10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21},
  {22, 23, 24, 25, 26, 27},
  {-1, 28, 29, 30, 31, -1}
};

DisplayWrapper::DisplayWrapper(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t ppin, uint8_t p) : LPD8806(n, dpin, cpin) {
  pinMode(ppin, OUTPUT);
  digitalWrite(ppin, HIGH);
  setPower(p);
}

void DisplayWrapper::clear() {
  fill(0, 0, 0);
}

uint32_t DisplayWrapper::randomColor() {
  uint8_t r, g, b;
  randomColor(r, g, b);
  return Color(r, g, b);
}

void DisplayWrapper::randomColor(uint8_t& r, uint8_t& g, uint8_t& b) {
  r = random(127);
  g = random(127);
  b = random(127);
}

void DisplayWrapper::dumpColorToSerial(const char* name, uint32_t c) {
  Serial.print(name);
  Serial.print(" = ");
  dumpColorToSerial(c);
}

void DisplayWrapper::dumpColorToSerial(uint32_t c) {
  byte green = (c & 0x7F0000) >> 16;
  byte red   = (c & 0x007F00) >> 8;
  byte blue  = c & 0x00007F;
  
  Serial.print("(");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.println(")");
}

uint32_t DisplayWrapper::scaleColor(uint32_t c) {
  return scaleColor(c, power);
}

uint32_t DisplayWrapper::scaleColor(uint32_t c, uint8_t t) {
  byte green = (c & 0x7F0000) >> 16; // this logic should be a macro
  byte red   = (c & 0x007F00) >> 8;
  byte blue  = c & 0x00007F;
  
  return Color(red * t / 100, green * t / 100, blue * t / 100);
}

void DisplayWrapper::setPower(uint8_t p) {
  if (p <= 100)
    power = p;
}

void DisplayWrapper::setPixelColor(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
  setPixelColor(x, y, Color(r, g, b));
}

void DisplayWrapper::setPixelColor(uint16_t x, uint16_t y, uint32_t color) {
  LPD8806::setPixelColor(yx_to_index[y][x], scaleColor(color));
}

void DisplayWrapper::fill(uint16_t r, uint16_t g, uint16_t b) {
  fill(Color(r, g, b));
}

void DisplayWrapper::fill(uint32_t color) {
  for (uint16_t i = 0; i < numPixels(); i++) LPD8806::setPixelColor(i, scaleColor(color));
}

