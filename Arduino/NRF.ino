#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
#include <DueTimer.h>

#define TIMEOUT 1000

int msg[1];
RF24 radio(9, 10);
const uint64_t pipes[2] = { 0xE8E8E8E8E8LL, 0xE7E7E7E7E7LL };

void NRFSetup(void) {
  DEBUG_PRINTLN("Setup - NRF");
  radio.begin();

  radio.setPayloadSize(32);
  radio.setChannel(0x60);
  radio.setRetries(5, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);

  radio.setAutoAck(1);
  radio.enableDynamicPayloads();
  radio.enableAckPayload();

  radio.openReadingPipe(1, pipes[1]);
  radio.openWritingPipe(pipes[0]);
  radio.startListening();

#ifdef DEBUG
  radio.printDetails();
#endif

  Timer1.attachInterrupt(NRFRead);
  Timer1.start(1000);
  DEBUG_PRINTLN("End setup - NRF");
}

void NRFRead() {
  while (radio.available()) {
    radio.read(msg, radio.getDynamicPayloadSize());
    queue.push(msg[0]);
  }
}

void NRFSend(int* data, int dataLen) {
  DEBUG_PRINTLN("Sending");
  Timer1.stop(); // Stop interupt so it doesn't try read while sending
  radio.stopListening();
  for (int i = 0; i < dataLen; i++) {
    int curTime = millis();
    while (!radio.write(&data[i], sizeof(data[i]))) {
      if (millis() - curTime > TIMEOUT) {
        DEBUG_PRINTLN("Timed out");
        break;
      }
    }
  }
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  Timer1.start(); 
}
