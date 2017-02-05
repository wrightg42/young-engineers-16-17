#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
#include <DueTimer.h>

#define TIMEOUT 1000

int msg[1];
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xE8E8E8E8E8LL, 0xE7E7E7E7E7LL };

void NRFUpdate(){ // read radio every milisecond
  if (radio.available()){
    radio.read(msg, radio.getDynamicPayloadSize());
  }
}

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
  #ifdef DEBUG
    radio.printDetails();
  #endif

  Timer1.attachInterrupt(NRFUpdate);
  Timer1.start(1000);
  DEBUG_PRINTLN("End setup - NRF");
}

void NRFSend(byte* msg){ // To be used with command identifier already prepended
  //unsigned long tim = millis();
  DEBUG_END();
  Timer1.stop();
  radio.stopListening();
  radio.closeReadingPipe(1);
  radio.write(msg, sizeof(msg));
  /*while ((!radio.write(msg, sizeof(msg)))){
    if (millis()-tim > TIMEOUT){
      DEBUG_PRINTLN("Timeout");
      break;
    }
  }*/
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  Timer1.start(1000);
  DEBUG_BEGIN(115200);  
}


void NRFLoop(void){    
    DEBUG_PRINTLN(msg[0]);
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
}




