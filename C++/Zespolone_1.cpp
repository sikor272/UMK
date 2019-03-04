#include<iostream>
#include<iomanip>

using namespace std;

class zespolona{
    private:
       double real;
       double imag;
    public:
        zespolona(){
            real = 0;
            imag = 0;
        }
        zespolona(double _real, double _imag){
            real = _real;
            imag = _imag;
        }
        zespolona(const zespolona& old){
            real = old.real;
            imag = old.imag;
        }
        void dodawanie(zespolona a, zespolona b){
            real = a.real + b.real;
            imag = a.imag + b.imag;
        }
        void odejmowanie(zespolona a, zespolona b){
            real = a.real - b.real;
            imag = a.imag - b.imag;
        }
        void wypisz(){
            if(real == 0 && imag == 0){
                cout << 0;
                return;
            }
            if(real == 0){
                cout <<  imag << "i";
                return;
            }
            if(imag == 0){
                cout <<  real;
                return;
            }
            cout << real;
            if(imag > 0)cout << "+";
            cout << imag << "i";
        }
};

int main(){
    double a, b, c, d;
    char znak, dzialanie;
    cin >> a >> znak >> b;
    if(znak == '-')b = -b;
    cin >> znak;
    cin >> dzialanie;
    cin >> c >> znak >> d;
    if(znak == '-')d = -d;
    cin >> znak;

    zespolona x(a,b), y(c,d), wynik;
    if(dzialanie == '+')
        wynik.dodawanie(x,y);
    else
        wynik.odejmowanie(x,y);
    wynik.wypisz();
    return 0;
}
