#include <iostream>
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
    int licz(){
        return licznik;
    }
    int mian(){
        return mianownik;
    }
    ulamek(){
        licznik = 0;
        mianownik = 0;
    }
    ulamek(int l, int m){
        licznik = l;
        mianownik = m;
        skroc();
    }
    ulamek & operator=(const ulamek & drugi){
        licznik = drugi.licznik;
        mianownik = drugi.mianownik;
        return *this;
    }
    bool operator>(const ulamek drugi){
        return ((double)licznik / mianownik) > ((double)drugi.licznik / drugi.mianownik);
    }
    bool operator>=(const ulamek drugi){
        return ((double)licznik / mianownik) >= ((double)drugi.licznik / drugi.mianownik);
    }
    bool operator<(const ulamek drugi){
        return ((double)licznik / mianownik) < ((double)drugi.licznik / drugi.mianownik);
    }
    bool operator<=(const ulamek drugi){
        return ((double)licznik / mianownik) <= ((double)drugi.licznik / drugi.mianownik);
    }
    bool operator==(const ulamek drugi){
        return ((double)licznik / mianownik) == ((double)drugi.licznik / drugi.mianownik);
    }
    bool operator!=(const ulamek drugi){
        return ((double)licznik / mianownik) != ((double)drugi.licznik / drugi.mianownik);
    }
    friend istream & operator>>(istream & strumien, ulamek & wczytaj);
    friend ostream & operator<<(ostream & strumien, const ulamek & wypisz);
};
class tablica{
private:
    int rozmiar;
    ulamek *tab;
public:
    tablica(){
        rozmiar = 0;
        tab = NULL;
    }
    tablica(int n){
        rozmiar = n;
        tab = new ulamek[rozmiar];
    }
    ulamek zwroc(int i){
        return ulamek(tab[i].licz(),tab[i].mian());
    }
    void dodaj(int i, ulamek nowy){
        tab[i] = nowy;
    }
    void sortuj(){
    int i, j;
    ulamek x;
    for (i = 0; i < rozmiar; i++)
        for (j = 0; j < rozmiar - 1 - i; j++)
            if(tab[j] > tab[j + 1]){
                x = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = x;
            }
    }
    ~tablica(){
        delete [] tab;
    }
    friend ostream & operator<<(ostream & strum, const tablica & wypis);
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
ostream & operator<<(ostream & strum, const tablica & wypis){
    int i;
    ulamek a;
    for(i = 0; i < wypis.rozmiar; i++){
        strum << wypis.tab[i];
    }
    return strum;
}
int main(){
    ulamek a;
    int n, i;
    cin >> n;
    tablica dane(n);
    for(i = 0; i < n; i++){
        cin >> a;
        dane.dodaj(i, a);
    }
    dane.sortuj();
    cout << dane;
    return 0;
}
