/*
  AnalogWrite-FadeLED
  Fades an LED from 0 to 255 then 255 to 0 with a delay of 10 ms between each value change
  LED is attached to D3 with a 220 Ohm resistor to GND
*/

// LED Pin
const int LED_PIN = 3;

// Constants to help us map to min/max analog out values
const int ANALOG_OUT_MIN = 0;
const int ANALOG_OUT_MAX = 255;

const int LED_DELAY_MS = 5;

// LED Value
int brightnessValue = 0;

// Direction to light LED
bool isReversed = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set up the LED for output, and turn it off
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // Check if we need to flip the lighting direction
  if (brightnessValue >= ANALOG_OUT_MAX) {
    isReversed = true;
  } else if (brightnessValue <= ANALOG_OUT_MIN) {
    isReversed = false;
  }

  // Increment light value
  if (!isReversed) {
    brightnessValue += 1;
  } else {
    brightnessValue -= 1;
  }
  // Light LED
  analogWrite(LED_PIN, brightnessValue);

  // Print out the analog out value to serial
  Serial.println(brightnessValue);

  // Delay for a few ms
  delay(LED_DELAY_MS);
}
