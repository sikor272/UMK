import numpy as np
from ZadanieRobot.Point import Point


class Examples(object):

    def __init__(self, arm_length=10, center=Point(0, 0)):
        self.arm_length = arm_length
        self.center = center
        self.input = []
        self.output = []

    def generate(self, number_of_examples):
        for i in range(number_of_examples):
            point = self.generate_point()
            self.input.append([point.x, point.y])
        return self.input, self.output

    def generate_point(self):
        alpha = np.random.random() * np.pi
        beta = np.random.random() * np.pi
        self.output.append([alpha, beta])
        temp_point = self.translate(self.center, alpha)
        final_point = self.translate(temp_point, np.pi - beta + alpha)
        return final_point

    def translate(self, center, angle):
        return Point(center.x + self.arm_length * np.sin(angle), center.y - self.arm_length * np.cos(angle))
