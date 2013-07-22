#include <Arduino.h>

#include "LPD8806.h"
#include "SPI.h"
#ifdef TEST
#include <display.h>
#else
#include "display.h"
#endif
#include "tetris.h"
#include "utils.h"

extern DisplayWrapper display;

namespace widget { namespace tetris {

// IIII  JJJ  OO  ZZ
//         J  OO   ZZ
//  SS  TTT  LLL
// SS    T   L

const uint16_t tetris_grid_size = 15;
const char* tetris_grid =
  "ILLIJOOLZZLLLTT"
  "OJLJJOOLZOOZZTS"
  "OJLTTTSSJOOTZZL"
  "JJSSTSSZJJJTTJJ"
  "TSSJJJZZLLLTSLL"
  "ZZLLSJZTLIZZSSL"
  "SZZLSSTTTISZZSL"
  "SOOLTSOOLISSOOJ"
  "TOOTTTOOLIJSOOJ"
  "ZJIIIISSLLJJJIJ"
  "ZJLOOSSJIIIITIT"
  "JJLOOLLJJJSTTIJ"
  "OOLLZJLTTTSSTIJ"
  "OOTZZJLSTOOSZLL"
  "ZTTZJJZSSOOZZOO"
;

uint32_t tetris_grid_color(int x, int y) {
  uint32_t index = (x % tetris_grid_size) + (y * tetris_grid_size);
 
  static uint32_t tetriminos_colors[] = {
    display.Color(127, 0, 0),
    display.Color(127, 127, 127),
    display.Color(127, 0, 127),
    display.Color(0, 0, 127),
    display.Color(0, 127, 0),
    display.Color(127, 127, 0),
    display.Color(0, 127, 40)
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

void Tetris::show() {
  uint16_t x_offset = random(tetris_grid_size - 6);
  uint16_t y_offset = random(tetris_grid_size - 6);
  
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 6; x++) {
      display.setPixelColor(x, y, tetris_grid_color(x + x_offset, y + y_offset));
    }
  }
  
  display.show();
}

void Tetris::delay() { ::delay(TETRIS_SPEED); }

void Tetris::reset() { display.clear(); }

} }

