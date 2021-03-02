import tkinter as tk
import numpy as np
import random
from ZadanieAdaLine.Input import *
from ZadanieAdaLine.AdaLine import AdaLine

# ZADANIE DOMOWE 5 - GUI
class Window(object):
    def __init__(self, rows, cols, input_size, training_data, learning_rate=0.01, iterations=100):
        self.root = tk.Tk()
        self.rows = rows
        self.cols = cols
        self.adalines = []
        self.learning_rate = learning_rate
        self.iterations = iterations
        self.input_size = input_size
        for _ in range(10):
            self.adalines.append(AdaLine(input_size * input_size, self.learning_rate, self.iterations, str(_)))
        self.training_data = training_data
        self.array = np.zeros((rows, cols))
        self.buttons = {}
        self.controls = {}
        self.labels = {}
        self.probability = [0.0 for _ in range(10)]
        self._add_buttons()
        self._changeOutput()

    def show(self):
        self.root.mainloop()

    def _add_buttons(self):
        for j in range(self.cols):
            for i in range(self.rows):
                self.buttons[i, j] = tk.Button(self.root, text="", width=4, height=3, bg="red",
                                               command=lambda x=i, y=j: self.change(x, y))
                self.buttons[i, j].grid(row=i, column=j)
        self.controls[0] = tk.Button(self.root, text="Clear", width=4, height=3, bg="white",
                                     command=lambda: self.clear())
        self.controls[0].grid(row=0, column=15)
        self.controls[1] = tk.Button(self.root, text="^", width=4, height=3, bg="white",
                                     command=lambda: self.move('Up'))
        self.controls[1].grid(row=0, column=16)
        self.controls[2] = tk.Button(self.root, text="Neg", width=4, height=3, bg="white",
                                     command=lambda: self.neg())
        self.controls[2].grid(row=0, column=17)
        self.controls[3] = tk.Button(self.root, text="Vert", width=4, height=3, bg="white",
                                     command=lambda: self.move('Vert'))
        self.controls[3].grid(row=0, column=18)
        self.controls[4] = tk.Button(self.root, text="Hori", width=4, height=3, bg="white",
                                     command=lambda: self.move('Hori'))
        self.controls[4].grid(row=0, column=19)
        self.controls[5] = tk.Button(self.root, text="<", width=4, height=3, bg="white",
                                     command=lambda: self.move('Left'))
        self.controls[5].grid(row=1, column=15)
        self.controls[6] = tk.Button(self.root, text="v", width=4, height=3, bg="white",
                                     command=lambda: self.move('Down'))
        self.controls[6].grid(row=1, column=16)
        self.controls[7] = tk.Button(self.root, text=">", width=4, height=3, bg="white",
                                     command=lambda: self.move('Right'))
        self.controls[7].grid(row=1, column=17)
        self.controls[8] = tk.Button(self.root, text="Rand", width=4, height=3, bg="white",
                                     command=lambda: self.rand())
        self.controls[8].grid(row=1, column=18)
        self.controls[9] = tk.Button(self.root, text="Exit", width=4, height=3, bg="white",
                                     command=lambda: self.root.destroy())
        self.controls[9].grid(row=1, column=19)
        self.controls[10] = tk.Button(self.root, text="0", width=4, height=3, bg="white",
                                      command=lambda: self.set(0))
        self.controls[10].grid(row=2, column=15)
        self.controls[11] = tk.Button(self.root, text="1", width=4, height=3, bg="white",
                                      command=lambda: self.set(1))
        self.controls[11].grid(row=2, column=16)
        self.controls[12] = tk.Button(self.root, text="2", width=4, height=3, bg="white",
                                      command=lambda: self.set(2))
        self.controls[12].grid(row=2, column=17)
        self.controls[13] = tk.Button(self.root, text="3", width=4, height=3, bg="white",
                                      command=lambda: self.set(3))
        self.controls[13].grid(row=2, column=18)
        self.controls[14] = tk.Button(self.root, text="4", width=4, height=3, bg="white",
                                      command=lambda: self.set(4))
        self.controls[14].grid(row=2, column=19)
        self.controls[15] = tk.Button(self.root, text="5", width=4, height=3, bg="white",
                                      command=lambda: self.set(5))
        self.controls[15].grid(row=3, column=15)
        self.controls[16] = tk.Button(self.root, text="6", width=4, height=3, bg="white",
                                      command=lambda: self.set(6))
        self.controls[16].grid(row=3, column=16)
        self.controls[17] = tk.Button(self.root, text="7", width=4, height=3, bg="white",
                                      command=lambda: self.set(7))
        self.controls[17].grid(row=3, column=17)
        self.controls[18] = tk.Button(self.root, text="8", width=4, height=3, bg="white",
                                      command=lambda: self.set(8))
        self.controls[18].grid(row=3, column=18)
        self.controls[19] = tk.Button(self.root, text="9", width=4, height=3, bg="white",
                                      command=lambda: self.set(9))
        self.controls[19].grid(row=3, column=19)
        self.controls[20] = tk.Button(self.root, text="Learn", width=4, height=3, bg="white",
                                      command=lambda: self.learn())
        self.controls[20].grid(row=4, column=15)
        self.controls[21] = tk.Button(self.root, text="Check", width=4, height=3, bg="white",
                                      command=lambda: self.check())
        self.controls[21].grid(row=4, column=16)
        self.controls[22] = tk.Button(self.root, text="", width=4, height=3, bg="white")
        self.controls[22].grid(row=4, column=17)
        self.controls[23] = tk.Button(self.root, text="Save", width=4, height=3, bg="white",
                                      command=lambda: self.save())
        self.controls[23].grid(row=4, column=18)
        self.controls[24] = tk.Button(self.root, text="Load", width=4, height=3, bg="white",
                                      command=lambda: self.load())
        self.controls[24].grid(row=4, column=19)
        self.controls[25] = tk.Button(self.root, text="Tran", width=4, height=3, bg="white",
                                      command=lambda: self.move('Tran'))
        self.controls[25].grid(row=5, column=15)
        self.controls[26] = tk.Button(self.root, text="Rota", width=4, height=3, bg="white",
                                      command=lambda: self.move('Rota'))
        self.controls[26].grid(row=5, column=16)

    def _changeOutput(self):
        for i in self.labels:
            self.labels[i].destroy()

        for i in range(10):
            self.labels[i] = tk.Label(
                master=self.root,
                text="{}={:.15f}".format(i, self.probability[i])
            )
            self.labels[i].grid(column=20, row=i, sticky="n")

    def change(self, x, y):
        if self.array[x, y] == 0:
            self.buttons[x, y].configure(bg="green")
            self.array[x, y] = 1
        else:
            self.buttons[x, y].configure(bg="red")
            self.array[x, y] = 0
        self.check()

    def color(self):
        for j in range(self.cols):
            for i in range(self.rows):
                if self.array[i, j] == 0:
                    self.buttons[i, j].configure(bg="red")
                else:
                    self.buttons[i, j].configure(bg="green")

    def clear(self):
        for j in range(self.cols):
            for i in range(self.rows):
                self.array[i, j] = 0
        self.color()

    def move(self, direction):
        if direction == 'Up':
            self.array = np.vstack((self.array[1:, :], self.array[0, :]))
        if direction == 'Down':
            self.array = np.vstack((self.array[len(self.array)-1, :], self.array[0:len(self.array)-1, :]))
        if direction == 'Left':
            self.array = self.array.T
            self.array = np.vstack((self.array[1:, :], self.array[0, :]))
            self.array = self.array.T
        if direction == 'Right':
            self.array = self.array.T
            self.array = np.vstack((self.array[len(self.array)-1, :], self.array[0:len(self.array)-1, :]))
            self.array = self.array.T
        if direction == 'Hori':
            self.array = self.array[::-1]
        if direction == 'Vert':
            self.array = self.array.T[::-1].T
        if direction == 'Tran':
            self.array = self.array.T
        if direction == 'Rota':
            self.array = np.rot90(self.array)
        self.color()
        self.check()

    def neg(self):
        for j in range(self.cols):
            for i in range(self.rows):
                self.array[i, j] = 1.0 - self.array[i, j]
        self.color()
        self.check()

    def rand(self):
        pickX = random.randint(0, self.cols - 1)
        pickY = random.randint(0, self.rows - 1)
        self.change(pickY, pickX)
        self.check()

    def set(self, x):
        self.array = np.array(number[x])
        self.color()
        self.check()

    def learn(self):
        for i in range(10):
            self.adalines[i] = AdaLine(self.input_size * self.input_size, self.learning_rate, self.iterations, str(i))
            labels = np.zeros(10)
            labels[0:] = -1
            labels[i] = 1
            self.adalines[i].train(self.training_data, labels)

    def check(self):
        values = [[] for _ in range(10)]
        for i in range(10):
            values[i] = self.adalines[i].predict(np.ravel(self.array))
        for i in range(10):
            self.probability[i] = values[i]
        self._changeOutput()
        check = ""
        m = max(values)
        check = str([i for i, j in enumerate(values) if m == j])
        self.controls[22].configure(text=check)

    def save(self):
        save = self.adalines[0].weights
        for i in range(1, 10):
            save = np.vstack((save, self.adalines[i].weights))
        np.savetxt("weights.txt", save)

    def load(self):
        load = np.loadtxt("weights.txt")
        for i, j in zip(load, range(10)):
            self.adalines[j].weights = i.copy()


