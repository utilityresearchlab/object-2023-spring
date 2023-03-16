
// Pin Constants
const int BUTTON_1_PIN = 3;
const int BUTTON_2_PIN = 4;
const int POT_1_PIN = A1;

// Serial Data Message Delimiters
const String KEY_VALUE_DELIMITER = ":";
const String KV_PAIR_DELIMITER = "#";

// Variables to hold sensor values
int button1Value;
int button2Value;
int pot1Value;

void setup() {
  // Init pins
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
  pinMode(POT_1_PIN, INPUT);

  // Init serial port
  Serial.begin(9600);
}

void loop() {
  // Get updated sensor values
  updateSensorValues();
  sendDataMessageOverSerial();

  // delay data rate 
  delay(20);
}

// Updates the out sensor input values
void updateSensorValues() {
  button1Value = digitalRead(BUTTON_1_PIN);
  button2Value = digitalRead(BUTTON_2_PIN);
  pot1Value = analogRead(POT_1_PIN);
}

// Now send a data message consisting of multiple inputs as key:value pairs
// and separated by by "#"
// Results in a string sent over serial that looks something like:
// "button1:1#button2:0#pot1:500"

void sendDataMessageOverSerial() {
  // Create a KV pair
  Serial.print("button1");
  Serial.print(KEY_VALUE_DELIMITER);
  Serial.print(button1Value); 
  
  // Separate the next and previous KV Pair with a "#"
  Serial.print(KV_PAIR_DELIMITER);

  // Create a KV pair
  Serial.print("button2");
  Serial.print(KEY_VALUE_DELIMITER);
  Serial.print(button2Value); 

  // Separate the next and previous KV Pair with a "#"
  Serial.print(KV_PAIR_DELIMITER);

  Serial.print("pot1");
  Serial.print(KEY_VALUE_DELIMITER);
  Serial.print(button2Value); 

  // End Message with new line
  Serial.println();
}
