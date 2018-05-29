#pragma once

namespace widget {

class Widget {
  public:
    virtual void reset() { }
    virtual void update() = 0;
    virtual void delay() = 0;
    virtual ~Widget() {}
};

}

