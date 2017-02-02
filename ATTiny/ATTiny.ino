#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
 
void setup() {
  mySwitch.enableTransmit(6); // pin 6 on arduino uno. change to 0 for attiny85
  mySwitch.setProtocol(5);
  mySwitch.setRepeatTransmit(15);
}
 
void loop() {
  mySwitch.send(47869, 16);
  delay(250);
}
