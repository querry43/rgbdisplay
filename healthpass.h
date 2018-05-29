#pragma once

#include "widget.h"

namespace widget { namespace healthpass {

class Healthpass : public widget::Widget {
  public:
    virtual void update();
    virtual void delay();
    virtual ~Healthpass() {}
};

} }
