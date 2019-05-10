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

def check(x,y,value):

	for i in range(9):
		# wiersz
		if sudoku[x][i] == value:
			return False
		# kolumna
		if sudoku[i][y] == value:
			return False
	# kwadrat
	for i in range(3):
		for j in range(3):
			if sudoku[i + x - x%3][j + y - y%3] == value:
				return False
	return True

def free():
	for x in range(9):
		for y in range(9):
			if sudoku[x][y] == 0:
				return x,y
	return -1,-1

def solve():
	x,y = free()
	if x == -1:
		return True
	for i in range(1,10):
		if check(x,y,i):
			sudoku[x][y] = i
			if solve():
				return True
			sudoku[x][y] = 0
	return False
def complete():
	for i in range(9):
		for j in range(9):
			pomoc = sudoku[i][j]
			sudoku[i][j] = 0
			if not check(i,j,pomoc):
				sudoku[i][j] = pomoc
				return False
			sudoku[i][j]=pomoc
	return True

plik = open("sudoku2.txt",'r')
sudoku = []
for linia in plik:
	pom = []
	for w in linia.strip():
		if w != ' ':
			x = int(w)
			pom.append(x)
	sudoku.append(pom)
plik.close()
pomoc = sudoku
print "SUDOKU DO ROZWIAZANIA"
wypisz()
solve()
if complete():
	print "ROZWIAZANE SUDOKU"
	wypisz()
else:
	print "ROZWIAZANIE NIEMOZLIWE"
