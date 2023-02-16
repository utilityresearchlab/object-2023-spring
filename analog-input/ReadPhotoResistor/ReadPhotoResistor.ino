/*
  ReadPhotoResistor

  Reads an analog input on pin A0, uses a voltage divider with a 10kOhm resistor
  Photoresistor is connected on the 5V side of the voltage divider
*/

const int PHOTORES_PIN = A0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(PHOTORES_PIN, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(PHOTORES_PIN);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // print out the value you read:
  Serial.println(sensorValue);
  // Print Min and max line to prevent plotter from auto-scaling
  // See: https://www.diyrobocars.com/2020/05/04/arduino-serial-plotter-the-missing-manual/
  Serial.println("Min:0,Max:1023");

  // Print converted voltage measurement
  // Serial.println(voltage);
  // Serial.println("Min:0,Max:5");
  
  // Slow down serial port processing (so data input in slower)
  delay(50);
}

