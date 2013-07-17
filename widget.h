#pragma once

namespace widget {

class Widget {
  public:
    virtual void reset() { }
    virtual void update() { }
    virtual void delay() = 0;
    virtual void show() = 0;
    virtual ~Widget() {}
};

}

