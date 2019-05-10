import math
import random

def monteCarlo(f,a,b,n):
    point = []
    for x in range(n):
        point.append(random.uniform(a,b))
    point.sort()
    value = 0
    for i in range(n-1):
        value = value + f(point[i])*(point[i]-point[i-1])
    return value

def f1(x):
    return x
def f2(x):
    return math.sin(x)
def f3(x):
    return math.sqrt(1 - x**2)
print "Calka f(x) = x dla x e (0,10)"
print monteCarlo(f1,0,10,100000)
print "Calka f(x) = sin(x) dla x e (0,PI)"
print monteCarlo(f2,0,math.pi,100000)
print "Calka f(x) = (1 - x^2)^(1/2) dla x e (-1,1)"
print monteCarlo(f3,-1,1,100000)
print "Calka f(x) = x^2 - 9 * x + 18 dla x e (-10,10)"
print monteCarlo(lambda x: x**2 - 9 * x + 18,-10,10,100000)
A = [1,2,3,4]
