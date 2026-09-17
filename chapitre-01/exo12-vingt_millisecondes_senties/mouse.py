import tkinter as tk
import time

DELAY = 50  # retard en millisecondes, réglable entre 0 et 200

root = tk.Tk()
root.title("Test de latence souris")

canvas = tk.Canvas(root, width=800, height=500, bg="white")
canvas.pack()

circle = canvas.create_oval(390, 240, 410, 260, fill="black")

mouse_x = 400
mouse_y = 250


def mouse_move(event):
    global mouse_x, mouse_y
    mouse_x = event.x
    mouse_y = event.y


def update():
    canvas.coords(
        circle,
        mouse_x - 10,
        mouse_y - 10,
        mouse_x + 10,
        mouse_y + 10
    )

    root.after(DELAY, update)


canvas.bind("<Motion>", mouse_move)

update()
root.mainloop()