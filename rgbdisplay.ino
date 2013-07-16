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

const long changePatternInterval = 1000 * 60 * 30;


#define BUG_SPEED (100ul * 5)
#define TETRIS_SPEED (1000ul * 60 * 10)

DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, powerPin, power);
Tetris tetris;
environment_t bugs;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.begin();
  display.show();
}

void loop() {
  static long previousMillis;

  previousMillis = millis();

  while (millis() - previousMillis < changePatternInterval) {
    tetris.drawRandomTetrisGrid();
    delay(TETRIS_SPEED);
  }

  previousMillis = millis();

  while (millis() - previousMillis < changePatternInterval) {
    bugs.advance();
    bugs.show();
    delay(BUG_SPEED);
  }
}
