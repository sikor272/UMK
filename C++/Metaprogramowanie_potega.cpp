#include <iostream>
using namespace std;

template<unsigned int n, unsigned int k>
class Potega{
public:
    static const unsigned long long wartosc = n * Potega<n, k - 1>::wartosc;
};
template<unsigned int n>
class Potega<n, 0>{
public:
    static const unsigned long long wartosc = 1;
};
int main(){
    cout << Potega<2, 63>::wartosc;
    return 0;
}
