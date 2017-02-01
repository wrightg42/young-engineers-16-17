#include "printf.h"
#include "NRF.h"
#include "Radio.h"

void setup() {
  Serial.begin(115200);
  printf_begin();
  NRFSetup();
  RadioSetup();
}

void loop() {
  NRFLoop();
  RadioLoop();
}
