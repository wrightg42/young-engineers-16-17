import datetime
import RPi.GPIO as GPIO
from nrf24 import *

pipes = [[0xe7, 0xe7, 0xe7, 0xe7, 0xe7], [0xe8, 0xe8, 0xe8, 0xe8, 0xe8]]
irq = 16
ce = 24
radio = NRF24()

def init():
    global radio
    radio = NRF24()
    radio.begin(0, 1, ce, irq)
    radio.setPayloadSize(32)
    radio.setChannel(0x60)
    radio.setRetries(0,15)
    radio.setDataRate(NRF24.BR_1MBPS)
    radio.setPALevel(NRF24.PA_MAX)

    radio.setAutoAck(1)
    radio.enableDynamicPayloads()
    radio.enableAckPayload()

    radio.openWritingPipe(pipes[0])
    radio.openReadingPipe(1, pipes[1])
    radio.powerUp()

def print_details():
    global radio
    radio.printDetails()

def send(msg):
    global radio
    radio.stopListening()
    radio.write(msg)
    print(msg)

def read():
    global radio
    msg = []
    radio.startListening()
    start = datetime.datetime.now()
    while (datetime.datetime.now() - start).seconds < 1:
        if radio.available():
            radio.read(msg, radio.getDynamicPayloadSize())
            print(msg)
            break
    radio.stopListening()
    return msg if msg != [] else None

#while True:
#    radio.write([c])
#    if radio.isAckPayloadAvailable():
#        newBuff = []
#        radio.read(newBuff, radio.getDynamicPayloadSize())
#        print(newBuff)
#    c += 1
#    print(c)
#    time.sleep(1)
   

