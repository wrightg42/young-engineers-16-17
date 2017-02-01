import GUI
import Coms

ms_delay = 1000
commands = [["forward", "w", "↑"], ["backward", "s", "↓"], ["left", "a", "←"], ["right", "d", "→"]]
move_command = ""
keys_down = [0]

def main():
    if move_command != "":
        Coms.send(move_command)

def move_change(cmd):
    # parse command
    if cmd in commands[0]:
        cmd = "f"
    elif cmd in commands[1]:
        cmd = "b"
    elif cmd in commands[2]:
        cmd = "l"
    elif cmd in commands[3]:
        cmd = "r"
    else:
        cmd = ""

    global move_command   
    move_command = cmd
    if cmd == "":
        Coms.send(" ")
    main()

def scan():
    print("SCANNING")
    Coms.send("s")
    val = Coms.read()

    print(val)
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
    elif key in keys_down:
        if keys_down.index(key) == len(keys_down) - 1:
            # change the movement if latest key was removed
            move_change(keys_down[keys_down.index(key) - 1] if keys_down.index(key) != 0 else "")
        keys_down.remove(key) 
