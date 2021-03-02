from ZadanieAdaLine.Gui import Window
from ZadanieAdaLine.Input import *
import numpy as np

training_data = [np.ravel(x) for x in number]
input_size = 9
window = Window(9, 9, input_size, training_data, 0.001, 1000)
window.show()
