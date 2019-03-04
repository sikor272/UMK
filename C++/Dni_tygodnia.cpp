#include <iostream>
using namespace std;


class tydzien
{
private:
		int dzien;
		int miesiac;
		int rok;
public:
	tydzien()
	{
		dzien = 0;
		miesiac = 0;
		rok = 0;
	}
	bool sprawdz()const
	{
	    int month[] = {31, 29, 31, 30, 31 , 30, 31, 31, 30, 31, 30, 31};
		if(miesiac < 1 || miesiac > 12)
			return false;
		if(miesiac == 2 && dzien == 29 && !przestepny(rok))
                return false;
        if(dzien < 1 || dzien > month[miesiac - 1])
            return false;
		return true;
	}
	bool przestepny(int rok)const
	{
		return ((rok % 4 == 0  &&  rok % 100 != 0) || rok % 400 == 0);
	}
	int oblicz()const
	{
	    int liczba[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
		int day;
		day = dzien + liczba[miesiac-1];
		if(miesiac > 2 && przestepny(rok))
            day++;
		return ((((((((rok - 1) - (rok - 1) % 10) / 100) % 4) * 5) + ((rok - 1) % 100 + ((rok - 1) % 100 / 4))) % 7) + day - 1) % 7;
	}
	friend istream & operator>>(istream & wczytaj, tydzien & co);
	friend ostream & operator<<(ostream & wypisz, const tydzien & co);
};
istream & operator>>(istream & wczytaj, tydzien & co)
{
	char znak;
	wczytaj >> co.dzien;
	wczytaj >> znak;
	wczytaj >> co.miesiac;
	wczytaj >> znak;
	wczytaj >> co.rok;

	return wczytaj;
}
ostream & operator<<(ostream & wypisz, const tydzien & co){
    if(!co.sprawdz()){
        wypisz << "ERROR";
    }
    else {
        switch(co.oblicz()){
        case 0:
            wypisz << "PN";
            break;

        case 1:
            wypisz << "WT";
            break;

        case 2:
            wypisz << "SR";
            break;

        case 3:
            wypisz << "CZ";
            break;

        case 4:
            wypisz << "PT";
            break;

        case 5:
            wypisz << "SB";
            break;

        case 6:
            wypisz << "ND";
            break;
        }
    }
    return wypisz;
}
int main() {
	tydzien day;
	cin >> day;
	cout << day;
	return 0;
}
