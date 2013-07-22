CXXFLAGS += -I. -I.. -g -Wall -DTEST

ifndef WIDGET
$(error WIDGET env variable is missing)
endif

ifndef WIDGET_TYPE
$(error WIDGET_TYPE env variable is missing)
endif

widget_test: widget.h widget_main.o display.o utils.o Arduino.o $(WIDGET).o
	${CXX} ${CXXFLAGS} -o widget_test widget_main.o display.o utils.o Arduino.o $(WIDGET).o

$(WIDGET).o:
	${CXX} ${CXXFLAGS} -c -o $(WIDGET).o ../$(WIDGET).cpp

widget.h:
	echo "#include <$(WIDGET).h>" > widget.h
	echo "$(WIDGET_TYPE) widgetToTest;" >> widget.h

utils.o:
	${CXX} ${CXXFLAGS} -c -o utils.o ../utils.cpp

clean:
	rm -f *.o widget widget_test widget.h

all: widget_test

.PHONY: all clean widget.h

# vim: noet ts=8 tw=8
