#include "LPD8806.h"
#include "display.h"
#include "widget.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

DisplayWrapper display(0, 0, 0, 0);

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "USAGE: " << argv[0] << " <numCycles>" << endl;
        return 1;
    };

    int numCycles = strtol(argv[1], NULL, 0);

    cout << "running for " << numCycles << " cycles" << endl;

    cout << "widget.reset()" << endl; widgetToTest.reset();
    cout << "widget.show()" << endl; widgetToTest.show();
    for(int i = 0; i < numCycles; i++) {
        cout << "widget.delay()" << endl; widgetToTest.delay();
        cout << "widget.update()" << endl; widgetToTest.update();
        cout << "widget.show()" << endl; widgetToTest.show();
    }

    return 0;
}
