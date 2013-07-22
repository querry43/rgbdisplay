#pragma once

#include <Arduino.h>
#include <vector>

typedef uint32_t color_t;

struct color_tuple {
    int r, g, b;
    color_tuple();
    color_tuple(uint8_t r, uint8_t g, uint8_t b);
    color_tuple(uint32_t c);
    void show();
};


class DisplayWrapper {
  public:
    std::vector<std::vector<color_tuple> > displayValues;
    DisplayWrapper();
    DisplayWrapper(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t ppin, uint8_t p = 100);

    void setPower(uint8_t p);

    void setPixelColor(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t x, uint16_t y, color_t color);

    void clear();

    void fill(uint16_t r, uint16_t g, uint16_t b);
    void fill(color_t color);

    color_t randomColor();

    void dumpColorToSerial(const char* name, color_t c);
    void dumpColorToSerial(color_t c);

    void show();

    uint32_t Color(byte r, byte g, byte b);
    int numPixels() { return 32; }
};
