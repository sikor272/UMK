#include <iostream>
using namespace std;
class ulamek{
private:
    unsigned int licznik;
    unsigned int mianownik;
    void skroc(){
        unsigned int a, b;
        a = licznik;
        b = mianownik;
        while(b)
            swap(a %= b, b);
        licznik /= a;
        mianownik /= a;
    }
public:
    ulamek(unsigned int l, unsigned int m){
        licznik = l;
        mianownik = m;
        skroc();
    }
    unsigned int oddajp(){
        return licznik;
    }
    unsigned int oddajq(){
        return mianownik;
    }
    ulamek operator+(ulamek & drugi){
        return ulamek(licznik * drugi.mianownik + drugi.licznik * mianownik, mianownik * drugi.mianownik);
    }
    ulamek operator-(ulamek & drugi){
        return ulamek(licznik * drugi.mianownik - drugi.licznik * mianownik, mianownik * drugi.mianownik);
    }
    ulamek operator*(ulamek & drugi){
        return ulamek(licznik * drugi.licznik, mianownik * drugi.mianownik);
    }
    ulamek operator/(ulamek & drugi){
        return ulamek(licznik * drugi.mianownik, mianownik * drugi.licznik);
    }

};
class ulameklancuchowy{
private:
    unsigned int n;
    unsigned int *tab;
public:
    ulameklancuchowy(ulamek & old){
        unsigned int a, b, _n = 1;
        a = old.oddajp();
        b = old.oddajq();
        while(a % b != 0){
            _n++;
            swap(a %= b,b);
        }
        n = _n;
        tab = new unsigned int[n];
        a = old.oddajp();
        b = old.oddajq();
        _n = 0;
        while(a % b != 0){
            tab[_n] = a / b;
            swap(a %= b,b);
            _n++;
        }
        tab[n - 1] = a;
    }
    ~ulameklancuchowy(){
        delete [] tab;
    }
    friend ostream & operator<<(ostream & wypisz, const ulameklancuchowy & co);
};
ostream & operator<<(ostream & wypisz, const ulameklancuchowy & co){
    int i;
    wypisz << "[";
    if(co.n == 1){
        wypisz << co.tab[0];
    } else {
        wypisz << co.tab[0] << "; " << co.tab[1];
        for(i = 2; i < co.n; i++){
            wypisz << ", " << co.tab[i];
        }
    }
    wypisz << "]";
    return wypisz;
}
int main(){
    unsigned int a, b, c, d;
    char znak;
    cin >> a >> b >> znak >> c >> d;
    ulamek x(a, b);
    ulamek y(c, d);
    if(znak == '+'){
        x = x + y;
    } else if(znak == '-'){
        x = x - y;
    } else if(znak == '*'){
        x = x * y;
    } else if(znak == '/'){
        x = x / y;
    }
    ulameklancuchowy wynik(x);
    cout << wynik;
    return 0;
}
