
import processing.serial.*;
import java.util.concurrent.*;

import java.util.Map;
import java.util.Set.*;

// The serial port (same as what is used on the Arduino Sketch)
final int BAUD_RATE = 9600;

// Change index this to match your Arduino's port name. You can see the options in the console once you start the
// processing app with your Arduino PLUGGED IN to USB. The name should appear something like:
// [0] "/dev/tty.usbModem1230" : the index for this name would be '0'.
// Note that you may have multiple usb devices named usbModemXXX and you will have to determine which one is the Arduino
// you can get the name of our arduino from the Arduino IDE when selecting the board/port.
int SERIAL_PORT_INDEX = 1;

// Variable to store the Serial Port once we initialize it
Serial SERIAL_PORT;

// Note `final` is like `const` in Arduino. Once declared, final/const variables cannot be changed/edited
// We use these delimiters when sending data from the Arduino side, and once we received the data in processing
// we use these delimiters to recover the key/value pairs of data
// for example, we could send the following string from the arduino: "pot:923#button1:0#joystickX:500#joystickY:800",
// Once received we can split the string up to recover the respective values
final String KEY_VALUE_DELIMITER = ":";
final String KV_PAIR_DELIMITER = "#";

// Circle display variables
int circleSize = 20;
color circleColor = color(255, 0, 100); // Hot Pink color

// The data from serial
String inputSerialDataString;

// The setup() fxn is just like in arduino. It gets called only once at the start of the processing application
void setup () {
  // Creates a window of size w x h = 720 x 390
  size(720, 390);
  // Alternatively using the fullScreen() fxn will make the window fullscreen.
  //fullScreen();

  // List all the available serial ports
  printArray(Serial.list());

  // I know that the first port in the serial list on my mac
  // is usually my Arduino, so I open index 0 (SERIAL_PORT_INDEX = 0)
  // Open whatever port is the one you're using.
  // In most cases the arduino port will be called something like:
  // "/dev/cu.usbmodem1101" or "/dev/tty.usbmodem1101"
  String serialPortName = Serial.list()[SERIAL_PORT_INDEX];

  // Initialize the Serial Port
  SERIAL_PORT = new Serial(this, serialPortName, BAUD_RATE);

  // Wait while serial port gets setup
  delay(1000);

  // don't generate a serialEvent() unless you get a newline character:
  SERIAL_PORT.bufferUntil('\n');

  // set inital background with R,G,B color
  background(10, 10, 10);
}

// This function is like "loop()" in arduino, it gets repeatedly called
void draw () {
  background(0);
  fill(circleColor);
  
  // Parse any input serial data
  //parseSerialDataBasic(inputSerialDataString);
  parseSerialDataKeyValue(inputSerialDataString);
  //parseSerialDataMultipleKeyValuePairs(inputSerialDataString);

  // Draw the shape with the parsed date
  int xPos = width / 2;
  int yPos = height / 2 ;
  ellipse(xPos, yPos, circleSize, circleSize);
}


// If you need to reset anything, you can do it here and this gets called when 'r' is pressed (See keyPressed() fxn below)
void reset() {
  println("Canvas Reset.");
}


// keyPressed: Handles keyboard presses, you can add more keys to check for here
void keyPressed() {
  if (key == 'r') {
    println("Reset triggered");
    reset();
  } else if (key == 's') {
    println("'s' pressed");
  } else if (key == ' ') {
    println("spacebar pressed");
  }
}


// This is called by processing to handle serial events
// You want this function to be quick, and the serialPort parameter is useful if you have multiple serial connections -- it will tell
// which serialport has the data
void serialEvent(Serial serialPort) {
  // get the ASCII string, up until the newline character
  String inputDataString = serialPort.readStringUntil('\n');
  long timestamp = millis();
  if (inputDataString == null) {
    return;
  }
  println(inputDataString);
  inputSerialDataString = inputDataString;
}


//-----------------------------
// Parses a value from a basic data string
// This function takes a serial data string and parses an integer value from it
void parseSerialDataBasic(String inputData) {
  if (inputData == null || inputData.length() == 0) {
    // Do nothing for no data
    return;
  }
  // Remove the whitespace / new line character
  String trimmedInputData = trim(inputData);
  int itemValue = Integer.parseInt(trimmedInputData);
  circleSize = itemValue;
  println("New circleSize: " + itemValue);
}

//-----------------------------
// This function takes a serial data string and parses it to a key-value pair
// Note that this only handles 1 key-value as input
void parseSerialDataKeyValue(String inputData) {
  if (inputData == null || inputData.length() == 0) {
    // Do nothing for no data
    return;
  }
  // Otherwise we have a data string which has multiple items that can be split up using our item delimeter
  String[] itemValuePair = inputData.split(KEY_VALUE_DELIMITER);
  if (itemValuePair == null || itemValuePair.length < 2) {
    return;
  }
  String item = itemValuePair[0];
  String value = trim(itemValuePair[1]);
  int itemValue = Integer.parseInt(value);
  circleSize = itemValue;
  println("New circleSize: " + itemValue);
}

//-----------------------------
// Parsing a Multiple Key:Value Pairs in a String from an Arduino
// This function takes a serial data string and parses multiple key-value pairs, and puts them into the hashmap called keyValuePairsMap below!
// You can "get" the value from the map using keyValuePairsMap.get(key) where key is the string for the key that you want.
// For example:
// To get the "button1", you would call keyValuePairsMap.get("button1").
// To put a value into the hashmap with a key, you would call: keyValuePairsMap.put("button1", 0);
// For more info or HashMap's Usage see: https://processing.org/reference/HashMap.html
HashMap<String, Integer> keyValuePairsMap = new HashMap<String, Integer>();

void parseSerialDataMultipleKeyValuePairs(String inputData) {
  if (inputData == null || inputData.length() == 0) {
    // Do nothing for no data
    return;
  }
  // Splits the original input string on our kvpair delimiter and creates an array of strings where each item is a "key:value" string
  String[] keyValuePairStrings = inputData.split(KV_PAIR_DELIMITER);
  
  // Use a forEach loop to iterate through our string array
  for(String kvString : keyValuePairStrings) {
    // Otherwise we have a data string which has multiple items that can be split up using our item delimeter
    String[] keyValuePair = kvString.split(KEY_VALUE_DELIMITER);
    if (keyValuePair == null || keyValuePair.length < 2) {
      // skip if we have bad input
      continue;
    }
    // trim our values now 
    String keyItem = trim(keyValuePair[0]);
    String value = trim(keyValuePair[1]);
    int itemValue = Integer.parseInt(value);
    
    // Put the value into our hashmap
    keyValuePairsMap.put(keyItem, itemValue);
  }
  
  // After we're done we can gets a value out  of the hashmap and provide 0 as a default value in case there is no corresponding key in the hashmap
  String circleKey = "sensor1";
  int newCircleSize = keyValuePairsMap.getOrDefault(circleKey, 0);
  circleSize = newCircleSize;
  println("New circleSize: " + newCircleSize);
}
