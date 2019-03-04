#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class ulamek{
private:
    int licznik;
    int mianownik;
    void skroc(){
        int a, b;
        a = licznik;
        b = mianownik;
        while(b)
            swap(a %= b, b);
        licznik /= a;
        mianownik /= a;
        if(mianownik < 0){
            mianownik = -mianownik;
            licznik = -licznik;
        }
    }
public:
    
    friend istream & operator>>(istream & strumien, ulamek & wczytaj);
    friend ostream & operator<<(ostream & strumien, const ulamek & wypisz);
    friend bool sprawdz(const ulamek & x, const ulamek & y);
};

istream & operator>>(istream & strumien, ulamek & wczytaj){
    char znak;
    strumien >> wczytaj.licznik;
    strumien >> znak;
    strumien >> wczytaj.mianownik;
    wczytaj.skroc();
    return strumien;
}
ostream & operator<<(ostream & strumien, const ulamek & wypisz){
    strumien << wypisz.licznik;
    if(wypisz.mianownik != 1){
        strumien << "|";
        strumien << wypisz.mianownik;
    }
    strumien << " ";
    return strumien;
}
bool sprawdz(const ulamek & x, const ulamek & y){
	return x.licznik * y.mianownik < x.mianownik * y.licznik;
}
int main(){
    vector<ulamek> a;
    int n, i;
    cin >> n;
    a.resize(n);
    for(i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end(),sprawdz);
    for(i = 0; i < n; i++){
        cout << a[i];
    }
    return 0;
}