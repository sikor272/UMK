import random
class Dispatcher:
    def __init__(self,k):
        self.n = reduce(lambda x,y:x+y,k)
        self.k = [i for i in k]
        self.d = [0 for i in self.k]
        self.generate()
    def getBucket(self):
        r = random.random()
        i = 0
        k = self.k[0]
        while k < (r * self.n):
            i += 1
            k += self.k[i]
        self.k[i] -= 1
        self.n -= 1
        return i
    def generate(self):
        for i in range(self.n):
            self.d[self.getBucket()] += 1
    def dispatch(self):
        lista = [[] for i in self.k]
        self.k = [i for i in self.d]
        self.n = reduce(lambda x,y:x+y,self.k)
        for i in range(self.n):
            lista[self.getBucket()].append(i)
        return lista

k = [(random.randint(1,10)) for i in range(random.randint(20,100))]
x = Dispatcher(k)
y = x.dispatch()
for i in y:
    print i