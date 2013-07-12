#pragma once

#include <Arduino.h>

typedef uint32_t color_t;

class DisplayWrapper : public LPD8806 {
  protected:
    uint8_t power;
    uint32_t scaleColor(color_t c);
    
  public:
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
};
