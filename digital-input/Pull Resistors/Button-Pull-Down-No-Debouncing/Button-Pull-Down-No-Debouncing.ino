
const int INPUT_BUTTON_PIN = 8;
const int LED_PIN = 12;

void setup() {
  pinMode(INPUT_BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600); // for printing values to console
}

void loop() {
  // returns 0 (LOW) or 1 (HIGH) based on the button state
  int buttonVal = digitalRead(INPUT_BUTTON_PIN); 
  // print value to Serial the button state
  Serial.println((buttonVal) ? "PRESSED" : "NOT pressed");  
  // Delay a little bit to slow down printing to serial                  
  delay(5);                                    
}
