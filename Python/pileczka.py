import math
h = input("Podaj wysokosc do uderzenia(m): ")
a = 9.8
l = input("Podaj odleglosc do upadku(m): ")
tx = math.sqrt(2*l/a)
vz = math.sqrt(l*a/2)
if vz**2 - 2*a*h < 0 :
    print "Wprowadzono bledne dane!"
else :
    vo = math.sqrt(vz**2 - 2*a*h);
    print "Predkosc poczatkowa:",\
            vo,\
            "m/s"