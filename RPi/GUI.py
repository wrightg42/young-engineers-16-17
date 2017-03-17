import math
import tkinter as tk
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import matplotlib.lines as mlines

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
from tkinter import Grid

import Logic

window = None
scan_points = [[], []]
path_points = [[], []]
scan_radii = []

def init_window():
    global window
    window = tk.Tk()
    window.title("IED Detector")
    window.geometry("600x450")
    window.minsize(600, 450)
    window.grid_propagate(False)
    window.after(500, check_stop_command) # Resends the stop move command if bot not in motion after 500 ms
    init_controls()
    plot_grid()
    window.mainloop()

def check_stop_command():
    Logic.time_since_turn += 500
    if len(Logic.keys_down) == 0:
        Logic.move_change(0)
    window.after(500, check_stop_command)

def init_controls():
    # add labels
    tk.Label(window, text="Controls", font=("Vera", 20)).grid(row=0, columnspan=3, sticky="NSEW")

    # add buttons
    fwd = tk.Button(window, text="Forward\n^\nW", font=("Vera", 8), width=5, height=3)
    fwd.grid(row=2, column=0, sticky="N")
    bcd = tk.Button(window, text="Backward\n\\/\nS", font=("Vera", 8), width=5, height=3)
    bcd.grid(row=2, column=0, sticky="S")
    lft = tk.Button(window, text="Left\n<\nA", font=("Vera", 8), width=5, height=3)
    lft.grid(row=2, column=0, sticky="W")
    rgt = tk.Button(window, text="Right\n>\nD", font=("Vera", 8), width=5, height=3)
    rgt.grid(row=2, column=0, sticky="E")
    scn = tk.Button(window, text="Scan\nSpacebar", font=("Vera", 8), width=5, height=3)
    scn.grid(row=3, column=0, sticky="SEW")

    # add handlers for button presses
    fwd.bind("<ButtonPress>", lambda *args: Logic.handle_key("forward"))
    bcd.bind("<ButtonPress>", lambda *args: Logic.handle_key("backward"))
    lft.bind("<ButtonPress>", lambda *args: Logic.handle_key("left"))
    rgt.bind("<ButtonPress>", lambda *args: Logic.handle_key("right"))
    scn.bind("<ButtonPress>", lambda *args: Logic.scan())

    # add handlers for button realeases
    fwd.bind("<ButtonRelease>", lambda *args: Logic.handle_key("forward", False))
    bcd.bind("<ButtonRelease>", lambda *args: Logic.handle_key("backward", False))
    lft.bind("<ButtonRelease>", lambda *args: Logic.handle_key("left", False))
    rgt.bind("<ButtonRelease>", lambda *args: Logic.handle_key("right", False))

    # apply to key bindings
    window.bind("<space>", lambda *args: Logic.scan())
    window.bind("<Key>", lambda *args: Logic.handle_key(args[0].char))
    window.bind("<Up>", lambda *args: Logic.handle_key("up_arrow"))
    window.bind("<Down>", lambda *args: Logic.handle_key("down_arrow"))
    window.bind("<Left>", lambda *args: Logic.handle_key("left_arrow"))
    window.bind("<Right>", lambda *args: Logic.handle_key("right_arrow"))
    window.bind("<KeyRelease>", lambda *args: Logic.handle_key(args[0].char, False))
    window.bind("<KeyRelease-Up>", lambda *args: Logic.handle_key("up_arrow", False))
    window.bind("<KeyRelease-Down>", lambda *args: Logic.handle_key("down_arrow", False))
    window.bind("<KeyRelease-Left>", lambda *args: Logic.handle_key("left_arrow", False))
    window.bind("<KeyRelease-Right>", lambda *args: Logic.handle_key("right_arrow", False))

    # set grid widths
    Grid.rowconfigure(window, 0, weight=1)
    Grid.rowconfigure(window, 1, weight=1)
    Grid.rowconfigure(window, 2, weight=2)
    Grid.rowconfigure(window, 3, weight=1)
    Grid.columnconfigure(window, 0, weight=1)

def plot_grid():
    # create grid
    f = Figure(figsize=(5, 5), dpi=80)
    f.subplots_adjust(bottom=0.15)
    plot = f.add_subplot(111)
    plot.grid(True)

    # plot location and path data
    scan = plot.scatter(scan_points[0], scan_points[1], color="blue")
    plot.plot(path_points[0], path_points[1], color="green", linestyle="--")
    if len(scan_radii) > 0:
        plot.axes.set_xlim(scan_points[0][0] - scan_radii[0] - 0.00001, scan_points[0][0] + scan_radii[0] + 0.00001)
        plot.axes.set_ylim(scan_points[1][0] - scan_radii[0] - 0.00001, scan_points[1][0] + scan_radii[0] + 0.00001)

    # plots direction lines
    for i in range(len(scan_radii)):
        dist = plt.Circle((scan_points[0][i], scan_points[1][i]), scan_radii[i], color=(1, 0, 0, 1), fill=False)
        dist_fill = plt.Circle((scan_points[0][i], scan_points[1][i]), scan_radii[i], color=(1, 0, 0, 0.05))
        plot.add_artist(dist)
        plot.add_artist(dist_fill)

        # adjust axis if circle off plot
        axes = list(plot.axis())
        if axes[0] >= scan_points[0][i] - scan_radii[i]:
            axes[0] = scan_points[0][i] - scan_radii[i] - 0.00001
        if axes[1] <= scan_points[0][i] + scan_radii[i]:
            axes[1] = scan_points[0][i] + scan_radii[i] + 0.00001
        if axes[2] >= scan_points[1][i] - scan_radii[i]:
            axes[2] = scan_points[1][i] - scan_radii[i] - 0.00001
        if axes[3] <= scan_points[1][i] + scan_radii[i]:
            axes[3] = scan_points[1][i] + scan_radii[i] + 0.00001
        plot.axes.set_xlim([axes[0], axes[1]])
        plot.axes.set_ylim([axes[2], axes[3]])

    # plot legend
    path = mlines.Line2D([], [], color="green", linestyle="--")
    distance = mlines.Line2D([], [], color="red")
    plot.legend([scan, distance, path] , ["Scan Points", "Distance of IED", "Bot Path"], loc="upper center", bbox_to_anchor=(0.48, -0.05), fancybox=True, shadow=True, ncol=5)

    # add to window
    canvas = FigureCanvasTkAgg(f, master=window)
    canvas.show()
    canvas.get_tk_widget().grid(column=3, row=1, rowspan=3, sticky="NSEW")
    Grid.columnconfigure(window, 3, weight=9)

    # add label
    header = tk.Label(window, text="Location", font=("Vera", 20)).grid(column=3, row=0, sticky="NSEW")

def add_scan_point(point, radius):
    # add point to plots
    global scan_points
    global scan_radii
    scan_points[0].append(point[0])
    scan_points[1].append(point[1])

    # add circle
    scan_radii.append(radius)

def add_path_point(point):
    # add point to path
    global path_points
    path_points[0].append(point[0])
    path_points[1].append(point[1])

