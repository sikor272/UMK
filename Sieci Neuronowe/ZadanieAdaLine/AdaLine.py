import numpy as np
import matplotlib.pyplot as plt
import random


def fourier_transform(x):
    a = np.abs(np.fft.fft(x))
    a[0] = 0
    return a / np.max(a)


class AdaLine(object):
    def __init__(self, no_of_input, learning_rate=0.01, iterations=100, name='0', biased=True):
        self.no_of_input = no_of_input
        self.learning_rate = learning_rate
        self.iterations = iterations
        self.biased = biased
        if self.biased:
            self.weights = (np.random.random(2 * self.no_of_input + 1) - 0.5) / 1000
        else:
            self.weights = (np.random.random(2 * self.no_of_input) - 0.5) / 1000
        self.errors = []
        self.name = name

    def train(self, training_data_x, training_data_y):
        training_data_x = [self.normalization(i) for i in
                           training_data_x]  # Zmienic wejsice na przedzial 0.1 , 0.9 zeby dzialalo na innej funkcji aktywacji
        training_data_y = self.normalization(training_data_y)
        # jesli uzywamy innej aktywacji to
        training_data_x = [i * 0.8 + 0.1 for i in training_data_x]
        training_data_y = training_data_y * 0.8 + 0.1
        for _ in range(self.iterations):
            e = 0
            data = list(zip(training_data_x, training_data_y))
            np.random.shuffle(data)
            for x, y in data:
                x = self.noise(x.copy())
                x = np.concatenate([x, fourier_transform(x)])
                output = self.output(x)
                if self.biased:
                    self.weights[1:] += self.learning_rate * (y - output) * x * output * (
                                1 - output)  # pochodna dla innej aktywacji
                    self.weights[0] += self.learning_rate * (y - output) * output * (1 - output)
                else:
                    self.weights += self.learning_rate * (y - output) * x * output * (1 - output)
                e += 0.5 * ((y - output) ** 2)
            self.errors.append(e)
        plt.plot(range(len(self.errors)), self.errors, label="{}".format(self.name))
        plt.legend(loc="upper right")
        plt.savefig('errors.pdf')

    def activation(self, x):
        # return x
        return 1 / (1 + np.exp(-x))  # inna funkcja aktywacji

    def noise(self, x):
        pick = random.randint(0, len(x) - 1)
        x[pick] = 1.0 - x[pick]
        return x

    def output(self, input):
        if self.biased:
            return self.activation(np.dot(self.weights[1:], input) + self.weights[0])
        else:
            return self.activation(np.dot(self.weights, input))

    def predict(self, x):
        x = self.normalization(x)
        if self.biased:
            return self.activation(np.dot(self.weights[1:],
                                          np.concatenate([x, fourier_transform(x)])) + self.weights[0])
        else:
            return self.activation(np.dot(self.weights, np.concatenate([x, fourier_transform(x)])))

    def standardization(self, i):
        return (i - np.mean(i)) / np.std(i)

    def normalization(self, i):
        return (i - min(i)) / (max(i) - min(i))
