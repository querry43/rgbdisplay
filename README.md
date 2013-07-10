rgb-display
===========

This software drives a 6x6 array of individually addressable RGB leds arranged in a circle as such:


    0,0                 5,0
        +------------------
        |    () () () ()
        | () () () () () ()
        | () () () () () ()
        | () () () () () ()
        | () () () () () ()
    0,5 |    () () () ()


The LEDs themselves are arranged in a strip and driven by LPD8806 chips, one for every two LEDs.

The micro controller is an Arduino compatible board called a [Teensy 2.0](http://www.pjrc.com/store/teensy.html).  This board comes with additional loader software and instructions for programming.

Requirements
------------
1. [Arduino](http://arduino.cc/en/Main/Software)
2. [Teensyduino](http://www.pjrc.com/teensy/td_download.html)
3. [LPD8806 Library](https://github.com/adafruit/LPD8806)