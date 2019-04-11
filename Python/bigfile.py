import random
def otworz(nazwa,n,k):
    plik = open(nazwa,'r')
    j = 0
    m = 0
    for line in plik :
        r = random.random()
        if ((k - j) / (n - m)) > r :
            j += 1
            print line
        m += 1;
nazwa = raw_input("Podaj nazwe: ")
ilosc = input("Ilosc linii: ")
ziarno = input("Ilosc seed: ")
otworz(nazwa,ilosc,float(ziarno))