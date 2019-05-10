import numpy
import matplotlib.pyplot

def pierwsze(n):
    tab = [1 for i in range(n)];
    tab[0] = 0;
    tab[1] = 0;
    for i in range(2,n):
        if tab[i] == 1:
            for j in range(i**2,n,i):
                tab[j] = 0
    return [i for i in range(2,n) if tab[i] == 1]

def generator(polowa):

    rozmiar = (2*(polowa-1)+1)**2
    wielkosc = 2*polowa+1
    primes = pierwsze(rozmiar)

    # pomocnicza do generowania
    pomocnicza = numpy.zeros((wielkosc,wielkosc))
    # spirala
    wyjsciowa = numpy.zeros((wielkosc,wielkosc))

    # zmienne startowe
    x = polowa+1
    y = polowa
    pomocnicza[y,x] = 1
    wyjsciowa[y,x] = 1

    # pozycja startowa
    pomocnicza[y,x-1] = 1
    wyjsciowa[y,x-1] = 0
    # generujemy spirale
    for i in range(3,rozmiar + 1):
        if (pomocnicza[y+1,x] == 0) and (pomocnicza[y,x+1] == 1):
            # W dol
            y = y + 1
            pomocnicza[y,x] = 1
            wyjsciowa[y,x] = (i in primes)
        elif (pomocnicza[y,x-1] == 0) and (pomocnicza[y+1,x] == 1):
            # W lewo
            x = x - 1
            pomocnicza[y,x] = 1
            wyjsciowa[y,x] = (i in primes)
        elif (pomocnicza[y-1,x] == 0) and (pomocnicza[y,x-1] == 1):
            # W gore
            y = y - 1
            pomocnicza[y,x] = 1
            wyjsciowa[y,x] = (i in primes)
        else:
            # W prawo
            x = x + 1
            pomocnicza[y,x] = 1
            wyjsciowa[y,x] = (i in primes)
    return wyjsciowa


Ulam = generator(150)


matplotlib.pyplot.axis('off')
matplotlib.pyplot.imshow(Ulam,cmap=matplotlib.cm.binary)
matplotlib.pyplot.show()