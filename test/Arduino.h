#pragma once

#include <stdint.h>
#include <math.h>

#define OUTPUT 0
#define HIGH 0

typedef uint8_t byte;

void delay(int ms);
int random(int min);
int random(int min, int max);
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

class SerialClass {
public:
    void print(const char* s);
    void println(const char* s);
    void print(const byte b);
};

extern SerialClass Serial;
