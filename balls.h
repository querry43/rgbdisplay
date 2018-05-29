#pragma once

#include "widget.h"

namespace widget { namespace balls {

#define BALL_DELAY (50ul)

// Simulate multiple balls moving in 2-d space.
// Written by Aaron Harsh.  Thanks Aaron!

class Balls : public widget::Widget {
  public:
    virtual void update();
    virtual void delay();
    virtual ~Balls() {}
};

} }
