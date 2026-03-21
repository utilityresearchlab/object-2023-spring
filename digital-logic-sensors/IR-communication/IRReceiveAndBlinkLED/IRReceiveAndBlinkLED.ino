// You must install the Library IRremote, verision >=4.6  

#include <IRremote.hpp>


#define PIN_IR_RECEIVE 2
#define PIN_LED LED_BUILTIN

#define COMMAND_PWR 0x45

bool isLEDOn = false;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(PIN_IR_RECEIVE);
  Serial.println("Ready to detect IR protocol...");
  updateLEDState();
}

void updateLEDState() {
  digitalWrite(PIN_LED, isLEDOn);
}

void printIRDebugInfo() {
 // Print received signal info
  Serial.print("Protocol: ");
  Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));

  Serial.print("Address: ");
  Serial.println(IrReceiver.decodedIRData.address, HEX);

  Serial.print("Command: ");
  Serial.println(IrReceiver.decodedIRData.command, HEX);

  Serial.print("Raw Data: ");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  Serial.println("###############");
}

void loop() {
  // Check if we have a signal decoded
  if (IrReceiver.decode()) {
    // Use function below to see the command data coming in
    // printIRDebugInfo();
    
    // Check if we received our special command
    uint16_t receivedCommand = IrReceiver.decodedIRData.command;
    // Serial.println(receivedCommand, HEX);
    // Serial.println(COMMAND_PWR, HEX);

    if (receivedCommand == COMMAND_PWR) {
      // Toggle LED State
      isLEDOn = !isLEDOn;
      Serial.print("Light: ");
      Serial.println(isLEDOn ? "On" : "Off");
    }

    // Resume receiving signals
    IrReceiver.resume();
  }

  // Update the LED State at end
  updateLEDState();
}