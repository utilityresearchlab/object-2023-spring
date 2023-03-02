#include "pitches.h"


// Piezo Pin
const int PIEZO_PIN = 11;

void setup() {
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop() {
  // frequency (in hertz) and duration (in milliseconds).
  int frequencyHz = 100; // could aslo be any pitch from pitches.h

  // duration in milliseconds of the tone
  int durationMs = 90;

  // Two ways to use tone:
  // First plays a tone continuously (and indefinitely until you specify turning it off)
  tone(PIEZO_PIN, frequencyHz);
  // To turn off you use the "noTone(pin) function
  noTone(PIEZO_PIN);

  // Otherway is to specify a duration in the call to tone like so:
  tone(PIEZO_PIN, frequencyHz, durationMs);
  delay(100);
}
