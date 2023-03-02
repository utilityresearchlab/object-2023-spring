#include "pitches.h"


// Piezo Pin
const int PIEZO_PIN = 11;

void setup() {
  // do nothing for pwm pins
}

void loop() {
  // frequency (in hertz) and duration (in milliseconds).
  int frequencyHz = 100; // could be any pitch from pitches.h
  int durationMs = 90;
  tone(PIEZO_PIN, frequencyHz, durationMs);
  delay(100);
}
