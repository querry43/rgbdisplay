#pragma once

#include "widget.h"

namespace widget { namespace pulse {

// Each pixel gets a random color and offset.  It ramps up to
// the target color and then dims back to black before chosing
// a new random target color and repeating.

class Pulse : public widget::Widget {
  public:
    virtual void update();
    virtual void delay();
    virtual ~Pulse() {}
};

} }
