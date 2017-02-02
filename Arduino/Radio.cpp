#include "Arduino.h"
#include "RCSwitch.h"
#include "RCSwitchB.h"

RCSwitch rswitch = RCSwitch();
RCSwitchB lswitch = RCSwitchB();

void RadioSetup() {
  Serial.println("Begin Radio Setup");
  rswitch.enableReceive(2);
  lswitch.enableReceive(3);
  Serial.println("End Radio Setup");
}

int GetSignalRight() {
  if (rswitch.available()) {
    int value = rswitch.getReceivedValue();
    int protocol = rswitch.getReceivedProtocol();
    int rssi = analogRead(0);
    if (value == 47869 && protocol == 3) {
      Serial.print("Package Received on right radio -> RSSI: ");
      Serial.println(rssi);
    } else {
      Serial.println("External package on right radio :");
      Serial.print("\tReceived ");
      Serial.print(value);
      Serial.print(" / ");
      Serial.print("Protocol: ");
      Serial.println(protocol);
      Serial.print("\tRSSI: ");
      Serial.println(rssi);
    }

    rswitch.resetAvailable();

    return rssi;
  }
}


int GetSignalLeft() {
  if (lswitch.available()) {
    int value = lswitch.getReceivedValue();
    int protocol = lswitch.getReceivedProtocol();
    int rssi = analogRead(1);
    if (value == 47869 && protocol == 3) {
      Serial.print("Package Received on left radio -> RSSI: ");
      Serial.println(rssi);
    } else {
      Serial.println("External package on left radio:");
      Serial.print("\tReceived ");
      Serial.print(value);
      Serial.print(" / ");
      Serial.print("Protocol: ");
      Serial.println(protocol);
      Serial.print("\tRSSI: ");
      Serial.println(rssi);
    }

    lswitch.resetAvailable();

    return rssi;
  }
}

void RadioLoop() {
  GetSignalRight();
  GetSignalLeft();
}


