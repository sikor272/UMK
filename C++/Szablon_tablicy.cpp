#include <iostream>
using namespace std;
template<typename T>
class Tablica{
private:
    T *dane;
    int rozmiar;
public:
    Tablica<T>(){
        dane = NULL;
        rozmiar = 0;
    }
    Tablica<T>(int _r){
        rozmiar = _r;
        dane = new T[rozmiar];
    }
    Tablica<T>(const Tablica<T> & old){
        rozmiar = old.rozmiar;
        delete [] dane;
        dane = new T[rozmiar];
        for(int i = 0; i < rozmiar; i++){
            dane[i] = old.dane[i];
        }
    }
    Tablica<T>(int _r, T *_dane){
        rozmiar = _r;
        dane = new T[rozmiar];
        for(int i = 0; i < rozmiar; i++){
            dane[i] = _dane[i];
        }
    }
    void sortowanie(){
        int i, j;
        T x;
        for (i = 0; i < rozmiar; i++)
            for (j = 0; j < rozmiar - 1 - i; j++)
                if(dane[j] > dane[j + 1]){
                    x = dane[j];
                    dane[j] = dane[j + 1];
                    dane[j + 1] = x;
                }
    }
    friend ostream & operator<<(ostream & wypisz, const Tablica<T> & q){
        if(q.rozmiar == 0){
            wypisz << "Pusto" << endl;
            return wypisz;
        }
        wypisz << "Zawartosc:" << endl;
        for(int i = 0; i < q.rozmiar; i++){
            wypisz << q.dane[i] << " ";
        }
        wypisz << endl;
        return wypisz;
    }
    friend istream & operator>>(istream & wczytaj, Tablica<T> & q){
        if(q.rozmiar == 0){
            cout << "Podaj rozmiar:" << endl;
            wczytaj >> q.rozmiar;
            q.dane = new T[q.rozmiar];
        }
        for(int i = 0; i < q.rozmiar; i++){
            wczytaj >> q.dane[i];
        }
        return wczytaj;
    }
    ~Tablica(){
        if(rozmiar > 0){
            delete [] dane;
        }
    }
};

int main(){
    Tablica<string> nowa;
    cin >> nowa;
    nowa.sortowanie();
    cout << nowa;
    return 0;
}
