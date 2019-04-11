def psi(funkcja,wartosc):
    return lambda x : funkcja(x,wartosc)
psiv2 = psi(lambda x,y:x<y,5)
print psiv2(4)
print psiv2(6)