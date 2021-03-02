import numpy as np
from PIL import Image
from ZadanieKohonen.Kohonen import Kohonen
import matplotlib.pyplot as plt
from tkinter import *


class Gui(object):
    def __init__(self, n=5, m=5):
        self.root = Tk()
        self.width = 450
        self.height = 450
        self.root.geometry(str(self.width) + "x" + str(self.height + 50))
        self.canvas = Canvas(self.root, width=self.width, height=self.height, highlightthickness=1,
                             highlightbackground="black")
        self.button = []
        self.inputs = []
        self.n = n
        self.m = m
        self.neural = Kohonen(self.n, self.m, 2)
        self.build()
        self.root.mainloop()

    def build(self):
        self.canvas.bind("<Button-1>", self.callback)
        self.canvas.bind("<B1-Motion>", self.callback)
        self.canvas.grid(row=0, column=0, columnspan=100)
        self.button.append(Button(self.root, text="Clear", width=6, height=2, bg="white",
                                  command=lambda: self.clear()))
        self.button[0].grid(row=1, column=0)
        self.button.append(Button(self.root, text="Run", width=6, height=2, bg="white",
                                  command=lambda: self.kohonen()))
        self.button[1].grid(row=1, column=1)
        self.button.append(Button(self.root, text="Exit", width=6, height=2, bg="white",
                                  command=lambda: self.root.destroy()))
        self.button[2].grid(row=1, column=2)
        self.button.append(Button(self.root, text="Square", width=6, height=2, bg="white",
                                  command=lambda: self.square()))
        self.button[3].grid(row=1, column=3)
        self.button.append(Button(self.root, text="Circle", width=6, height=2, bg="white",
                                  command=lambda: self.circle()))
        self.button[4].grid(row=1, column=4)
        self.button.append(Button(self.root, text="Random", width=6, height=2, bg="white",
                                  command=lambda: self.random()))
        self.button[5].grid(row=1, column=5)

    def callback(self, event):
        self.draw_point([event.x, event.y], "black")
        self.inputs.append(np.array([event.x, event.y]))

    def clear(self):
        self.canvas.delete("all")
        self.canvas.create_rectangle(0, 0, self.width, self.height, fill='white', outline="")
        self.inputs = []

    def square(self):
        for x in range(50, self.width - 50):
            self.inputs.append(np.array([x, 50]))
            self.inputs.append(np.array([x, self.height - 50]))
        for y in range(50, self.height - 50):
            self.inputs.append(np.array([50, y]))
            self.inputs.append(np.array([self.width - 50, y]))
        self.repaint()

    def circle(self):
        for alpha in range(0, 360):
            x = self.width / 2 + self.width / 3 * np.cos(alpha / 180 * np.pi)
            y = self.height / 2 + self.height / 3 * np.sin(alpha / 180 * np.pi)
            self.draw_point([x, y], "black")
            self.inputs.append(np.array([x, y]))

    def random(self):
        for _ in range(40):
            x = np.random.randint(0, self.width)
            y = np.random.randint(0, self.height)
            self.inputs.append(np.array([x, y]))
            self.draw_point([x, y], "black")

    def repaint(self):
        self.canvas.delete("all")
        for i in self.inputs:
            self.draw_point(i, "black")

    def paintSom(self):
        for i in range(self.n):
            for j in range(self.m):
                if j < self.m - 1:
                    x, y = self.neural.som[i, j]
                    x2, y2 = self.neural.som[i, j + 1]
                    self.canvas.create_line(x, y, x2, y2, fill="red")
                if i < self.n - 1:
                    x, y = self.neural.som[i, j]
                    x2, y2 = self.neural.som[i + 1, j]
                    self.canvas.create_line(x, y, x2, y2, fill="red")
                self.draw_point(self.neural.som[i, j], "white")

    def kohonen(self):
        self.neural = Kohonen(self.n, self.m, 2)
        # Move to center
        #self.neural.som += [self.width / 2, self.height / 2]
        # Move around all screen
        self.neural.som *= [self.width, self.height]
        for i in range(100):
            self.neural.train(i * 25, np.array(self.inputs))
            self.repaint()
            self.paintSom()
            self.canvas.update()
            print("Krok " + str(i) + " na 100")

    def draw_point(self, point, color):
        self.canvas.create_oval(point[0] - 3, point[1] - 3, point[0] + 3, point[1] + 3, fill=color)


main = Gui(10, 10)
