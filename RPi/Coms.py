import datetime
import RPi.GPIO as GPIO
from nrf24 import *

pipes = [[0xe7, 0xe7, 0xe7, 0xe7, 0xe7], [0xe8, 0xe8, 0xe8, 0xe8, 0xe8]]
irq = 16
ce = 24
radio = NRF24()

def init():
    global radio
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
    if not isinstance(msg, list):
        msg = [int(msg)]
    global radio
    radio.write(msg)

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
   

