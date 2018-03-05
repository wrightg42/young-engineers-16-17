import sys

import gui
import logic
import coms

def main():
    coms.init()
    gui.init_window()
    
if __name__ == "__main__":
    arguments = [s.lower() for s in sys.argv[1:]]
    if "gps" in arguments or "-gps" in arguments:
        logic.get_gps = True
    main()
