#pragma once

#include <Arduino.h>
#include "display.h"

#define PCT_TIME_BUG_MOVES_SAME_DIRECTION 80
#define SATIATION_PROVIDED_BY_PLANT 10
#define GRID_SIZE 6
#define MAX_BUGS (GRID_SIZE * GRID_SIZE)
#define PCT_TIME_NEW_VEGETATION 18
#define BUG_REPRODUCE_AT_SATIATION 32

extern DisplayWrapper display;

struct bug_t {
  int x, y;
  int dx, dy;
  int satiation;

  void randomize_direction();

  void move();

  void eat();

  bool is_alive();

  uint32_t color();

  bug_t reproduce();
};


struct environment_t {
  int num_bugs;
  bug_t bugs[MAX_BUGS];
  bool vegetation[GRID_SIZE][GRID_SIZE];

  environment_t();

  void add_initial_bug();

  void add_bug(bug_t b);

  void add_bug(int x, int y, int s);

  void add_random_vegetation();

  void advance();
  void show();
};


