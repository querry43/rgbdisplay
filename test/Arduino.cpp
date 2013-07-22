#include "Arduino.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void delay(int ms) { cout << "delay(" << ms << ")" << endl; }

int random(int max) { return rand() % max; }
int random(int min, int max) { return (rand() % (max-min)) + min; }

void pinMode(int pin, int mode) {
    cout << "pinMode(" << pin << "," << mode << ")" << endl;
}

void digitalWrite(int pin, int value)
{
    cout << "digitalWrite(" << pin << "," << value << ")" << endl;
}

void SerialClass::print(const char* s) {
    cout << "print(" << s << ")" << endl;;
}

void SerialClass::println(const char* s) {
    cout << "println(" << s << ")" << endl;;
}

void SerialClass::print(const byte b) { }

SerialClass Serial;
