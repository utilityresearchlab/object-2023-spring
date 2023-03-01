// This sketch uses a 5 LEDS, a potentiometer and a button and demonstrates
// controlling the brightness of each LED. The pot changes the brightness 
// of the currently selected LED; the button rotates the currently selected LED
// The brightness state of each led is stored globally and set using PWM pins

// Analog input for the pot pin
const int POT_PIN = A0;

// Digital input for the button pin
const int BUTTON_PIN = 2;

// All led pins are on PWM pins (~)
const int LED_PINS[] = {3, 5, 6, 9, 10};

// Calculate the number of led pins we have.
const int LED_PIN_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

// We use another array to store the STATE of all the leds.
// In our case this is a int between 0, 255 (since this is the resolution that /// our arduino can output). We initially have all set to 0 (OFF)
// note this is not declared `const` (constant) because we need 
// to change the values in the array
int ledStates[] = {0, 0, 0, 0, 0};

// Stores the LED index that we are currently focused on for adjusting the brightness. This is between (0, LED_PIN_COUNT - 1)
// We will update this when a button is pressed.
int currentLEDIndex = 0; 
       
// Acutal Analog Input Max/Min reading for our arduino 
const int ANALOG_INPUT_MIN = 0;
const int ANALOG_INPUT_MAX = 1023;


// Acutal Analog Output Max/Min reading for our arduino 
const int ANALOG_OUTPUT_MIN = 0;
const int ANALOG_OUTPUT_MAX = 255;


// Calibration: our potentiometers aren't super great at the ends of the range 
// so if we print the min/max values to serial output we see can see that 
// they don't reach the min of 0 and max of 1023 that our arduino can actually
// detect.  We can give ourselves a new range, by measuring/printing what that min/max is and use [min, max] as our range. 
// const int POT_INPUT_MAX = 1000;
// const int POT_INPUT_MIN = 10;


// Alternatively, we could use an fixed error boundary at the ends of the range
// so that we map in the range [MIN_INPUT + ERROR, MAX_INPUT - ERROR];
// Rather than using (0, 1023) as our range, 
// We can set an error of 40, and map from (40, 983)
const int POT_ERROR = 40;
const int POT_INPUT_MIN = ANALOG_INPUT_MIN + POT_ERROR;
const int POT_INPUT_MAX = ANALOG_INPUT_MAX - POT_ERROR;


void setup() {
  // Set pot pin as inpuit
  pinMode(POT_PIN, INPUT);
  // Set initial led states to be off
  for (int i = 0; i < LED_PIN_COUNT; i++) {
    const int ledPin = LED_PINS[i];
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  }
  // Start Serial
  Serial.begin(9600);
}

void loop() {
  updateCurrentlySelectedLED();
  updateBrightnessValue();
  updateLEDStates();  
}

void updateLEDStates() {
  for (int i = 0; i < LED_PIN_COUNT; i++) {
    const int ledPin = LED_PINS[i];
    const int ledState = ledStates[i];
    analogWrite(ledPin, ledState);
  }
}

void updateBrightnessValue() {
  int potInput = analogRead(POT_PIN);
  potInput = constrain(potInput, POT_INPUT_MIN, POT_INPUT_MAX);
  int mappedOutValue = map(
    potInput, 
    POT_INPUT_MIN, 
    POT_INPUT_MAX, 
    ANALOG_OUTPUT_MIN, 
    ANALOG_OUTPUT_MAX);

  // Update value for currently selected led
  ledStates[currentLEDIndex] = mappedOutValue;
  // Print out value
  Serial.println(mappedOutValue);
}

void updateCurrentlySelectedLED() {
  bool buttonWasPressed = checkForButtonPress();
  if (buttonWasPressed) {
    // Increment our index
    currentLEDIndex += 1;
    if (currentLEDIndex > LED_PIN_COUNT - 1) {
      // Wrap the index back to zero
      currentLEDIndex = 0;
    }
  }
}

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the 
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

// Debounces the button and returns true if the button was pressed
bool checkForButtonPress() {
  bool wasButtonPressed = false;
   // read the state of the switch into a local variable:
  int reading = digitalRead(BUTTON_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        wasButtonPressed = true;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  return wasButtonPressed;
}
