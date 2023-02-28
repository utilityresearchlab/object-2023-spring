/*
  AnalogRead-AnalogWriteLED

  Reads an analog input from 0 to 1023 on pin A0, 
  maps it to analog output from 0 to 255
  prints the result to the Serial Monitor,
  and lights the LED at the respective 
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
  LED is attached to D3 with a 220 Ohm resistor to GND
*/

const int POT_PIN = A0;
const int LED_PIN = 3;

// Constants to help us map to min/max analog out values
const int ANALOG_OUT_MIN = 0;
const int ANALOG_OUT_MAX = 255;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set up Potentiometer pin for input
  pinMode(POT_PIN, INPUT);

  // Set up the LED for output, and turn it off
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 0);
}

// the loop routine runs over and over again forever:
void loop() {
   // Get current Pot value, returns value from 0 -> 1023
  int currentPotValue = analogRead(POT_PIN);
  // Map pot value (0->1023) to our blink rate (0 -> 255) - using Arduino Library fxn called map
  int analogOutValue = map(currentPotValue, 
    0, 1023, 
    ANALOG_OUT_MIN, ANALOG_OUT_MAX);
  
  analogWrite(LED_PIN, analogOutValue);

  // Print out the analog out value to serial
  Serial.println(analogOutValue);
  // Fix the serial monitor range
  // Serial.println("Min:0,Max:255");
}
