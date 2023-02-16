/*
  ReadAnalog-DigitalBlinkLED

  Reads an analog input on pin A0, 
  maps it to blinking rate from 0 - 5000 milliseconds, 
  prints the result to the Serial Monitor,
  and blinks at LED at the rate.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
  LED is attached to D10 with a 220 Ohm resistor to G
*/

const int POT_PIN = A0;
const int LED_PIN = 10;

// We want to constrain our possible LED value between 0 to 5000 milliseconds (5 seconds)
const int MIN_BLINK_MS = 10;
const int MAX_BLINK_MS = 2000;

// Current LED state's start time, starts at -1 since we have no time
int currentLEDStateStartTime = 0;

// State of the LED
bool isLEDOn = false;

// Current blink time
int blinkRateInMs = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set up Potentiometer pin for input
  pinMode(POT_PIN, INPUT);

  // Set up the LED for output, and turn it off
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize our current state, if we just started the arduino
  currentLEDStateStartTime = millis();
  isLEDOn = false;

}

// the loop routine runs over and over again forever:
void loop() {
  // Update our blinking rate based on the potentiometer
  updateBlinkTime();
  
  // Updates our LED's on/off state based on our blink time 
  updateLEDState();

  // Print out the blink rate to serial
  Serial.println(blinkRateInMs);

  // Serial.println("Min:0,Max:5000");
  // Slow down serial port processing (so data input in slower)
  delay(50);
}

// Handles updating our Blink Time in MS
void updateBlinkTime() {
  // Get current Pot value, returns value from 0 -> 1023
  int currentPotValue = analogRead(POT_PIN);
  // Map pot value (0->1023) to our blink rate (0 -> 5000) - using Arduino Library fxn called map
  blinkRateInMs = map(currentPotValue, 
                    0, 1023, 
                    MIN_BLINK_MS, MAX_BLINK_MS);
}

// Handles updating our LED state if necessary using millis() for timing
// Two possibilties, LED is on or it is off...
void updateLEDState() {
  int currentTime = millis();
  bool isTimeForStateChange = (currentLEDStateStartTime + blinkRateInMs) <= currentTime;
  if (isTimeForStateChange) {
    if (isLEDOn) {
        // LED is currently ON, we need to switch it to OFF
        digitalWrite(LED_PIN, LOW);
        // Now update the state to be off, and update our state time
        isLEDOn = false;
        currentLEDStateStartTime = millis();
      } else {
        // LED is currently OFF, so we need to switch it to ON
        digitalWrite(LED_PIN, HIGH);
        // Now update the state to be off, and update our state time
        isLEDOn = true;
        currentLEDStateStartTime = millis();
      }
  }
}

