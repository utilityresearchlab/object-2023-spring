const int TRANSISTOR_PIN = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRANSISTOR_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRANSISTOR_PIN, HIGH);
  delay(2000);
  digitalWrite(TRANSISTOR_PIN, LOW);
  delay(2000);
}
