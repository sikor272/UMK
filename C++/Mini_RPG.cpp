#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;

class monster{
    private:
    	int hp;
       int resist;
    public:
        monster(){
            resist = 0;
            hp = 0;
        }
        monster(int _resist, int _hp){
            resist = _resist;
            hp = _hp;
        }
        monster(const monster& old){
            resist = old.resist;
            hp = old.hp;
        }
        friend istream & operator>>(istream & wczytaj, monster & liczba);
        friend ostream & operator<<(ostream & wczytaj, const monster & liczba);
		void zmien(int buf, char znak){
			int kontrol;
			int pomoc;
			kontrol = 1 << (buf - 1);
			pomoc = 0xff;
			if(znak == '+'){
				resist |= kontrol;
			}
			if(znak == '-'){
				pomoc ^= kontrol;
				resist &= pomoc;
			}
		}

};
istream & operator>>(istream & wczytaj, monster & liczba){
    int buf;
    char znak;
    wczytaj >> liczba.hp;
    wczytaj >> hex >> liczba.resist;
    while(wczytaj >> buf){
    	wczytaj >> znak;
    	liczba.zmien(buf, znak);
    }
    return wczytaj;
}
ostream & operator<<(ostream & wczytaj, const monster & liczba){
	wczytaj << "Potwor ma " << liczba.hp << " HP." << endl;
    	wczytaj << "Atrybuty:";
    if(liczba.resist & 1){
    	wczytaj << endl << "Earth resistance";
    }
    if(liczba.resist & (1 << 1)){
		wczytaj << endl << "Wind resistance";
    }
	if(liczba.resist & (1 << 2)){
		wczytaj << endl << "Fire resistance";
	}
	if(liczba.resist & (1 << 3)){
		wczytaj << endl << "Water resistance";
	}
	if(liczba.resist & (1 << 4)){
		wczytaj << endl << "Dagger resistance";
	}
	if(liczba.resist & (1 << 5)){
		wczytaj << endl << "Bow resistance";
	}
	if(liczba.resist & (1 << 6)){
		wczytaj << endl << "Blunt vulnerable";
	}
	if(liczba.resist & (1 << 7)){
		wczytaj << endl << "Sword vulnerable";
	}
    return wczytaj;
}
int main(){
    monster a;
    cin >> a;
    cout << a;
    return 0;
}