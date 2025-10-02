#include <IRremote.hpp>

// Define pin where the IR receiver is connected
const int RECV_PIN = 2;   // You can change this to your wiring

void setup() {
  Serial.begin(9600);  // Start serial communication
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Start the IR receiver
  Serial.println("IR Receiver ready. Point your remote and press a button...");
}

void loop() {
  // Check if IR signal is received
  if (IrReceiver.decode()) {
    // Print raw decoded data
    Serial.print("IR Code: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // Optionally, print address and command
    Serial.print("Address: 0x");
    Serial.println(IrReceiver.decodedIRData.address, HEX);

    Serial.print("Command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    Serial.println("-----------------------");

    // Prepare for the next value
    IrReceiver.resume();
  }
}
