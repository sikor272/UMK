import random
def otworz(nazwa,n,k):
    plik = open(nazwa,'r')
    for line in plik :
        r = random.random()
        if (k / n) > r :
            k = k - 1
            print line,
        n = n - 1
nazwa = raw_input("Podaj nazwe: ")
ilosc = input("Ilosc linii: ")
ziarno = input("Ilosc seed: ")
otworz(nazwa,ilosc,float(ziarno))
