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
    radio.setRetries(5,15)
    radio.setDataRate(NRF24.BR_1MBPS)
    radio.setPALevel(NRF24.PA_MAX)

    radio.setAutoAck(1)
    radio.enableDynamicPayloads()
    radio.enableAckPayload()

    radio.startListening()
    radio.openReadingPipe(1, pipes[1])
    radio.stopListening()
    radio.openWritingPipe(pipes[0])
    radio.powerDown()
    radio.powerUp()

def print_details():
    global radio
    radio.printDetails()

def send(msg):
    print(msg)
    radio.write(msg)

def read(timeout = 1000):
    corrupt = False
    msg = []
    radio.startListening()
    radio.openReadingPipe(1, pipes[1])

    start = datetime.datetime.now()
    while (datetime.datetime.now() - start).total_seconds() * 1000 < timeout:
        while radio.available():
            data = []
            radio.read(data, radio.getDynamicPayloadSize())
            if corrupted_bytes(data):
                currupt = True
            data = fix_bytes(data)
            msg.append(bytes_to_int(data))
        if msg != []:
            break

    print("msg: " + str(msg))
    radio.stopListening()
    radio.openWritingPipe(pipes[0])
    radio.powerDown()
    radio.powerUp()
    if corrupt:
        print("Corrupt payload")
        return "CORRUPT"
    elif msg == []:
        print("Timed Out")
        return None
    else:
        return msg

def corrupted_bytes(bytes):
    # Check each byte hasn't been corrupted
    for byte in bytes:
        binary = bin(byte)[2:]
        if len(binary) % 2 == 1:
            binary = "0" + binary
        for i in range(int(len(binary) / 2)):
            if binary[2 * i] == binary[2 * i + 1]:
                return True
    
    return False

def fix_bytes(bytes):
    new_bytes = []

    # Fix each byte tp remove the security from corruption
    for byte in bytes:
        binary = bin(byte)[2:]
        if len(binary) % 2 == 1:
            binary = "0" + binary
        new_byte = binary[::2]
        new_bytes.append(int(new_byte, 2))

    return new_bytes

def bytes_to_int(bytes):
    i = 0
    for j in range(len(bytes) - 1, -1, -1):
        i += bytes[j] << (4 * j)

    return i