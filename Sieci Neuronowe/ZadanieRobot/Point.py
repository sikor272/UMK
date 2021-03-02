class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __truediv__(self, other):
        return Point(self.x / other, self.y / other)

    def __mul__(self, other):
        return Point(self.x * other, self.y * other)

    def __add__(self, other):
        if isinstance(other, Point):
            return Point(self.x + other.x, self.y + other.y)
        if isinstance(other, float):
            return Point(self.x + other, self.y + other)
