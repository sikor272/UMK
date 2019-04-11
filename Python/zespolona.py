import math
class LiczbaZespolona:
    real = None
    imagine = None
    def __init__(self, a, b = 0):
        self.real = a
        self.imagine = b
    # Dodawanie
    def __add__(self, other):
        if isinstance(other, LiczbaZespolona) :
            if isinstance(self, LiczbaZespolona) :
                return LiczbaZespolona(self.real + other.real, self.imagine + other.imagine)
            else :
                return LiczbaZespolona(self + other.real, other.imagine)
        else :
            return  LiczbaZespolona(self.real + other, self.imagine)
    # Odejmowanie
    def __sub__(self, other):
        if isinstance(other, LiczbaZespolona) :
            if isinstance(self, LiczbaZespolona):
                return LiczbaZespolona(self.real - other.real, self.imagine - other.imagine)
            else :
                return LiczbaZespolona(self - other.real, other.imagine)
        else :
            return LiczbaZespolona(self.real - other.real, self.imagine)
    # Dzielenie
    def __div__(self, other):
        if isinstance(other, LiczbaZespolona) :
            if isinstance(self, LiczbaZespolona) :
                return LiczbaZespolona((self.real * other.real + self.imagine * other.imagine) / (
                            other.real * other.real + other.imagine * other.imagine),
                                       (self.imagine * other.real - self.real * other.imagine) / (
                                                   other.real * other.real + other.imagine * other.imagine))
            else :
                return LiczbaZespolona(self * other.real / ( other.real * other.real + other.imagine * other.imagine),
                                       -self * other.imagine / ( other.real * other.real + other.imagine * other.imagine))
        else :
            return LiczbaZespolona(self.real / other, self.imagine / other)
    # Mnozenie
    def __mul__(self, other):
        if isinstance(other, LiczbaZespolona) :
            return LiczbaZespolona(self.real * other.real - self.imagine * other.imagine, self.real * other.imagine + self.imagine * other.real)
        else :
            return LiczbaZespolona(self.real * other, self.imagine * other)
    # Negacja
    def __neg__(self):
        return LiczbaZespolona(-self.real, -self.imagine)
    # Modul
    def modul(self):
        return math.sqrt(self.real * self.real + self.imagine * self.imagine)
    # Wyspisywanie
    def __str__(self):
        if self.imagine == 0:
            return '(%r)' % (self.real)
        else :
            if self.real == 0 :
                if self.imagine == 1 :
                    return '(i)'
                else :
                    if self.imagine == -1 :
                        return  '(-i)'
                    else :
                        return '(%ri)' % (self.imagine)
            else :
                return '(%r + %ri)' % (self.real, self.imagine)
    def solveSquale(self, a, b, c):
        if not isinstance(a, LiczbaZespolona) :
            a = LiczbaZespolona(a)
        if not isinstance(b, LiczbaZespolona) :
            b = LiczbaZespolona(b)
        if not isinstance(c, LiczbaZespolona) :
            c = LiczbaZespolona(c)
        delta = b * b - a * c * 4
        if delta.real == 0 :
			if delta.imagine == 0 :
					x1 = -b / (a * 2)
					return x1, x1
        z = delta.modul()
        kat = math.acos(delta.real/z)
        r1 = LiczbaZespolona(math.cos(kat / 2), math.sin(kat / 2))
        r1 = r1 * math.sqrt(z)
        x1 = (-b + r1) / (a * 2);
        x2 = (-b - r1) / (a * 2);
        x1.real = round(x1.real, 10)
        x1.imagine = round(x1.imagine, 10)
        x2.real = round(x2.real, 10)
        x2.imagine = round(x2.imagine, 10)
        return x1, x2

a = LiczbaZespolona(0, 1)
b = LiczbaZespolona(0, 1)
c = LiczbaZespolona(0, -2)

print "Rozwiazanie dla :",\
    a,\
    "x^2 +",\
    b,\
    "x +",\
    c

a,b = c.solveSquale(a, b, c)
print a,
print "oraz",
print b

a = LiczbaZespolona(0, 1)
b = LiczbaZespolona(2, 4)
c = LiczbaZespolona(16, 8)

print "Rozwiazanie dla :",\
    a,\
    "x^2 +",\
    b,\
    "x +",\
    c

a,b = c.solveSquale(a, b, c)
print a,
print "oraz",
print b