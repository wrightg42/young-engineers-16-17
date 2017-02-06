import datetime
import RPi.GPIO as GPIO
from nrf24 import *

pipes = [[0xe7, 0xe7, 0xe7, 0xe7, 0xe7], [0xe8, 0xe8, 0xe8, 0xe8, 0xe8]]
irq = 16
ce = 24
radio = NRF24()

def init():
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
    print(msg)
    radio.write(msg)

def read():
    msg = []
    radio.startListening()
    radio.openReadingPipe(1, pipes[1])

    start = datetime.datetime.now()
    while (datetime.datetime.now() - start).seconds < 1:
        while radio.available():
            data = []
            radio.read(data, radio.getDynamicPayloadSize())
            print(data)
            msg.append(data)
        if msg != []:
            break

    print(msg)
    radio.stopListening()
    radio.openWritingPipe(pipes[0])
    radio.powerDown()
    radio.powerUp()
    return msg if msg != [] else None
   

