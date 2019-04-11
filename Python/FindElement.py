## Dawid Sikorski ##
def findKthelement(l,k):
    if len(l) == 1 :
        return l[0]
    piwot = l[0]
    pozycja = 1
    for i in range(1, len(l)) :
        if l[i] < piwot :
            l[i],l[pozycja] = l[pozycja],l[i]
            pozycja = pozycja + 1
    l[0],l[pozycja - 1] = l[pozycja - 1],l[0]
    if pozycja > k :
        return findKthelement(l[:pozycja], k)
    else :
        return findKthelement(l[pozycja:], k - pozycja)
tab = [20,2,20,7,16,19,4,7,7,15,1,2,17,4,15,3,2,8,3,12]
# Posortowana
# [1,2,2,2,3,3,4,4,7,7,7,8,12,15,15,16,17,19,20,20]
print findKthelement(tab, 19)