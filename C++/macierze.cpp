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
        void dodawanie(macierz A, macierz B){
            int i, j;
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    tab[i][j] = A.tab[i][j] + B.tab[i][j];
                }
            }
        }
        void mnozenie(macierz A, macierz B){
            int i, j, k;
            for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                    for(k = 0; k < n; k++){
                        tab[i][j] = tab[i][j] + A.tab[i][k] * B.tab[k][j];
                    }
                }
            }
        }
        double wyznacznik(){
            double wynik = 0;
            int i, j, znak;
            if(n == 1)
                return tab[0][0];
            macierz A(n - 1);
            wynik = 0;

            for(i = 0; i < n - 1; i++){
                for(j = 0; j < n - 1; j++){
                    A.tab[i][j] = tab[i + 1][j + 1];
                }
            }
            znak = 1;
            for(i = 0; i < n; i++){
                wynik = wynik + znak * tab[i][0] * A.wyznacznik();
                for(j = 0; j < n - 1 && i < (n - 1); j++){
                    A.tab[i][j] = tab[i][j + 1];
                }
                znak = -znak;
            }
            return wynik;

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
                    x = y = 0;
                    for(k = 0; k < n - 1; k++){
                        if(x == i) x++;
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
    macierz a(n),b(n),wynik(n),wynik2(n);
    a.wczytaj();
    b.wczytaj();

    a.odwroc();
    wynik.dodawanie(a, b);
    wynik.wypisz();
    cout << endl;
    wynik2.mnozenie(a, b);
    wynik2.wypisz();
    return 0;
}

