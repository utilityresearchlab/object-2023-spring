// The input pin for the button
const int INPUT_PIN = 8;

// The time window for debouncing
const int DEBOUNCE_TIME_MS = 50;

// Stores the previous button state
int prevButtonState = LOW;

// The Set-up
void setup() {
  // Set Input Pin to input
  pinMode(INPUT_PIN, INPUT);

  // Initialize the Serial 
  Serial.begin(9600);
}

void loop() {
  // Grab the current button state
  int buttonState = digitalRead(INPUT_PIN);

  // Check if out current pin state has changed from the last state
  if (prevButtonState != buttonState) {
    // If so, we wait for a debouncing time period
    delay(DEBOUNCE_TIME_MS);
    int debouncedState = digitalRead(INPUT_PIN);

    // Did our switch state settle?
    if (buttonState == debouncedState) {
      // If so, we update our global button state and say what the 
      // new state is: 
      String pressedString = (buttonState) ? "Pressed" : "NOT Pressed!";
      Serial.println("The Button is now: " + pressedString);
      prevButtonState = buttonState;
    }
  }
}


