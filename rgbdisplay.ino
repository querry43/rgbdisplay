#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "tetris.h"
#include "bugs.h"
#include "balls.h"
#include "utils.h"


// settings for teensy 2.0
const int nLEDs = 32;
const int dataPin  = 22;
const int clockPin = 10;
const int powerPin = 11;
const int power = 20;

#define MILLIS_PER_WIDGET 1000ul * 60 * 30


DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, powerPin, power);
widget::tetris::Tetris tetris;
widget::balls::Balls balls;
widget::bugs::Bugs bugs;

const int numWidgets = 3;
widget::Widget * widgets[] = {
  &balls,
  &tetris,
  &bugs,
};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.begin();
  display.show();
}

void loop() {
  static unsigned long previousMillis;
  static int currentWidget = 0;

  previousMillis = millis();

  widgets[currentWidget]->reset();
  widgets[currentWidget]->show();
  while (millis() - previousMillis < MILLIS_PER_WIDGET) {
    widgets[currentWidget]->delay();
    widgets[currentWidget]->update();
    widgets[currentWidget]->show();
  }

  currentWidget = (currentWidget + 1) % numWidgets;
}
