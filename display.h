#pragma once

class DisplayWrapper : public LPD8806 {
  protected:
    //LPD8806 * strip;
    static const uint16_t yx_to_index[6][6];
    
  public:
    DisplayWrapper(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t ppin) : LPD8806(n, dpin, cpin) {
      pinMode(ppin, OUTPUT);
      digitalWrite(ppin, HIGH);
    }
    
    void setPixelColor(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
      setPixelColor(x, y, Color(r, g, b));
    }
    
    void setPixelColor(uint16_t x, uint16_t y, uint32_t color) {
      LPD8806::setPixelColor(yx_to_index[y][x], color);
    }
    
    void clear() {
      fill(0, 0, 0);
    }
    
    void fill(uint16_t r, uint16_t g, uint16_t b) {
      fill(Color(r, g, b));
    }
    
    void fill(uint32_t color) {
      for (uint16_t i = 0; i < numPixels(); i++) LPD8806::setPixelColor(i, color);
    }
    
    uint32_t randomColor() {
      return Color(random(127), random(127), random(127));
    }
    
    void dumpColorToSerial(const char* name, uint32_t c) {
      Serial.print(name);
      Serial.print(" = ");
      dumpColorToSerial(c);
    }

    
    void dumpColorToSerial(uint32_t c) {
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
};

const uint16_t DisplayWrapper::yx_to_index[6][6] = {
  {-1,  0,  1,  2,  3, -1},
  { 4,  5,  6,  7,  8,  9},
  {10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21},
  {22, 23, 24, 25, 26, 27},
  {-1, 28, 29, 30, 31, -1}
};

