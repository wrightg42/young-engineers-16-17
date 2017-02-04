#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"

int msg[1];
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xE8E8E8E8E8LL, 0xE7E7E7E7E7LL };

void NRFSetup(void){
  DEBUG_PRINTLN("Setup - NRF");
  radio.begin();
 
  radio.setPayloadSize(32);
  radio.setChannel(0x60);
  radio.setRetries(0, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);

  radio.setAutoAck(1);
  radio.enableDynamicPayloads();
  radio.enableAckPayload();

  radio.openReadingPipe(1, pipes[1]);
  radio.openWritingPipe(pipes[0]);
  radio.startListening();
  radio.printDetails();
  DEBUG_PRINTLN("End setup - NRF");
}
 
void NRFLoop(void){
  if (radio.available()){
    radio.read(msg, radio.getDynamicPayloadSize());    
    DEBUG_PRINTLN(msg[0]);
    radio.stopListening();
    ProcessCommand(msg);
    /*if (msg[0] == 115) {    
      Serial.println("pinging back");
      delay(100);
      int data[4] = {111, 222, 333, 444};
      while (!radio.write(&data, sizeof(data))) { // Ping till it sends
      }
      Serial.println("Pinged");
      //radio.openReadingPipe(1, pipes[1]);
    }*/
    radio.startListening();
  }
}




