#pragma once

#include "widget.h"

namespace widget { namespace comscore {

class Comscore : public widget::Widget {
  public:
    virtual void update();
    virtual void delay();
    virtual void show();
    virtual ~Comscore() {}
};

} }
