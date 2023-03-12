/*
 * Reads the distance from an  HC-SR04 ultrasonic distance sensor
 * using the HCSR04 library by Martinsos installed via the Libraries menu in 
 * the Arduino IDE. See details of the library here: 
 * https://github.com/Martinsos/arduino-lib-hc-sr04
 * The Trigger is on pin 4 and the echo is on pin 3
 * The default ambient temperature is set to 20C.
*/

#include <HCSR04.h>

// Pin Set-up for the HC-SR04 Sensor
const byte TRIGGER_PIN = 4;
const byte ECHO_PIN = 3;

// Initialize Sensor
UltraSonicDistanceSensor distanceSensor = UltraSonicDistanceSensor(TRIGGER_PIN,ECHO_PIN);

// Assume we have a ambient room temperature of 20 degree C 
const float DEFAULT_AMBIENT_TEMPERATURE_C = 20;

void setup () {
  Serial.begin(9600);
}

void loop () { 
  double distance = distanceSensor.measureDistanceCm(DEFAULT_AMBIENT_TEMPERATURE_C);
  
  Serial.print(distance);
  Serial.println(" cm");
  delay(250);
}