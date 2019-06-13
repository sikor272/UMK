import numpy as np
class drzewo:
    def __init__(self):
        self.value = 0
    def potomek(self):
        self.dzieci = [drzewo() for i in range(16)]
    def start(self):
        self.potomek()
        for i in range(16):
            self.dzieci[i].potomek()
            for j in range(16):
                self.dzieci[i].dzieci[j].potomek()
                for k in range(16):
                    self.dzieci[i].dzieci[j].dzieci[k].potomek()
    def dodaj(self,a,b,c,d):
        self.dzieci[a].value += 1
        self.dzieci[a].dzieci[b].value += 1
        self.dzieci[a].dzieci[b].dzieci[c].value += 1
        self.dzieci[a].dzieci[b].dzieci[c].dzieci[d].value += 1
    def mniejsze(self,a):
        a = '{0:04x}'.format(a)
        b,c,d,a = int(a[1],16),int(a[2],16),int(a[3],16),int(a[0],16)
        suma = 0
        for i in range(a):
            suma += self.dzieci[i].value
        for i in range(b):
            suma += self.dzieci[a].dzieci[i].value
        for i in range(c):
            suma += self.dzieci[a].dzieci[b].dzieci[i].value
        for i in range(d):
            suma += self.dzieci[a].dzieci[b].dzieci[c].dzieci[i].value
        return suma

arr = np.random.randint(0, 2**16-1, (1000, 500), dtype=np.uint16)
wynik = [['{0:04x}'.format(j) for j in i] for i in arr]
korzen = drzewo()
korzen.start()
for i in wynik:
    for j in i:
        korzen.dodaj(int(j[0],16),int(j[1],16),int(j[2],16),int(j[3],16))
print korzen.mniejsze(0x1f5c)