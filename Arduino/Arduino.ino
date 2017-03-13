#include <QueueArray.h>
#include <printf.h>

#define DEBUG
//#define DONTMOVE

#ifdef DEBUG
  #define DEBUG_BEGIN(x) Serial.begin(x)
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_PRINTLN2(x, y) Serial.println(x, y)
  #define DEBUG_END(x) Serial.end(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTLN2(x, y)
  #define DEBUG_BEGIN(x)
  #define DEBUG_END(x)
#endif

QueueArray <int> queue;

void setup() {
  DEBUG_BEGIN(115200);
  DEBUG_PRINTLN("Setup Begin");
  printf_begin();
  NRFSetup();
  MovementSetup();
  RadioSetup();
  GPSSetup();
  DEBUG_PRINTLN("Setup End");
}

void loop() {
  // Process command if in queue
  if (!queue.isEmpty()) {
    ProcessCommand(queue.pop());
  }
}
