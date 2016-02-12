#include <Arduino.h>

#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "comscore.h"
#include "utils.h"

extern DisplayWrapper display;

namespace widget { namespace comscore {

const color_t orange = display.Color(100, 40, 0);
const color_t blue = display.Color(8, 50, 87);

color_t c1 = orange, c2 = blue;
  
void Comscore::delay() { ::delay(25ul); }

bool draw_big = true;
uint8_t i = 0;
bool getting_brighter = true;

void big() {
  color_t scaled_c2 = display.scaleColor(c2, i);
  color_t scaled_c1 = display.scaleColor(c1, i);

  for (uint8_t i = 2; i < 6; i++) {
    display.setPixelColor(i, 0, scaled_c2);
    display.setPixelColor(i, 3, scaled_c2);
  }
  display.setPixelColor(2, 1, scaled_c2);
  display.setPixelColor(5, 1, scaled_c2);
  display.setPixelColor(5, 2, scaled_c2);

  for (uint8_t i = 0; i < 4; i++) {
    display.setPixelColor(i, 2, scaled_c1);
    display.setPixelColor(i, 5, scaled_c1);
  }
  display.setPixelColor(3, 4, scaled_c1);
  display.setPixelColor(0, 3, scaled_c1);
  display.setPixelColor(0, 4, scaled_c1);
}

void small() {
  color_t scaled_c2 = display.scaleColor(c2, i);
  color_t scaled_c1 = display.scaleColor(c1, i);

  for (uint8_t i = 2; i < 6; i++) {
    display.setPixelColor(i, 1, scaled_c2);
    display.setPixelColor(i, 3, scaled_c2);
  }
  display.setPixelColor(5, 2, scaled_c2);

  for (uint8_t i = 0; i < 4; i++) {
    display.setPixelColor(i, 2, scaled_c1);
    display.setPixelColor(i, 4, scaled_c1);
  }
  display.setPixelColor(0, 3, scaled_c1);
}

void changeColor() {
  if  (random(10) == 0) {
    c1 = orange;
    c2 = blue;
  } else {
    c1 = display.randomColor();
    c2 = display.randomColor();
  }
}

void Comscore::update() {
  if (getting_brighter) {
    i++;
    if (i > 95)
      getting_brighter = false;
  } else {
    i--;
    if (i < 5) {
      getting_brighter = true;
      draw_big = !draw_big;
      changeColor();
    }
  }
}

void Comscore::show() {
  display.clear();
  if (draw_big)
    big();
  else
    small();
  display.show();
}

} }
