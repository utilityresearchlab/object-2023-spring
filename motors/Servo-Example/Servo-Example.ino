/*
 Setting a Servo Position with Servo on pin D3 (PWM)
*/

#include <Servo.h>

const int SERVO_PIN = 3;

Servo servoA;  // create servo object to control a servo

 
void setup() {
  servoA.attach(SERVO_PIN);  // attaches the servo on SERVO_PIN to the servo object
}

void loop() {
  // Angle of servo can be any value 0 -> 180 degrees
  servoA.write(180); 
  delay(1000);  
  
  servoA.write(100);
  delay(1000);                           
    
  servoA.write(140);
  delay(1000);                           
 
  servoA.write(0); 
  delay(1000);                           
}
