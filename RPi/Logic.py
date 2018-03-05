import GUI
import Coms
import struct

commands = [["forward", "w", "up_arrow"], ["backward", "s", "down_arrow"], ["left", "a", "left_arrow"], ["right", "d", "right_arrow"]]
keys_down = []
tracking = True
time_since_turn = 9500
get_gps = False

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
    Coms.send(0) # Stop bot moving while scanning
    Coms.send(15) # Get phone distance
    val = Coms.read()
    
    # Check scan data is valid, and within 50m radius
    if val != None and val[0] == 17 and len(val) == 2 and val[1] <= 50000:
        radius = val[1] * 0.0000144503606 * 0.001 # Turn distance from mm into lat/long degrees
        print("Phone distance:", val[1], "mm, ", radius, " lat/long distance")
        
        gps = get_gps_data()
        if gps != None:
            GUI.add_scan_point([gps[3], gps[2]], radius)
            GUI.plot_grid()
    else:
        print("Invalid scan data")

def handle_key(key, pressed = True):
    key = key.lower() # Convert to lower case incase shift was held during key press
    if pressed:
        if key in commands[0] or key in commands[1] or key in commands[2] or key in commands[3]:
            if key not in keys_down:
                # Move key pressed, handle movement
                keys_down.append(key)
                move_change(key)

                # Get gps data to track bot if we changed direction
                if tracking and key in commands[2] or key in commands[3]:
                    # Make sure we havn't turned recently since plotting is time consuming
                    if time_since_turn > 10000:
                        gps = get_gps_data()
                        if gps != None:
                            GUI.add_path_point([gps[3], gps[2]])
                            GUI.plot_grid()
                        else:
                            return
                    global time_since_turn
                    time_since_turn = 0
    elif key in keys_down:
        # Change the movement if key was released
        keys_down.remove(key)
        move_change(keys_down[-1] if len(keys_down) != 0 else 0)

def get_gps_data():
    # Check gps is wanted
    if get_gps:
        # Get gps location of bot
        Coms.send(10) 
        gps = Coms.read()

        # Check GPS data is valid
        if gps != None and gps[0] == 12 and len(gps) == 13: 
            gps = parse_gps(gps)
            print("GPS data:", gps)

            # Only return data if we had gps fix
            if gps[0] > 0:
                return gps
            else:
                print("No GPS fix")
        else:
            print("Invalid GPS data")
    else:
        print("No GPS fix")
   
    return None

def parse_gps(data):
    gps_data = []
    gps_data.append(data[1]) # Fix
    gps_data.append(data[2]) # Fix quality
    gps_data.append(struct.unpack("<f", struct.pack("4B", *data[3:7]))[0]) # Latitude
    gps_data.append(struct.unpack("<f", struct.pack("4B", *data[7:11]))[0]) # Longitude
    gps_data.append(data[11]) # Altitude
    gps_data.append(data[12]) # Satellites
    return gps_data
