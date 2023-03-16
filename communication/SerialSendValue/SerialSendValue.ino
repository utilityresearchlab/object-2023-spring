void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 255; i++) {
    Serial.print("sensor1:");
    Serial.print(i);
    Serial.println();
    delay(5);
  }

 for (int i = 255; i >= 0; i--) {
    Serial.print("sensor1:");
    Serial.print(i);
    Serial.println();
    delay(5);
  }
}
