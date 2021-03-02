import numpy as np
import random
import matplotlib.pyplot as plt

class Perceptron(object):
    def __init__(self, no_of_inputs, learning_rate=0.01, iterations=100):
        self.iterations = iterations
        self.learning_rate = learning_rate
        self.no_of_inputs = no_of_inputs
        self.weights = (np.random.rand(self.no_of_inputs + 1) - 0.5) / 1000  # ZADANIE DOMOWE 1 - losowosc


    def trainSPLA(self, training_data, labels):
        train = True
        for _ in range(self.iterations):
            if not train:# ZADANIE DOMOWE 3 - warunek stopu
                return
            data = list(zip(training_data, labels))
            random.shuffle(data)
            for input, label in data:  # ZADANIE DOMOWE 2 - losowosc
                choosed_input = random.choice(input)  # ZADANIE DOMOWE - zaburzenie wejscia
                prediction = self.predict(choosed_input)
                if label - prediction != 0:
                    train = True
                    self.weights[1:] += self.learning_rate * (label - prediction) * choosed_input
                    self.weights[0] += self.learning_rate * (label - prediction)
            # h(x) = (ax + b) % m

    def trainPLA(self, training_data, labels):  # ZADANIE DOMOWE 4 - PLA + RPLA
        total_alive = 0
        alive = 0
        weights_alive = self.weights.copy()
        for i in range(self.iterations):
            input, label = random.choice(list(zip(training_data, labels)))
            choosed_input = random.choice(input)
            prediction = self.predict(choosed_input)
            if label - prediction != 0:
                if alive > total_alive:
                    weights_alive = self.weights.copy()
                    total_alive = alive
                    if self.iterations - i < total_alive:  # ZADANIE DOMOWE 3 - warunek stopu
                        self.weights = weights_alive.copy()
                        return
                alive = 0
                self.weights[1:] += self.learning_rate * (label - prediction) * choosed_input
                self.weights[0] += self.learning_rate * (label - prediction)
            else:
                alive += 1
        if alive > total_alive:
            weights_alive = self.weights.copy()
        self.weights = weights_alive.copy()

    def trainRPLA(self, training_data, labels):  # ZADANIE DOMOWE 4 - PLA + RPLA
        total_alive = 0
        alive = 0
        weights_alive = self.weights.copy()
        total_ok = 0
        for _ in range(self.iterations):
            input, label = random.choice(list(zip(training_data, labels)))
            choosed_input = random.choice(input)
            prediction = self.predict(choosed_input)
            if label - prediction != 0:
                if alive > total_alive:
                    ok = self.sum_predict(training_data, labels)
                    if ok > total_ok:
                        weights_alive = self.weights.copy()
                        total_alive = alive
                        total_ok = ok
                        if ok == sum(len(i) for i in training_data):  # ZADANIE DOMOWE 3 - warunek stopu
                            self.weights = weights_alive.copy()
                            return
                alive = 0
                self.weights[1:] += self.learning_rate * (label - prediction) * choosed_input
                self.weights[0] += self.learning_rate * (label - prediction)
            else:
                alive += 1
        if alive > total_alive:
            ok = self.sum_predict(training_data, labels)
            if ok > total_ok:
                weights_alive = self.weights.copy()
        self.weights = weights_alive.copy()

    def sum_predict(self, data, labels):
        sum = 0
        for input, label in zip(data, labels):
            for i in input:
                prediction = self.predict(i)
                if label - prediction == 0:
                    sum += 1
        return sum

    def predict(self, input):
        if np.dot(input, self.weights[1:]) + self.weights[0] > 0:
            return 1
        else:
            return 0

    def noise(self, input):
        pick = random.randint(0, len(input) - 1)
        input[pick] = 1.0 - input[pick]
        return input

    def saveWeights(self, name):
        save = self.weights[1:]
        plt.imshow(np.reshape(save, newshape=(5, 5)))
        plt.savefig('./weights/perceptron' + name + '.pdf')
        plt.close()