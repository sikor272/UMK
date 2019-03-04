#include<iostream>
#include<cstdlib>

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
        zespolona operator+(zespolona & druga){
            real += druga.real;
            imag += druga.imag;
            return zespolona(real,imag);
        }
        zespolona operator-(zespolona & druga){
            real -= druga.real;
            imag -= druga.imag;
            return zespolona(real,imag);
        }
        zespolona operator+=(zespolona & druga){
            real += druga.real;
            imag += druga.imag;
            return zespolona(real,imag);
        }
        zespolona operator-=(zespolona & druga){
            real -= druga.real;
            imag -= druga.imag;
            return zespolona(real,imag);
        }
        
        zespolona operator*(zespolona & druga){
            zespolona a;
            a.real = real * druga.real - imag * druga.imag;
            a.imag = real * druga.imag + imag * druga.real;
            return a;
        }
        zespolona operator*=(zespolona & druga){
            zespolona a;
            a.real = real * druga.real - imag * druga.imag;
            a.imag = real * druga.imag + imag * druga.real;
            return a;
        }
        zespolona operator/(zespolona & druga){
            if(druga.real == druga.imag && druga.real == 0){
                cout << "INF";
                exit(0);
            }
            zespolona a;
            a.real = real * druga.real + imag * druga.imag;
            a.imag = imag * druga.real - real * druga.imag;
            a.real /= (druga.real * druga.real + druga.imag * druga.imag);
            a.imag /= (druga.real * druga.real + druga.imag * druga.imag);
            return a;
        }
        zespolona operator/=(zespolona & druga){
            if(druga.real == druga.imag && druga.real == 0){
                cout << "INF";
                exit(0);
            }
            zespolona a;
            a.real = real * druga.real + imag * druga.imag;
            a.imag = imag * druga.real - real * druga.imag;
            a.real /= (druga.real * druga.real + druga.imag * druga.imag);
            a.imag /= (druga.real * druga.real + druga.imag * druga.imag);
            return a;
        }
        friend istream & operator>>(istream & wczytaj, zespolona & liczba);
        friend ostream & operator<<(ostream & wczytaj, const zespolona & liczba);


};
istream & operator>>(istream & wczytaj, zespolona & liczba){
    char znak;
    wczytaj >> liczba.real;
    wczytaj >> znak;
    wczytaj >> liczba.imag;
    if(znak == '-')
        liczba.imag = -liczba.imag;
    wczytaj >> znak;
    return wczytaj;
}
ostream & operator<<(ostream & wczytaj, const zespolona & liczba){
    if(liczba.imag == 0){
        wczytaj << liczba.real;
    } else
    if(liczba.real == 0){
        wczytaj << liczba.imag << "i";
    } else {
        wczytaj << liczba.real;
        if(liczba.imag > 0)
            wczytaj << "+";
            wczytaj << liczba.imag << "i";
    }
    return wczytaj;
}
int main(){
    char dzialanie;
    zespolona a,b;
    cin >> a >> dzialanie >> b;
    if(dzialanie == '+')
        a = a + b;
    else if(dzialanie == '-')
        a = a - b;
    else if(dzialanie == '*')
        a = a * b;
    else
        a = a / b;
    cout << a;
    return 0;
}
