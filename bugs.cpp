#include <Arduino.h>

#include "LPD8806.h"
#include "SPI.h"
#include "display.h"
#include "bugs.h"
#include "utils.h"

extern DisplayWrapper display;

namespace widget { namespace bugs {

struct bug_t {
  int x, y;
  int dx, dy;
  int satiation;

  void randomize_direction()
  {
    dx = random(3) - 1;
    dy = random(3) - 1;
  }

  void move()
  {
    if (random(100) >= PCT_TIME_BUG_MOVES_SAME_DIRECTION)
      randomize_direction();
  
    x += dx;
    y += dy;
  
    if (x >= GRID_SIZE) { x = GRID_SIZE - 1; dx = -1; }
    if (y >= GRID_SIZE) { y = GRID_SIZE - 1; dy = -1; }
  
    if (x < 0) { x = 0; dx = 1; }
    if (y < 0) { y = 0; dy = 1; }
  
    --satiation;
  }


  void eat()
  {
    satiation += SATIATION_PROVIDED_BY_PLANT;
  }

  bool is_alive()
  {
    return satiation > 0;
  }

  uint32_t color()
  {
    uint32_t brightness = 8 * satiation;
    if (brightness > 255)
      brightness = 255;
  
    return display.Color(brightness, 0, 0);
  }

  bug_t reproduce()
  {
    satiation /= 2;
    bug_t child = *this;
    child.randomize_direction();
    return child;
  }
};


struct environment_t {
  int num_bugs;
  bug_t bugs[MAX_BUGS];
  bool vegetation[GRID_SIZE][GRID_SIZE];

  environment_t() : num_bugs(0)
  {
    add_initial_bug();
    for (int i = 0; i < 10; ++i)
      add_random_vegetation();
  }

  void add_initial_bug()
  {
    add_bug(3, 3, 30);
  }


  void add_bug(bug_t b)
  {
    bugs[num_bugs++] = b;
  }

  void add_bug(int x, int y, int s)
  {
    bug_t b;
    b.x = x;
    b.y = y;
    b.satiation = s;
    b.randomize_direction();
  
    add_bug(b);
  }

  void add_random_vegetation()
  {
    vegetation[random(GRID_SIZE)][random(GRID_SIZE)] = true;
  }

  void advance()
  {
    for (int i = 0; i < num_bugs; ++i) {
      bug_t & bug = bugs[i];
      bug.move();
      if (vegetation[bug.x][bug.y]) {
        vegetation[bug.x][bug.y] = false;
        bug.eat();
        if (bug.satiation >= BUG_REPRODUCE_AT_SATIATION) {
          add_bug(bug.reproduce());
        }
      }
    }
  
    for (int i = 0; i < num_bugs; ++i) {
      bug_t & bug = bugs[i];
      if (! bug.is_alive()) {
        bugs[i] = bugs[--num_bugs];
        i = 0;
      }
    }
  
    if (num_bugs == 0)
      add_initial_bug();
  
    if (random(100) <= PCT_TIME_NEW_VEGETATION)
      add_random_vegetation();
  }

  void show()
  {
    uint32_t vegetation_color = display.Color(0, 63, 0);
    uint32_t background_color = display.Color(0, 0, 0);
  
    for (int y = 0; y < GRID_SIZE; ++y) {
      for (int x = 0; x < GRID_SIZE; ++x) {
        uint32_t color = vegetation[x][y] ? vegetation_color : background_color;
        for (int b = 0; b < num_bugs; ++b) {
          bug_t & bug = bugs[b];
  
          if (bug.x == x && bug.y == y)
            color = bug.color();
        }
  
        display.setPixelColor(x, y, color);
      }
    }
    display.show();
  }
};


environment_t environment;

void Bugs::update() { environment.advance(); }
void Bugs::delay() { ::delay(BUG_SPEED); }
void Bugs::show() { environment.show(); }


} }
