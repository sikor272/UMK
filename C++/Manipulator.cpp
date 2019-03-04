#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
class Manipulator {
private:
    char znak;
    int ilosc;
public:
    Manipulator(int _ile, char _z){
        ilosc = _ile;
        znak = _z;
    }
    friend ostream & operator<<(ostream & strumien, const Manipulator m);
};
ostream & operator<<(ostream & strumien, Manipulator m){
    strumien << setw(m.ilosc) << setfill(m.znak);
    return strumien;
}

int main(int argc, char *argv[]){
    int n,t;
    int i,j;
    char znak;
    cin >> n >> t >> znak;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            cout << Manipulator(t, znak) << i * j << " ";
        }
        cout << endl;
    }
    return 0;
}
