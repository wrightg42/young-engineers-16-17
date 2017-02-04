import GUI
import Coms
import numpy

ms_delay = 1000
commands = [["forward", "w", "↑"], ["backward", "s", "↓"], ["left", "a", "←"], ["right", "d", "→"]]
keys_down = [0]

def move_change(cmd):
    # parse command
    if cmd in commands[0]:
        cmd = numpy.uint8(2)
    elif cmd in commands[1]:
        cmd = numpy.uint8(4)
    elif cmd in commands[2]:
        cmd = numpy.uint8(6)
    elif cmd in commands[3]:
        cmd = numpy.uint8(8)
    else:
        cmd = numpy.uint8(0)

    Coms.send(cmd)

def scan():
    print("SCANNING")
    Coms.send(numpy.unint8(14))
    val = Coms.read()

    print(val)
    if val[0] == ord(16):
        print("recieved data", val)
    #if val != None: # only replot if gain value
        #GUI.add_scan_point(point, direction)
        #GUI.plot_grid()

def handle_key(key, pressed = True):
    key = key.lower()
    if pressed:
        if key == " ":
            # Scan if scan pressed
            scan()
        elif key in commands[0] or key in commands[1] or key in commands[2] or key in commands[3]:
            if keys_down[-1] != key:
                # Move key pressed, handle movement
                keys_down.append(key)
                move_change(key)
    elif (key in keys_down) and (key == keys_down[-1]):
        # change the movement if latest key was released
        keys_down.remove(key)
        move_change(keys_down[-1] if len(keys_down) != 0 else "")
         
