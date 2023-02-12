
const int INPUT_BUTTON_PIN = 8;
const int LED_PIN = 12;

void setup() {
  pinMode(INPUT_BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600); // for printing values to console
}

void loop() {
  int buttonVal = digitalRead(INPUT_BUTTON_PIN); // returns 0 (LOW) or 1 (HIGH)
  digitalWrite(LED_PIN, buttonVal);
  Serial.println((buttonVal) ? "PRESSED" : "NOT pressed"); // print value to Serial
  delay(5);                                                // small delay to stop serial overload
}