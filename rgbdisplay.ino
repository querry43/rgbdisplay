#include "LPD8806.h"
#include "SPI.h"
#include "display.h"

// settings for teensy 2.0
const int nLEDs = 32;
const int dataPin  = 22;
const int clockPin = 10;
const int powerPin = 11;
const int power = 20;

DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, powerPin, power);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.begin();
  display.show();
}

void loop() {
  tetris();
  delay(1000ul * 60 * 10);
}

// IIII  JJJ  OO  ZZ
//         J  OO   ZZ
//  SS  TTT  LLL
// SS    T   L

static const uint16_t tetris_grid_size = 9;
static const char* tetris_grid =
  "OOJJJZZIJ"
  "OOTTTZIIJ"
  "LLSTJJIJJ"
  "ILSSJJILO"
  "ILTSJJILO"
  "ITTTJJSLL"
  "IZJOOTSST"
  "ZZJOOTTSL"
  "ZJJISTOOL"
;

uint32_t tetris_grid_color(int x, int y) {
  uint32_t index = (x % tetris_grid_size) + (y * tetris_grid_size);

  static uint32_t tetriminos_colors[] = {
    display.Color(127, 0, 0),
    display.Color(127, 127, 127),
    display.Color(127, 0, 127),
    display.Color(0, 0, 127),
    display.Color(0, 127, 0),
    display.Color(127, 80, 80),
    display.Color(0, 127, 127)
  };
  
  switch(tetris_grid[index]) {
    case 'I': return tetriminos_colors[0];
    case 'J': return tetriminos_colors[1];
    case 'L': return tetriminos_colors[2];
    case 'O': return tetriminos_colors[3];
    case 'S': return tetriminos_colors[4];
    case 'T': return tetriminos_colors[5];
    case 'Z': return tetriminos_colors[6];
    default: die("unknown tile"); return 0;
  }
}

void tetris() {    
  uint16_t x_offset = random(tetris_grid_size - 6);
  uint16_t y_offset = random(tetris_grid_size - 6);
  
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 6; x++) {
      display.setPixelColor(x, y, tetris_grid_color(x + x_offset, y + y_offset));
    }
  }
  
  display.show();
}

void die(const char* message) {
  Serial.print("Died: ");
  Serial.println(message);
  for(;;);
}
