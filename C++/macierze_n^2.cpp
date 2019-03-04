#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

class macierz{
    private:
        int n;
        double **tab;
    public:
        macierz(int _n){
            int i, j;
            n = _n;
            tab = new double*[n];
            for(i = 0; i < n; i++){
                tab[i] = new double[n];
                for(j = 0; j < n; j++){
                    tab[i][j] = 0;
                }
            }
        }
        macierz(const macierz& old){
            int i, j;
            n = old.n;
            tab = new double*[n];
            for(i = 0; i < n; i++){
                tab[i] = new double[n];
                for(j = 0; j < n; j++){
                    tab[i][j] = old.tab[i][j];
                }
            }
        }
        void wczytaj(){
            int i, j;
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    cin >> tab[i][j];
                }
            }
        }
        void wypisz(){
            int i, j;
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    cout << tab[i][j] << " ";
                }
                cout << endl;
            }
        }
        void dodawanie(macierz B){
            int i, j;
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    tab[i][j] += B.tab[i][j];
                }
            }
        }
        void mnozenie(macierz B){
            int i, j, k;
			double suma;
			macierz A(n);
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
					suma = 0;
                    for(k = 0; k < n; k++){
                        suma += tab[i][k] * B.tab[k][j];
                    }
					A.tab[i][j] = suma;
                }
            }
			for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    tab[i][j] = A.tab[i][j];
                }
            }
			
        }
        double wyznacznik(){
            double wynik = 0;
            int i, j, znak,k,x;
            if(n == 1)
                return tab[0][0];
            macierz A(n - 1);
            wynik = 0;

            
            znak = 1;
            for(i = 0; i < n; i++){
				x = 0;
                for(k = 0; k < n; k++){
					if(k == i)continue;
					for(j = 0; j < n - 1; j++){
						A.tab[x][j] = tab[k][j + 1];
					}
					x++;
				}
				wynik = wynik + znak * tab[i][0] * A.wyznacznik();
                znak = -znak;
            }
            return wynik;

        }
void odwroc2() {
tab[0][0] = 1 / tab[0][0];
} 
        void odwroc(){
            double wyz = this->wyznacznik();
            int znak;
            if(wyz == 0){
                cout << "Macierz nie jest odwracalna!";
                exit(0);
            }
            int i, j, k, l, x, y;
            macierz A(n - 1),B(n);
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    x = 0;
                    for(k = 0; k < n - 1; k++){
                        if(x == i) x++;
                        y = 0;
                        for(l = 0; l < n - 1; l++){
                            if(y == j) y++;
                            A.tab[k][l] = tab[x][y];
                            y++;
                        }
                        x++;
                    }
                    if( (i + j + 2) % 2 == 0) znak = 1;
                    else znak = -1;
                    B.tab[i][j] = znak * A.wyznacznik();
                }
            }
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    tab[i][j] = B.tab[j][i] / wyz;
                }
            }
        }
        ~macierz(){
            int i;
            for(i = 0; i < n; i++){
                delete [] tab[i];
            }
            delete [] tab;
        }
};

int main(){
    int n;
    cin >> n;
    macierz a(n),b(n);
    a.wczytaj();
    b.wczytaj();
    if(n!=1)
    a.odwroc();
else
a.odwroc2();
	macierz wynik(a);
    wynik.dodawanie(b);
    wynik.wypisz();
    cout << endl;
    a.mnozenie(b);
    a.wypisz();
    return 0;
}