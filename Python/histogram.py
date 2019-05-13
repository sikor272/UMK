from matplotlib.image import imread
import numpy
import matplotlib.pyplot as plot
picture =  numpy.asarray(imread("misie.jpg"), dtype="int32")
r = [0 for i in range(256)]
g = [0 for i in range(256)]
b = [0 for i in range(256)]
s = [0 for i in range(256)]
for i in picture:
    for j in i:
        x = 0.299 * j[0] + 0.587 * j[1] + 0.114 * j[2]
        x = int(x)
        r[j[0]] +=1
        g[j[1]] +=1
        b[j[2]] +=1
        s[x] += 1
def kolor(r,g,b):
    return '#%02x%02x%02x' % (r,g,b)
for i in range(256):
    plot.bar(i, s[i], color = kolor(0,0,0), edgecolor = kolor(0,0,0), alpha = 0.8)
    plot.bar(i, r[i], color = kolor(i,0,0), edgecolor = kolor(i,0,0), alpha = 0.4)
    plot.bar(i, g[i], color = kolor(0,i,0), edgecolor = kolor(0,i,0), alpha = 0.4)
    plot.bar(i, b[i], color = kolor(0,0,i), edgecolor = kolor(0,0,i), alpha = 0.4)

plot.xlabel("Kolor")
plot.ylabel("Ilosc")
plot.title("Histogram")
plot.show()
