from ZadaniePerceptron.Gui import Window
from ZadaniePerceptron.Input import *
import numpy as np

training_data = [[np.ravel(y) for y in x] for x in number]
input_size = 5
window = Window(5, 5, input_size, training_data, 0.01, 10000, 'RPLA')
for i in range(10):
    window.perceptrons[i].saveWeights(str(i))
