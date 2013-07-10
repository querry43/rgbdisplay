#pragma once

class DisplayWrapper : public LPD8806 {
  protected:
    static const uint16_t yx_to_index[6][6];
    uint8_t power;
    
    uint32_t scaleColor(uint32_t c);
    
  public:
    DisplayWrapper(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t ppin, uint8_t p = 100);
    
    void setPower(uint8_t p);
    
    void setPixelColor(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t x, uint16_t y, uint32_t color);
    
    void clear();
    
    void fill(uint16_t r, uint16_t g, uint16_t b);
    void fill(uint32_t color);
    
    uint32_t randomColor();
    
    void dumpColorToSerial(const char* name, uint32_t c);
    void dumpColorToSerial(uint32_t c);
    

};
