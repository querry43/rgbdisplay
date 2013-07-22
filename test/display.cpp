#include "display.h"

#include <vector>
#include <iostream>

using namespace std;

color_tuple::color_tuple() : r(0), g(0), b(0) { }
color_tuple::color_tuple(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) { }
color_tuple::color_tuple(uint32_t c) {
    g = (c & 0x7F0000) >> 16;
    r = (c & 0x007F00) >> 8;
    b = c & 0x00007F;
}
void color_tuple::show() { cout << "(" << r << "," << g << "," << b << ")"; }

DisplayWrapper::DisplayWrapper() { }
DisplayWrapper::DisplayWrapper(uint16_t n, uint8_t dpin, uint8_t cpin, uint8_t ppin, uint8_t p) { }

void DisplayWrapper::setPower(uint8_t p) { }

void DisplayWrapper::setPixelColor(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
    setPixelColor(x, y, Color(r, g, b));

    color_tuple c = color_tuple(r, g, b);
    cout << "display.setPixelColor(" << x << "," << y << ",";
    c.show();
    cout << ")" << endl;
    displayValues[x][y] = c;
}

void DisplayWrapper::setPixelColor(uint16_t x, uint16_t y, color_t color) {
    color_tuple c = color_tuple(color);
    cout << "display.setPixelColor(" << x << "," << y << ",";
    c.show();
    cout << ")" << endl;
    displayValues[x][y] = c;
}

void DisplayWrapper::clear() {
    displayValues.clear();

    for (int x = 0; x < 6; x++) {
        vector<color_tuple> v;
        for (int y = 0; y < 6; y++)
            v.push_back(color_tuple());
        displayValues.push_back(v);
    }
}

void DisplayWrapper::fill(uint16_t r, uint16_t g, uint16_t b) {
    fill(Color(r, g, b));
}

void DisplayWrapper::fill(color_t color) {
    color_tuple c = color_tuple(c);
    cout << color << " fill(";
    c.show();
    cout << ")" << endl;

    for (int x = 0; x < 6; x++)
        for (int y = 0; y < 6; y++)
            displayValues.at(x).at(y) = c;
}

color_t DisplayWrapper::randomColor() {
    return Color(random(0, 127), random(0, 127), random(0, 127));
}

void DisplayWrapper::dumpColorToSerial(const char* name, color_t c) { }
void DisplayWrapper::dumpColorToSerial(color_t c) { }

void DisplayWrapper::show() {
    cout << "display.show()" << endl;
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 6; x++) {
            displayValues[x][y].show();
        }
        cout << endl;
    }
}

uint32_t DisplayWrapper::Color(byte r, byte g, byte b) {
    return ((uint32_t)(g | 0x80) << 16) |
           ((uint32_t)(r | 0x80) <<  8) |
                       b | 0x80 ;
}
