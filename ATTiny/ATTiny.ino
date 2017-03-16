#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
 
void setup() {
  // Transmitter is connected to physical pin 5, software pin 0
  mySwitch.enableTransmit(0);
  mySwitch.setProtocol(5);
  mySwitch.setRepeatTransmit(15);
}
 
void loop() {
  mySwitch.send(47869, 16);
  delay(5);
}
