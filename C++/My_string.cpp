#include<iostream>
#include<cstring>

using namespace std;

class moj_string{
    private:
        char *napis;
    public:
        moj_string(char *_napis){
            unsigned int i, n;
            n = strlen(_napis);
            napis = new char[n];
            for(i = 0; i < n ; i++){
                napis[i] = _napis[i];
            }
        }
        moj_string(const moj_string& old){
            unsigned int i, n;
            n = old.dlugosc();
            napis = new char[n];
            for(i = 0; i < n ; i++){
                napis[i] = old.napis[i];
            }
        }
        unsigned int dlugosc() const{
            return strlen(napis);
        }
        bool czyPalindrom(){
            unsigned int i,j,n;
            n = dlugosc();
            for(i = 0, j = n - 1; i < j; i++, j--){
                if(napis[i] != napis[j])
                    return 0;
            }
            return 1;
        }
        unsigned int zlicz(char c){
            unsigned int i,j,n;
            n = dlugosc();
            j = 0;
            for(i = 0; i < n; i++){
                if(napis[i] == c)
                    j++;
            }
            return j;
        }
        ~moj_string(){
            delete [] napis;
        }
};

int main(){
    char ciag[101], znak;
    cin >> ciag;
    moj_string a(ciag);
    while(cin >> znak){
        if(znak == 'q')break;
        if(znak == 'l'){
            cout << a.dlugosc();
        }
        if(znak == 'p'){
            if(a.czyPalindrom())cout << "TAK";
            else cout << "NIE";
        }
        if(znak == 'c'){
            cin >> znak;
            cout << a.zlicz(znak);
        }
        cout << endl;
    }
    return 0;
}
