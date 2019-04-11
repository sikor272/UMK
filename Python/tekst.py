def wystapienie(tekst,jaka):
    litery = [(i, 1) for i in tekst]
    return reduce(lambda x,y:x+y,list(map(lambda x:1 if x[0] == jaka else 0,litery)))
def slowo(slownik,szukana):
    slownik = [(w,1) for w in slownik]
    return reduce(lambda x, y: x + y, list(map(lambda x: 1 if x[0] == szukana else 0, slownik)))

tekst = "Three Rings for the Elven-kings under the sky, \
Seven for the Dwarf-lords in their halls of stone, \
Nine for Mortal Men doomed to die, \
One for the Dark Lord on his dark throne \
In the Land of Mordor where the Shadows lie. \
One Ring to rule them all, One Ring to find them, \
One Ring to bring them all and in the darkness bind them \
In the Land of Mordor where the Shadows lie.";

# Zadanie 1.a)
print wystapienie(tekst, 'd');

# Zadanie 1.b)
lista = tekst.split();
slowa4 = [w.upper() for w in lista if len(w) <= 4]
print slowa4

# Zadanie 1.c)
wystap = [(w,slowo(lista,w)) for w in lista]
print list(set(wystap))
# Bez wzgledu na wielkosc liter
lista = [w.upper() for w in lista]
wystap = [(w,slowo(lista,w)) for w in lista]
print list(set(wystap))