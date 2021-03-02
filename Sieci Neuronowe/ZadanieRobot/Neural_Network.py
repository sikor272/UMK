import numpy as np


class Neural_Network(object):

    def __init__(self, layers=[2, 10, 20, 10, 2], eta=0.01):
        self.layers = layers.copy()
        self.eta = eta
        self.errors = []
        self.weights = []
        self.y = []
        self.a = []
        self.epsilon = []
        self.delta = []
        for i in range(len(self.layers) - 1):
            self.weights.append((np.random.randn(self.layers[i], self.layers[i + 1]) - 0.5))

    def sigmoid(self, x):
        return 1. / (1 + np.exp(-x))

    def sigmoid_derivative(self, s):
        return s * (1 - s)

    def forward(self, x):
        self.y = []
        self.a = []
        self.y.append(np.array(x).copy())
        for i in range(len(self.layers) - 1):
            self.a.append(np.dot(self.y[i], self.weights[i]))
            self.y.append(self.sigmoid(self.a[i]))
        return self.y[len(self.y) - 1]

    def backward(self, output):
        self.epsilon = []
        self.delta = []
        self.epsilon.append(output - self.y[len(self.y) - 1])
        i = 0
        for i in range(len(self.layers) - 2):
            self.delta.append((self.epsilon[i] * self.sigmoid_derivative(self.y[len(self.y) - 1 - i]).copy()))
            self.epsilon.append((self.delta[i].dot(self.weights[len(self.weights) - 1 - i].T)).copy())
        self.delta.append((self.epsilon[(i + 1)] * self.sigmoid_derivative(self.y[len(self.y) - 1 - (i + 1)])).copy())
        self.delta = self.delta[::-1].copy()
        for i in range(len(self.layers) - 1):
            self.weights[i] += self.eta * self.y[i].T.dot(self.delta[i])

    def train(self, x, y):
        self.forward(x)
        self.backward(y)
        self.errors.append(np.mean(np.square(y - self.y[len(self.y) - 1])))
