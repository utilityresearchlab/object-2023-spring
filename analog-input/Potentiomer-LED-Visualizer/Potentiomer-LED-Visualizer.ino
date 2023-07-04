

const int POT_PIN = A0;
const int LED_PINS[] = {3, 5, 6, 9, 10};
const int LED_PIN_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

       
// Acutal Analog Input Max/Min reading for our arduino 
const int ANALOG_INPUT_MAX = 1023;
const int ANALOG_INPUT_MIN = 0;

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
const int POT_INPUT_MAX = ANALOG_INPUT_MAX - POT_ERROR;
const int POT_INPUT_MIN = ANALOG_INPUT_MIN + POT_ERROR;


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
  int potInput = analogRead(POT_PIN);
  int mappedValue = map(
    potInput, 
    POT_INPUT_MIN, 
    POT_INPUT_MAX, 
    0, 
    LED_PIN_COUNT);

  // Print pot input value to serial
  Serial.println(potInput);

  for (int i = 0; i < LED_PIN_COUNT; i++) {
    const int ledPin = LED_PINS[i];
    if (i < mappedValue) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}
