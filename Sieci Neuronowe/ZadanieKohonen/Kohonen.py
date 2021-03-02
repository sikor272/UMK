import numpy as np


class Kohonen(object):
    def __init__(self, h, w, dim, sigma=0.9, alpha0=0.3, beta=100 * 25):
        self.h = h
        self.w = w
        self.dim = dim
        self.shape = (h, w, dim)
        self.som = np.random.random(self.shape)
        #self.som = np.zeros(self.shape)
        self.sigma = sigma
        self.alpha0 = alpha0
        self.data = []
        self.beta = beta

    def train(self, steps, data):
        self.data = data.copy()
        for t in range(steps, steps + 25):
            idx = np.random.choice(range(len(self.data)))
            best_neuron = self.find_best_neuron(self.data[idx])
            self.update_som(best_neuron, self.data[idx], t)

    def find_best_neuron(self, input_vector):
        list_neurons = []
        for x in range(self.shape[0]):
            for y in range(self.shape[1]):
                dist = np.linalg.norm(input_vector - self.som[x, y])
                list_neurons.append(((x, y), dist))
        list_neurons.sort(key=lambda param: param[1])
        return list_neurons[0][0]

    def update_som(self, bn, dp, t):
        for x in range(self.shape[0]):
            for y in range(self.shape[1]):
                dist_to_bn = np.linalg.norm(np.array(bn) - np.array([x, y]))
                self.update_cell((x, y), dp, t, dist_to_bn)

    def update_cell(self, cell, dp, t, dist_to_bn):
        self.som[cell] += self.alpha(t) * self.G(dist_to_bn) * (dp - self.som[cell])

    def alpha(self, t):
        return self.alpha0 * np.exp(-(t / self.beta))

    def G(self, rho):
        # return np.exp(-rho ** 2 / (2 * self.sigma ** 2))
        return 2 * np.exp(-rho ** 2 / 2 * self.sigma ** 2) - np.exp(
            -rho ** 2 / 2 * (self.sigma * 2) ** 2)
