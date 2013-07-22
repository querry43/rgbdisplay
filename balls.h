#pragma once

#include "widget.h"

namespace widget { namespace balls {

#define BALL_DELAY (50ul)

class Balls : public widget::Widget {
  public:
    virtual void reset();
    virtual void update();
    virtual void delay();
    virtual void show();
    virtual ~Balls() {}
};

} }
