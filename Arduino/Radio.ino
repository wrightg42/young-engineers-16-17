#include "RCSwitch.h"
#include "RCSwitchB.h"

RCSwitch rswitch = RCSwitch();
RCSwitchB lswitch = RCSwitchB();

void RadioSetup() {
  DEBUG_PRINTLN("Begin Radio Setup");
  lswitch.enableReceive(2);
  rswitch.enableReceive(3);
  DEBUG_PRINTLN("End Radio Setup");
}

int GetSignalLeft() {
  if (lswitch.available()) {
    int value = lswitch.getReceivedValue();
    int protocol = lswitch.getReceivedProtocol();
    int rssi = analogRead(0);
    if (value == 47869 && protocol == 5) {
      DEBUG_PRINT("Package Received on left radio -> RSSI: ");
      DEBUG_PRINTLN(rssi);
    } else {
      DEBUG_PRINTLN("External package on left radio:");
      DEBUG_PRINT("\tReceived ");
      DEBUG_PRINT(value);
      DEBUG_PRINT(" / ");
      DEBUG_PRINT("Protocol: ");
      DEBUG_PRINTLN(protocol);
      DEBUG_PRINT("\tRSSI: ");
      DEBUG_PRINTLN(rssi);
    }

    lswitch.resetAvailable();

    return rssi;
  } else {
    return 0;
  }
}

int GetSignalRight() {
  if (rswitch.available()) {
    int value = rswitch.getReceivedValue();
    int protocol = rswitch.getReceivedProtocol();
    int rssi = analogRead(1);
    if (value == 47869 && protocol == 5) {
      DEBUG_PRINTLN("Package Received on right radio -> RSSI: ");
      DEBUG_PRINTLN(rssi);
    } else {
      DEBUG_PRINTLN("External package on right radio :");
      DEBUG_PRINT("\tReceived ");
      DEBUG_PRINT(value);
      DEBUG_PRINT(" / ");
      DEBUG_PRINT("Protocol: ");
      DEBUG_PRINTLN(protocol);
      DEBUG_PRINT("\tRSSI: ");
      DEBUG_PRINTLN(rssi);
    }

    rswitch.resetAvailable();

    return rssi;
  } else {
    return 0;
  }
}

void ScanRadio() {
  DEBUG_PRINTLN("radio Scan start");
  int scanData[3] = { 17 }; // 17 is return 433 scan data command
  scanData[1] = GetSignalLeft();
  scanData[2] = GetSignalRight();
  delayMicroseconds(10000); // Delay 10ms, giving pi time to swap to read mode
  NRFSend(scanData, 3);
}
