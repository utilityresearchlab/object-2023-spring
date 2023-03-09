/*
  DC Motor Analog Write Example
  Transistor connected to pin D6 (PWM)
*/

// LED Pin
const int MOTOR_TRANSISTOR_PIN = 6;

// Constants to help us map to min/max analog out values
const int ANALOG_OUT_MIN = 0;
const int ANALOG_OUT_MAX = 255;

const int SPEED_DELAY_MS = 2500;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set up the Transistor Pin for output, and turn it off
  pinMode(MOTOR_TRANSISTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_TRANSISTOR_PIN, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // Turn Motor on at 50% duty cycl, or half speed (PWM)
  analogWrite(MOTOR_TRANSISTOR_PIN, ANALOG_OUT_MAX/2);
  // Wait 2.5 seconds as the current speed
  delay(SPEED_DELAY_MS);

  // Turn Motor on at 100% duty cycl, or full speed (PWM)
  analogWrite(MOTOR_TRANSISTOR_PIN, ANALOG_OUT_MAX);
  // Wait 2.5 seconds as the current speed
  delay(SPEED_DELAY_MS);

  // Turn Motor off, 0% duty cycl, or 0% speed (PWM)
  analogWrite(MOTOR_TRANSISTOR_PIN, 0);
  delay(SPEED_DELAY_MS);
}
