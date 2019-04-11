from random import seed
from random import randint
def wypisz():
	print "|---+---+---+---+---+---+---+---+---|"
	for i in range(0, 9):
		print "|",
		for j in range(0,9):
			if sudoku[i][j] != 0 :
				print str(sudoku[i][j]) + " |",
			else :
				print "  |",
		print ""
		print "|---+---+---+---+---+---+---+---+---|"

def check(x, y):
	for i in range(0, 9):
		if sudoku[x][i] in mozliwosci[x][y]:
			mozliwosci[x][y].remove(sudoku[x][i])
		if sudoku[i][y] in mozliwosci[x][y]:
			mozliwosci[x][y].remove(sudoku[i][y])
	x1 = x - x % 3;
	y1 = y - y % 3;
	for i in range(0, 3):
		for j in range(0,3):
			if sudoku[i+x1][j+y1] in mozliwosci[x][y]:
				mozliwosci[x][y].remove(sudoku[i+x1][j+y1])
	if len(mozliwosci[x][y]) == 1 :
		sudoku[x][y] = mozliwosci[x][y][0]
		mozliwosci[x][y] = []
		done(x,y)

def done(x,y):
	for i in range(0, 9):
		if sudoku[x][y] in mozliwosci[x][i]:
			mozliwosci[x][i].remove(sudoku[x][y])
			if len(mozliwosci[x][i]) == 1:
				sudoku[x][i] = mozliwosci[x][i][0]
				mozliwosci[x][i] = []
				done(x,i)
		if sudoku[x][y] in mozliwosci[i][y]:
			mozliwosci[i][y].remove(sudoku[x][y])
			if len(mozliwosci[i][y]) == 1:
				sudoku[i][y] = mozliwosci[i][y][0]
				mozliwosci[i][y] = []
				done(i,y)
	x1 = x - x % 3;
	y1 = y - y % 3;
	for i in range(0, 3):
		for j in range(0, 3):
			if sudoku[x][y] in mozliwosci[i+x1][j+y1] :
				mozliwosci[i+x1][j+y1].remove(sudoku[x][y])
				if len(mozliwosci[i+x1][j+y1]) == 1:
					sudoku[i+x1][j+y1] = mozliwosci[i+x1][j+y1][0]
					mozliwosci[i+x1][j+y1] = []
					done(i+x1,j+y1)

def solve():
	for j in range(0,9):
		for i in range(0,9):
			if sudoku[i][j] == 0:
				check(i,j)
			else :
				mozliwosci[i][j] = []
				done(i,j)
def wypelnione():
	for j in range(0, 9):
		for i in range(0, 9):
			if sudoku[i][j] == 0:
				return False
	return True
def minimalny():
	rozmiar = 10
	for j in range(0, 9):
		for i in range(0, 9):
			if len(mozliwosci[j][i]) > 0:
				if len(mozliwosci[j][i]) < rozmiar :
					rozmiar = len(mozliwosci[j][i])
					x,y = j ,i
	if rozmiar < 10 :
		sudoku[x][y] = mozliwosci[x][y][randint(0,len(mozliwosci[x][y]) - 1)]
		mozliwosci[x][y] = []
		done(x,y)
		minimalny()
def value(x,y):
	for i in range(0, 9):
		if sudoku[x][y] != 0:
			if sudoku[x][i] == sudoku[x][y]:
				if i != y:
					return True
			if sudoku[i][y] == sudoku[x][y]:
				if i != x:
					return True
	x1 = x - x % 3
	y1 = y - y % 3
	for i in range(0, 3):
		for j in range(0,3):
			if sudoku[i+x1][j+y1] != 0:
				if sudoku[i+x1][j+y1] == sudoku[x][y]:
					if i+x1 != x or j+y1 != y:
						return True
	return False
def sprawdz():
	for i in range(0,9):
		for j in range(0,9):
			if value(i,j) :
				return True
	return False
seed(1)
plik = open("sudoku2.txt",'r')
sudoku = []
pom = []
mozliwosci = [[[i for i in range(1,10)] for n in range(9)] for m in range(9)]
for linia in plik:
	pom = []
	for w in linia.strip():
		if w != ' ':
			x = int(w)
			pom.append(x)
	sudoku.append(pom)
plik.close()
print "Do rozwiazania"
wypisz()
if sprawdz():
	print "Bledne dane wejsciowe"
else :
	solve()
	if wypelnione() :
		print "Rozwiazanie koncowe"
		wypisz()
	else :
		minimalny()
		if sprawdz():
			print "Rozwiazanie niemozliwe"
		else :
			print "Rozwiazanie koncowe"
			wypisz()
