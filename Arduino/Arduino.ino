#include "printf.h"
#include "NRF.h"

void setup() {
  Serial.begin(115200);
  printf_begin();
  NRFSetup();
}

void loop() {
  NRFloop();
}
