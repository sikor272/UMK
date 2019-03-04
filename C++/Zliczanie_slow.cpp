#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){
    map<string, int> slownik;
    string napis;
    while(cin >> napis){
        if(napis[napis.length()-1] == '.' || napis[napis.length()-1] == ';' || napis[napis.length()-1] == ',' || napis[napis.length()-1] == ':' || napis[napis.length()-1] == '!' || napis[napis.length()-1] == '?'){
            napis.erase(napis.length()-1,1);
        }
        slownik[napis]++;
    }
    for(map<string,int>::iterator it = slownik.begin(); it != slownik.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}
