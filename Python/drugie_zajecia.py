class A:
    x = 7
    def __init__(self, a):
        self.x = a
    def f(self):
        print "A"
    def g(self):
        self.f()
    def w(self):
        print self.x
class B(A):
    y = 1
class C:
    def f(self):
        print "C"
class D(B,C):
    z = 1
def xyz():
    print "XYZ"

d = D(10)
d.w()
d.g()
d.f = xyz
d.g()
d.x = 17
d.w()