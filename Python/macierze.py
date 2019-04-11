plik = open('daneA.txt','r')
plik2 = open('daneB.txt','r')
A = plik.readlines()
B = plik2.readlines()
plik.close()
plik2.close()

A = [w.split() for w in A]
B = [w.split() for w in B]

C = [[] for i in range(len(A))]
print C
def mnozeniemacierzy(A,B):
    for i in range(len(A)) :
        for j in range(len(B[0])):
            d = []
            for k in range(len(B)):
                a = A[i][k]
                b = B[k][j]
                c = float(a)*float(b)
                d.append(c);
            print d
            C[i].append(reduce(lambda x,y:x+y,d));
    return C
C = mnozeniemacierzy(A,B)
print A
print B
print C


