#!/bin/bash

widget=balls
widget_type=widget::balls::Balls
num_cycles=3

make WIDGET=$widget WIDGET_TYPE=$widget_type
./widget_test $num_cycles &> widget.log

#run some gui command on widget.log
