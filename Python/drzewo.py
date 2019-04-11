class node:
    value = None
    left = None
    right = None
    def __init__(self, value):
        self.value = value
    def put(self, next):
        if next < self.value :
            if self.left is None : self.left = node(next)
            else : self.left.put(next)
        else :
            if self.right is None : self.right = node(next)
            else: self.right.put(next)
    def get(self):
        if self.left is not None : l = self.left.get()
        else : l = []
        v = self.value
        if self.right is not None : r = self.right.get()
        else : r = []
        l.append(v)
        return l + r

dane = [13, 3, 17, 1, 5, 19, 15, 0, 2, 4, 6, 14, 16, 18, 20]
tree = node(dane[0])
for i in range(1,len(dane)):
    tree.put(dane[i])
sort = tree.get()
for i in sort :
    print i,