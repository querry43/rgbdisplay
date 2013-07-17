#pragma once

#include "widget.h"

namespace widget { namespace bugs {
  
#define BUG_SPEED (100ul * 5)
#define PCT_TIME_BUG_MOVES_SAME_DIRECTION 80
#define SATIATION_PROVIDED_BY_PLANT 10
#define GRID_SIZE 6
#define MAX_BUGS (GRID_SIZE * GRID_SIZE)
#define PCT_TIME_NEW_VEGETATION 18
#define BUG_REPRODUCE_AT_SATIATION 32

class Bugs : public widget::Widget {
  public:
    virtual void update();
    virtual void delay();
    virtual void show();
    virtual ~Bugs() {}
};

} }

