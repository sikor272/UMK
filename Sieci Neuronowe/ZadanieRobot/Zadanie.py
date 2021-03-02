from tkinter import *
from PIL import ImageTk, Image
from ZadanieRobot.Point import Point
from ZadanieRobot.Examples import Examples
from ZadanieRobot.Neural_Network import Neural_Network
import numpy as np
import matplotlib.pyplot as plt


class Gui(object):
    def __init__(self, center=Point(0, 0), arm_length=10, no_of_examples=1000, iterations=1000, eta=0.1, width=400,
                 height=400, layers=[2, 10, 2]):
        self.root = Tk()
        self.width = width
        self.height = height
        self.root.geometry(str(self.width) + "x" + str(self.height))
        self.canvas = Canvas(self.root, width=400, height=400, highlightthickness=1, highlightbackground="black")
        self.img = ImageTk.PhotoImage(Image.open("./robot.jpg"))
        self.canvas.create_image(0, 0, image=self.img, anchor=NW)
        self.canvas.bind("<Button-1>", self.callback)
        self.canvas.bind("<B1-Motion>", self.callback)
        self.canvas.grid(row=0, column=1)
        self.arm_length = arm_length
        self.center = center
        self.iterations = iterations
        self.no_of_examples = no_of_examples
        self.eta = eta
        self.layers = layers.copy()
        self.examples = None
        self.input = None
        self.output = None
        self.x_train = None
        self.y_train = None
        self.neural_network = Neural_Network(eta=self.eta, layers=self.layers)
        self.build()
        self.root.mainloop()

    def build(self):
        self.canvas.create_rectangle(0, 0, self.width, self.height, fill='white', outline="")
        self.canvas.create_image(0, 0, image=self.img, anchor=NW)
        self.examples = Examples(self.arm_length, self.center)
        self.input, self.output = self.examples.generate(self.no_of_examples)
        self.x_train = (np.array(self.input) - np.min(self.input)) / (
                np.max(self.input) - np.min(self.input)) * 0.8 + 0.1
        self.y_train = np.array(self.output) / np.pi * 0.8 + 0.1
        for _ in range(self.iterations):
            self.neural_network.train(self.x_train, self.y_train)

    def callback(self, event):
        self.canvas.delete("all")
        event_point = Point(event.x, self.height - event.y)
        event_point = event_point / 400
        event_point = event_point * 0.8 + 0.1
        out = self.neural_network.forward([event_point.x, event_point.y])
        alfa = (out[0] - 0.1) / 0.8 * np.pi
        beta = (out[1] - 0.1) / 0.8 * np.pi
        point_a = self.translate(self.center, alfa)
        point_b = self.translate(point_a, np.pi - beta + alfa)
        point_a = Point(point_a.x, self.height - point_a.y)
        point_b = Point(point_b.x, self.height - point_b.y)
        self.canvas.create_rectangle(0, 0, self.width, self.height, fill='white', outline="")
        self.canvas.create_image(0, 0, image=self.img, anchor=NW)
        self.draw_line(self.center, point_a, 'green')
        self.draw_line(point_a, point_b, 'green')
        self.draw_point(self.center, 'blue')
        self.draw_point(point_a, 'blue')
        self.draw_point(point_b, 'blue')
        self.draw_point(event, 'red')

    def translate(self, center, angle):
        return Point(center.x + self.arm_length * np.sin(angle), center.y - self.arm_length * np.cos(angle))

    def draw_line(self, point_a, point_b, color):
        self.canvas.create_line(point_a.x, point_a.y, point_b.x, point_b.y, fill=color)

    def draw_point(self, point, color):
        self.canvas.create_rectangle(point.x - 5, point.y - 5, point.x + 5, point.y + 5, fill=color)


gui = Gui(center=Point(200, 200), arm_length=100, no_of_examples=1000, iterations=10000, eta=0.01, width=400,
          height=400, layers=[2, 10, 20, 10, 2])

err = gui.neural_network.errors
plt.plot(range(len(err)), err)
plt.show()
