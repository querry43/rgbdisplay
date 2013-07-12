#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "tetris.h"
#include "utils.h"


// settings for teensy 2.0
const int nLEDs = 32;
const int dataPin  = 22;
const int clockPin = 10;
const int powerPin = 11;
const int power = 20;

DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, powerPin, power);
Tetris tetris = Tetris();

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.begin();
  display.show();
}

void loop() {
  tetris.drawRandomTetrisGrid();
  delay(1000ul * 60 * 10);
}
