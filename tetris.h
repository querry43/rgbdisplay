#pragma once

#include "widget.h"

namespace widget { namespace tetris {

#define TETRIS_SPEED (1000ul * 60 * 5)

class Tetris : public widget::Widget {
  public:
    virtual void delay();
    virtual void show();
    virtual ~Tetris() {}
};

} }
