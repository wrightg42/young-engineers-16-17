#include "printf.h"

#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_BEGIN(x) Serial.begin(x)
#else
  #define DEBUG_PRINT(X)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_BEGIN(x)
#endif

void setup() {
  DEBUG_BEGIN(115200);
  DEBUG_PRINTLN("Setup Begin");
  //printf_begin();
  NRFSetup();
  MovementSetup();
  //RadioSetup();
  //GPSSetup();
  delay(1);
  DEBUG_PRINTLN("Setup End");
}

void loop() {
  NRFLoop();
  //RadioLoop();
}
