import GUI
import Coms
import struct

commands = [["forward", "w", "↑"], ["backward", "s", "↓"], ["left", "a", "←"], ["right", "d", "→"]]
keys_down = []

def move_change(cmd):
    if cmd in commands[0]:
        cmd = 3
    elif cmd in commands[1]:
        cmd = 5
    elif cmd in commands[2]:
        cmd = 6
    elif cmd in commands[3]:
        cmd = 9
    else:
        cmd = 0

    Coms.send(cmd)

def scan():
    Coms.send(15)
    val = Coms.read()

    if val != None and val[0] == 17:
        print("Recieved data: ", val)
        Coms.send(10) # Get gps location of bot
        gps = Coms.read()
        if gps != None and gps[0] == 12:
            gps = parse_gps(gps)
            print(gps)

def handle_key(key, pressed = True):
    key = key.lower() # Convert to lower case incase shift was held during key press
    if pressed:
        if key in commands[0] or key in commands[1] or key in commands[2] or key in commands[3]:
            if key not in keys_down:
                # Move key pressed, handle movement
                keys_down.append(key)
                move_change(key)
                return
    elif key in keys_down:
        # change the movement if key was released
        keys_down.remove(key)
        move_change(keys_down[-1] if len(keys_down) != 0 else 0)

def parse_gps(data):
    gps_data = []
    gps_data.append(data[1]) # fix
    gps_data.append(data[2]) # fix quality
    gps_data.append(struct.unpack("<f", struct.pack("4B", *data[3:7]))) # latitude
    gps_data.append(struct.unpack("<f", struct.pack("4B", *data[7:11]))) # longitude
    gps_data.append(data[11]) # altitude
    gps_data.append(data[12]) # satellites
    return gps_data
