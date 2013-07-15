#include <math.h>
#include "display.h"

// settings for teensy 2.0
const int nLEDs = 32;
const int dataPin  = 22;
const int clockPin = 10;
const int powerPin = 11;
const int power = 20;

#define GRID_SIZE 6

#define BALL_DELAY (100ul)

DisplayWrapper display = DisplayWrapper(nLEDs, dataPin, clockPin, powerPin, power);

struct color_t {
  double r, g, b;
};

const color_t black = { 0.0, 0.0, 0.0 };

struct ball_t {
  double x, y;
  double dx, dy;
  color_t color;
};

ball_t balls[] = {
  { 0.0, 0.0,  0.30,  0.20, { 1.0, 0.0, 0.0 } },
  { 2.0, 5.0,  0.37, -0.15, { 0.0, 1.0, 0.0 } },
  { 5.0, 2.0, -0.15,  0.37, { 0.0, 0.0, 1.0 } }
};
#define NUM_BALLS (sizeof(balls) / sizeof(balls[0]))

void move_through_dimension(double & xy, double & dxy) {
  xy += dxy;
  if (xy < 0) {
    xy = -xy;
    dxy = -dxy;
  }
  if (xy >= GRID_SIZE) {
    xy = GRID_SIZE - (xy - GRID_SIZE);
    dxy = -dxy;
  }
}

void move_balls() {
  for (int i = 0; i < NUM_BALLS; ++i) {
    ball_t & b = balls[i];
    move_through_dimension(b.x, b.dx);
    move_through_dimension(b.y, b.dy);
  }
}

void show_balls() {
  color_t colors[GRID_SIZE][GRID_SIZE];

  for (int x = 0; x < GRID_SIZE; ++x) {
    for (int y = 0; y < GRID_SIZE; ++y) {
      color_t c = black;

      for (int i = 0; i < NUM_BALLS; ++i) {
        ball_t & b = balls[i];
        double distance = pow(pow(b.x - x, 2) + pow(b.y - y, 2), 0.5);
        double f = 1.0 / (pow(distance, 2) + 1.0);

        c.r += b.color.r * f;
        c.g += b.color.g * f;
        c.b += b.color.b * f;
      }

      display.setPixelColor(x, y, int(c.r / NUM_BALLS * 255) + (int(c.g / NUM_BALLS * 255) << 8) + (int(c.b / NUM_BALLS * 255) << 16));
    }
  }
  display.show();
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.begin();
  display.show();
}

void loop() {
  move_balls();
  show_balls();
  delay(BALL_DELAY);
}
