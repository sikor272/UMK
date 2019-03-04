#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
class Pliczki{
private:
    ifstream wejscie;
    ofstream wyjscie;
    unsigned long long int rozmiar;
    void otworz(string _n1, string _n2){
        wejscie.open(_n1.c_str());
        wyjscie.open(_n2.c_str());
    }
public:
    Pliczki(string _n1, string _n2){
        otworz(_n1, _n2);
        rozmiar = 0;
    }
    void kopiuj(){
        string bufor;
        while(getline(wejscie,bufor)){
            wyjscie << bufor << endl;
            rozmiar += bufor.size();
        }
    }
    unsigned long long int ile(){
        return rozmiar;
    }
    ~Pliczki(){
        wejscie.close();
        wyjscie.close();
    }
};
using namespace std;
int main(int argc, char *argv[]){
    string a,b;
    cin >> a >> b;
    Pliczki plik(a, b);
    auto start = chrono::system_clock::now();
    plik.kopiuj();
    auto stop = chrono::system_clock::now();
    chrono::duration<double> diff = stop-start;
    cout << "Ilosc znakow: " << plik.ile() << endl;
    cout << "Czas wykonania: " << diff.count() << "s" << endl;

    return 0;
}
