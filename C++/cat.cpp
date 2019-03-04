#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]){
    string nazwa;
    string bufor;
    cin >> nazwa;
    ifstream plik(nazwa.c_str());
    while(getline(plik,bufor)){
        cout << bufor << endl;
    }
    plik.close();
    return 0;
}
