import GUI
import Coms

ms_delay = 1000
commands = [["forward", "w", "↑"], ["backward", "s", "↓"], ["left", "a", "←"], ["right", "d", "→"]]
keys_down = ["Thing"]

def move_change(cmd):
    # parse command
    if cmd in commands[0]:
        cmd = 2
    elif cmd in commands[1]:
        cmd = 4
    elif cmd in commands[2]:
        cmd = 6
    elif cmd in commands[3]:
        cmd = 8
    else:
        cmd = 0

    Coms.send(cmd)

def scan():
    print("SCANNING")
    Coms.send(14)
    val = Coms.read()

    print(val)
    if val == None:
        print("Timed Out")
    elif val[0] == 16:
        print("recieved data", val)
    Coms.send(0)
    #if val != None: # only replot if gain value
        #GUI.add_scan_point(point, direction)
        #GUI.plot_grid()

def handle_key(key, pressed = True):
    #key = key.lower()
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
         
