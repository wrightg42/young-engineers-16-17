#include "RCSwitch.h"
#include "RCSwitchB.h"

#define RADIOTIMEOUT 100
#define PROTOCOL 2

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
    if (value == 47869 && protocol == PROTOCOL) {
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
    if (value == 47869 && protocol == PROTOCOL) {
      DEBUG_PRINT("Package Received on right radio -> RSSI: ");
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

int GetPhoneDistance(){
  int left = 0;
  int right = 0;
  int curTime = millis();
  while ((left == 0) && (millis() - curTime < RADIOTIMEOUT)){
    left = GetSignalLeft();
  }
  curTime = millis();
  while ((right == 0) && (millis() - curTime < RADIOTIMEOUT)){
    right = GetSignalRight();
  }

  if (left == 0) {
    left = right;
  }
  if (right == 0) {
    right = left;
  }
  
  float avgSignal = (left + right) / 2;
  DEBUG_PRINT("Average Signal Strength: ");
  DEBUG_PRINTLN(avgSignal);
  int distance = int(-15.43 * avgSignal + 9682.7); // Linear when near
  if (avgSignal < 350) {
    // Exponential graph more appropriate when far
    distance = int(7.267 * pow(10, 5) * pow(exp(1), -0.013 * avgSignal) - 1);
  }

  // Make sure we don't send a negative value as this would become unused data
  if (distance < 0) {
    distance = 0;
  }
  
  DEBUG_PRINT("Phone Distance: ");
  DEBUG_PRINTLN(distance);
  return distance;
}

void SendRadioScan() {
  DEBUG_PRINTLN("radio Scan start");
  int scanData[2] = { 17 }; // 17 is return 433 scan data command
  scanData[1] = GetPhoneDistance();
  delayMicroseconds(10000); // Delay 10ms, giving pi time to swap to read mode
  NRFSend(scanData, 2);
}
