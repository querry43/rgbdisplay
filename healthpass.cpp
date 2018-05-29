#include <Arduino.h>

#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "healthpass.h"

extern DisplayWrapper display;

namespace widget { namespace healthpass {
  
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
  
  Pixel() : t(20), rising(true) {
    setTarget();
  }
  
  void update() {
    if (rising) {
      t++;
      if (t >= 100) rising = false;
    } else {
      t--;
      if (t <= 20) {
        rising = true;
        setTarget();
      }
    }
    
    color = display.scaleColor(target_color, t);
  }

  bool done() {
    return t == 20;
  }
};

Pixel p;
int offset[] = {0, 2};

void Healthpass::delay() { ::delay(50ul); }

void Healthpass::update() {
  if (p.done()) {
    display.clear();
    offset[0] = random(0, 3);
    offset[1] = random(2, 4);
  }
 
  display.setPixelColor(offset[0]+0, offset[1]+0, p.color);
  display.setPixelColor(offset[0]+1, offset[1]+1, p.color);
  display.setPixelColor(offset[0]+2, offset[1]+0, p.color);
  display.setPixelColor(offset[0]+3, offset[1]-1, p.color);
  p.update();
  display.show();
}

} }
