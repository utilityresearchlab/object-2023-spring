// You must install the Library IRremote, verision >=4.6  

#include <IRremote.hpp>

#define PIN_IR_RECEIVE 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(PIN_IR_RECEIVE);
  Serial.println("Ready to detect IR protocol...");
}

void loop() {
  // Check if we have a signal decoded
  if (IrReceiver.decode()) {
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

    // Resume receiving signals
    IrReceiver.resume();
  }
}