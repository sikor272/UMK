#include <iostream>
using namespace std;

template<unsigned int n>
class Binarnie{
public:
    static const unsigned long long wartosc = Binarnie<n/10>::wartosc*2 + n%10;
};
template<>
class Binarnie<0>{
public:
    static const unsigned long long wartosc = 0;
};
int main(){
    cout << Binarnie<1010101000>::wartosc;
    return 0;
}
