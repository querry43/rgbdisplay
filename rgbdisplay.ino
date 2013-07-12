#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "tetris.h"
#include "bug.h"
#include "utils.h"


// settings for teensy 2.0
const int nLEDs = 32;
const int dataPin  = 22;
const int clockPin = 10;
const int powerPin = 11;
const int power = 20;

#define BUG_SPEED (100ul * 5)
#define TETRIS_SPEED (1000ul * 60 * 10)

DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, powerPin, power);
Tetris tetris;
environment_t environment;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.begin();
  display.show();
}

long previousMillis = 0;
const long interval = 1000 * 60 * 30;

void loop() {
  while (millis() - previousMillis < interval) {
    tetris.drawRandomTetrisGrid();
    delay(TETRIS_SPEED);
  }

  previousMillis = millis();

  while (millis() - previousMillis < interval) {
    environment.advance();
    environment.show();
    delay(BUG_SPEED);
  }

  previousMillis = millis();
}
