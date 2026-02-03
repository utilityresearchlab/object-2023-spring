// Button INPUT Pull Up No Debouncing
// Reads the input on a tact button 
// and prints "PRESSED" to Serial when the Button is pressed, or
// "NOT pressed" when it isn't.
// Note that the buttonVal is inverted in a pull up scenario, as the
// signal is pulled up to VCC when the button is not pressed. So:
//  buttonVal == 1 -> "Not Pressed"
//  buttonVal == 0 -> "PRESSED"
const int INPUT_BUTTON_PIN = 8;
const int LED_PIN = 12;

void setup() {
  // **** Note the use of INPUT_PULLUP for the pinMode *******
  pinMode(INPUT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600); // for printing values to console
}

void loop() {
  // returns 0 (LOW) or 1 (HIGH) based on the button state
  int buttonVal = digitalRead(INPUT_BUTTON_PIN); 
  // print value to Serial the button state
  Serial.println((buttonVal) ? "NOT pressed" : "PRESSED");  
  // Delay a little bit to slow down printing to serial                  
  delay(5);                                    
}
