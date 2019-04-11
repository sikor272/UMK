# Zadanie 3
plik = open('odczyt.txt','r')
dane = plik.readlines()
plik.close()

wieksza = lambda x,y : x if x > y else y
dane = [w.split() for w in dane]

plik2 = open('zapis.txt','w')
for (x,y) in dane :
    plik2.write(str(wieksza(int(x),int(y))) + '\n')
plik2.close()