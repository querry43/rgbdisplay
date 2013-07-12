#include <Arduino.h>

void die(const char* message) {
  Serial.print("Died: ");
  Serial.println(message);
  for(;;);
}

