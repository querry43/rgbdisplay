#pragma once

#include "widget.h"

namespace widget { namespace pulse {

class Pulse : public widget::Widget {
  public:
    virtual void update();
    virtual void delay();
    virtual void show();
    virtual ~Pulse() {}
};

} }
