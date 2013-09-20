#include <Arduino.h>

#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "pulse.h"
#include "utils.h"

extern DisplayWrapper display;

namespace widget { namespace pulse {
  
class Pixel {
protected:
  color_t target_color;
  uint8_t t;

  void setTarget() {
    target_color = display.randomColor();
  }
public:
  color_t color;
  bool rising;
  
  Pixel() : t(random(100)), rising(true) {
    setTarget();
  }
  
  void update() {
    if (rising) {
      t++;
      if (t >= 100) rising = false;
    } else {
      t--;
      if (t <= 0) {
        rising = true;
        setTarget();
      }
    }
    
    color = display.scaleColor(target_color, t);
  }
};

Pixel p[6][6];

void Pulse::delay() { ::delay(50ul); }

void Pulse::update() {
  for (unsigned int x = 0; x < 6; x++) {
    for (unsigned int y = 0; y < 6; y++) {
      p[x][y].update();
    }
  }
}


void Pulse::show() {
  uint8_t r, g, b;
  display.randomColor(r, g, b);
  
  for (unsigned int x = 0; x < 6; x++) {
    for (unsigned int y = 0; y < 6; y++) {
      display.setPixelColor(x, y, p[x][y].color);
      p[x][y].update();
    }
  }

  display.show();
}

} }
