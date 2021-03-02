import numpy as np
from PIL import Image as img_reader
from ZadanieHopfield.HopfieldNetwork import HopfieldNetwork
from tkinter import *
from os import listdir
from os.path import isfile, join
from tqdm import tqdm


class Gui(object):
    def __init__(self, N=100):
        self.N = N
        self.network = HopfieldNetwork(self.N * self.N)
        self.data = self.read_images()
        self.width = 400
        self.height = 400
        self.root = Tk()
        self.buttons = {}
        self.controls = {}
        self.array = np.zeros((self.N, self.N)) - 1
        self.build_buttons()
        self.build_example()
        self.canvas = Canvas(self.root, width=self.width, height=self.height, highlightthickness=1,
                             highlightbackground="black")
        self.canvas.grid(row=0, column=0, columnspan=100)
        self.canvas.bind("<Button-1>", self.callback)
        self.canvas.bind("<B1-Motion>", self.callback)
        self.clear()
        self.root.mainloop()

    def train(self):
        self.network = HopfieldNetwork(self.N * self.N)
        training_data = [np.reshape(i, (self.N * self.N)) for i in self.data]
        self.network.training(training_data)
        self.network.plot_weights()

    def little(self):
        test_input = np.reshape(self.array, (self.N * self.N))
        test_output = self.network.run_dynamics(test_input, 'little')
        self.array = np.reshape(test_output, (self.N, self.N))
        self.color()

    def hamming(self):
        test_input = np.reshape(self.array, (self.N * self.N))
        training_data = [np.reshape(i, (self.N * self.N)) for i in self.data]
        test_output = self.network.hamming(test_input, training_data)
        self.array = np.reshape(test_output, (self.N, self.N))
        self.color()

    def glauber(self):
        test_input = np.reshape(self.array, (self.N * self.N))
        test_output = self.network.run_dynamics(test_input)
        self.array = np.reshape(test_output, (self.N, self.N))
        self.color()

    def callback(self, event):
        if event.x >= self.width:
            return
        if event.y >= self.height:
            return
        if self.array[int(event.x / (self.width / self.N)), int(event.y / (self.width / self.N))] == -1:
            color = "black"
            self.array[int(event.x / (self.width / self.N)), int(event.y / (self.width / self.N))] = 1
        else:
            color = "white"
            self.array[int(event.x / (self.width / self.N)), int(event.y / (self.width / self.N))] = -1
        self.draw_point(np.array([int(event.x / (self.width / self.N)), int(event.y / (self.width / self.N))]), color)

    def draw_point(self, point, color):
        self.canvas.create_rectangle(point[0] * self.width / self.N, point[1] * self.width / self.N,
                                     point[0] * self.width / self.N + self.width / self.N,
                                     point[1] * self.width / self.N + self.width / self.N, fill=color)

    def build_buttons(self):
        self.controls[0] = Button(self.root, text="Clear", width=4, height=3, bg="white",
                                  command=lambda: self.clear())
        self.controls[0].grid(row=self.N + 1, column=self.N + 1 + 1)
        self.controls[1] = Button(self.root, text="^", width=4, height=3, bg="white",
                                  command=lambda: self.move('Up'))
        self.controls[1].grid(row=self.N + 1, column=self.N + 1 + 2)
        self.controls[2] = Button(self.root, text="Neg", width=4, height=3, bg="white",
                                  command=lambda: self.neg())
        self.controls[2].grid(row=self.N + 1, column=self.N + 1 + 3)
        self.controls[3] = Button(self.root, text="Vert", width=4, height=3, bg="white",
                                  command=lambda: self.move('Vert'))
        self.controls[3].grid(row=self.N + 1, column=self.N + 1 + 4)
        self.controls[4] = Button(self.root, text="Hori", width=4, height=3, bg="white",
                                  command=lambda: self.move('Hori'))
        self.controls[4].grid(row=self.N + 1, column=self.N + 1 + 5)
        self.controls[25] = Button(self.root, text="Tran", width=4, height=3, bg="white",
                                   command=lambda: self.move('Tran'))
        self.controls[25].grid(row=self.N + 1, column=self.N + 1 + 6)
        self.controls[26] = Button(self.root, text="Rota", width=4, height=3, bg="white",
                                   command=lambda: self.move('Rota'))
        self.controls[26].grid(row=self.N + 1, column=self.N + 1 + 7)
        self.controls[27] = Button(self.root, text="Learn", width=4, height=3, bg="white",
                                   command=lambda: self.train())
        self.controls[27].grid(row=self.N + 1, column=self.N + 1 + 9)
        self.controls[28] = Button(self.root, text="Glauber", width=5, height=3, bg="white",
                                   command=lambda: self.glauber())
        self.controls[28].grid(row=self.N + 1, column=self.N + 1 + 10)
        self.controls[29] = Button(self.root, text="Little", width=5, height=3, bg="white",
                                   command=lambda: self.little())
        self.controls[29].grid(row=self.N + 1, column=self.N + 1 + 11)
        self.controls[39] = Button(self.root, text="Hamming", width=7, height=3, bg="white",
                                   command=lambda: self.hamming())
        self.controls[39].grid(row=self.N + 1, column=self.N + 1 + 12)

        self.controls[5] = Button(self.root, text="<", width=4, height=3, bg="white",
                                  command=lambda: self.move('Left'))
        self.controls[5].grid(row=self.N + 2, column=self.N + 1 + 1)
        self.controls[6] = Button(self.root, text="v", width=4, height=3, bg="white",
                                  command=lambda: self.move('Down'))
        self.controls[6].grid(row=self.N + 2, column=self.N + 1 + 2)
        self.controls[7] = Button(self.root, text=">", width=4, height=3, bg="white",
                                  command=lambda: self.move('Right'))
        self.controls[7].grid(row=self.N + 2, column=self.N + 1 + 3)
        self.controls[8] = Button(self.root, text="Rand", width=4, height=3, bg="white",
                                  command=lambda: self.rand())
        self.controls[8].grid(row=self.N + 2, column=self.N + 1 + 4)
        self.controls[9] = Button(self.root, text="Exit", width=4, height=3, bg="white",
                                  command=lambda: self.root.destroy())
        self.controls[9].grid(row=self.N + 2, column=self.N + 1 + 5)

    def build_example(self):
        for i in range(len(self.data)):
            self.controls[i + 9] = Button(self.root, text=str(i), width=4, height=3, bg="white",
                                          command=lambda x=i: self.set(x))
            self.controls[i + 9].grid(row=self.N + 3, column=self.N + 2 + i)

    def rand(self):
        for j in tqdm(range(self.N)):
            for i in range(self.N):
                if np.random.rand() > 0.75:
                    self.array[i, j] *= (-1)
        self.color()

    def color(self):
        self.canvas.delete("all")
        print("\nMalowanie: ")
        for j in tqdm(range(self.N)):
            for i in range(self.N):
                if self.array[i, j] == -1:
                    self.draw_point([i, j], "white")
                else:
                    self.draw_point([i, j], "black")
                self.canvas.update()

    def change(self, x, y):
        if self.array[x, y] == -1:
            self.draw_point([x, y], "black")
            self.array[x, y] = 1
        else:
            self.draw_point([x, y], "white")
            self.array[x, y] = -1

    def read_images(self, ):
        images = [self.__read_image(name) for name in
                  [f for f in listdir("Images") if isfile(join("Images", f))]]
        return images

    def __read_image(self, name):
        image = np.array(img_reader.open('Images/' + name)).reshape(self.N, self.N).T
        points = np.zeros((self.N, self.N)) - 1
        for y in range(len(image)):
            for x in range(len(image[y])):
                if not image[x][y]:
                    points[x][y] = 1
        return points

    def move(self, direction):
        if direction == 'Up':
            self.array = np.vstack((self.array[1:, :], self.array[0, :]))
        if direction == 'Down':
            self.array = np.vstack((self.array[len(self.array) - 1, :], self.array[0:len(self.array) - 1, :]))
        if direction == 'Left':
            self.array = self.array.T
            self.array = np.vstack((self.array[1:, :], self.array[0, :]))
            self.array = self.array.T
        if direction == 'Right':
            self.array = self.array.T
            self.array = np.vstack((self.array[len(self.array) - 1, :], self.array[0:len(self.array) - 1, :]))
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

    def neg(self):
        for j in range(self.N):
            for i in range(self.N):
                self.array[i, j] *= (-1)
        self.color()

    def set(self, x):
        self.array = np.array(self.data[x])
        self.color()

    def clear(self):
        self.array = np.zeros((self.N, self.N)) - 1
        self.color()


gui = Gui()
