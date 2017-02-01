#include "Arduino.h"
#include "RCSwitch.h"

RCSwitch mySwitch = RCSwitch();

void RadioSetup() {
  mySwitch.enableReceive(2); // Receiver on pin 2
}

void RadioLoop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    int protocol = mySwitch.getReceivedProtocol();
    if (value == 47869 && protocol == 3) {
      Serial.print("Package Received -> RSSI: ");
      Serial.println(analogRead(0));
    } else {
      Serial.println("External package:");
      Serial.print("\tReceived ");
      Serial.print(mySwitch.getReceivedValue());
      Serial.print(" / ");
      Serial.print(mySwitch.getReceivedBitlength());
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println(mySwitch.getReceivedProtocol());
      Serial.print("\tRSSI: ");
      Serial.println(analogRead(0));
    }

    mySwitch.resetAvailable();
  }
}

