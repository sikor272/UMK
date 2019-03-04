#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
using namespace std;
class Grep{
private:
    bool czy_plik;
    char *szukana;
    ifstream plik;
public:
    Grep(){
        czy_plik = false;
    }
    Grep(char *co){
        szukana = new char[strlen(co) + 1];
        czy_plik = false;
        for(int i = 0; i < strlen(co); i++){
            szukana[i] = co[i];
        }
        szukana[strlen(co)] = '\0';
    }
    Grep(char *co, char *name){
        szukana = new char[strlen(co) + 1];
        czy_plik = true;
        plik.open(name);
        for(int i = 0; i < strlen(co); i++){
            szukana[i] = co[i];
        }
        szukana[strlen(co)] = '\0';
    }
    bool sprawdz(string bufor){
        int i, j;
        bool wzorzec;
        for(i = 0; i <= bufor.size() - strlen(szukana); i++){
            wzorzec = true;
            for(j = 0; j < strlen(szukana); j++){
                if(bufor[i+j] != szukana [j]){
                    wzorzec = false;
                    break;
                }
            }
            if(wzorzec)
                return true;
        }
        return false;
    }
    void wypisz_plik(){
        string bufor;
        while(getline(plik,bufor)){
            if(sprawdz(bufor)){
                cout << bufor << endl;
            }
        }
    }
    void standard(){
        string bufor;
        while(getline(cin,bufor)){
            if(sprawdz(bufor)){
                cout << bufor << endl;
            }
        }
    }
    ~Grep(){
    delete [] szukana;
    if(czy_plik)
        plik.close();
    }
};

using namespace std;
int main(int argc, char *argv[]){
    if(argc == 2){
        Grep wypisz(argv[1]);
        wypisz.standard();
    } else if(argc == 3){
        Grep wypisz(argv[1],argv[2]);
        wypisz.wypisz_plik();
    } else {
        cout << "Niepoprawna ilosc argumentow!" << endl;
        return -1;
    }
    return 0;
}
