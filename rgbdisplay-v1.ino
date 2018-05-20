#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "balls.h"
#include "pulse.h"
#include "comscore.h"
#include "utils.h"


// settings for teensy 2.0
const int nLEDs = 32;
const int dataPin  = 10;
const int clockPin = 9;
const int power = 50;

#define MILLIS_PER_WIDGET 1000ul * 60 * 30


DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, power);
widget::balls::Balls balls;
widget::pulse::Pulse pulse;

const int numWidgets = 2;
widget::Widget * widgets[] = {
  &pulse,
  &balls,
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