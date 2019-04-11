
z = []
for i in range(1,101):
    z += [i**2]
print z

z = [n**2 for n in range(1,101)]
print z

xr = [(n**2,n**2 % 11) for n in range(1,101)]
print xr

br = [(n**2,n**2 % 11) for n in range(1,101) if n**2%11==0]
print br

podzielne = [l for (l,r) in xr if r == 0]
print podzielne
c = [0,1,2,3,4]
c4 = [4*n for n in c]
d = [6,7,8,9,0]
suma = [n + m for (n,m) in zip(c,d)]
print suma
tekst = 'In the Land of Mordor where the Shadows lie'
p = tekst.split()
print p
para = [(w,len(w)) for w in p if len(w) > 3]
print para
def mul4(arg):
    return arg * 4;
for i in map(mul4,c):
    print i,
print ""
for i in map(lambda x: x*4,c):
    print i,
print ""

for i in map(lambda x:x[0]-x[1],br):
    print i,
print ""
bin = map(lambda x:x%3,z)
print bin
siedem = filter(lambda x:x%7 == 0,z)
print siedem
osiem = reduce(lambda x,y:x+y,siedem)
print osiem
litery = [(i,1) for i in tekst]
def pomocnicza(co):
    if co[0] == 'a' or co[0] == 'A':
        return True
    return False
dane = filter(pomocnicza, litery)
print reduce(lambda x,y:x[1]+y[1], dane)
print reduce(lambda x,y:x+y,list(map(lambda x:1 if x[0]=='a' else 0,litery)))

#plik = open('dozapisu.txt','w')
#for i in tekst:
#    plik.write(str(i) + '\n')
#plik.close()
#plik2 = open('dozapisu.txt')
#print plik2.readlines()
#plik2.close()