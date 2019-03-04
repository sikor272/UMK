#include <iostream>
#include <iomanip>
using namespace std;
string *rysuj(string *rysunek, string ciag, int poz, int h, int w){
    if(ciag.size() == poz)
        return rysunek;
    if(ciag[poz] == 'R'){
        rysunek[h][w] = '/';
        return rysuj(rysunek, ciag, ++poz, --h, ++w);
    }
    if(ciag[poz] == 'F'){
        rysunek[++h][w] = '\\';
        return rysuj(rysunek, ciag, ++poz, h, ++w);
    }
    if(ciag[poz] == 'C'){
        rysunek[h][w] = '_';
        return rysuj(rysunek, ciag, ++poz, h, ++w);
    }
}
int main(){
    int a, i, j, k, h, maks, mini;
    string ciag, *rysunek, check;
    rysunek = new string[55];
    cin >> a;
    for(i = 0; i < a; i++){
        cin >> ciag;
        h = 0;
        maks = 0;
        mini = 0;
        for(j = 0; j < ciag.size(); j++){
            if(ciag[j] == 'R'){
                h++;
            } else if(ciag[j] == 'F'){
                h--;
            }
            if(h > maks)
                maks = h;
            if(h < mini)
                mini = h;
        }
        h = maks - mini + 2;
        for(j = 0; j < h; j++){
            rysunek[j] = "   " + ciag;
        }
        for(j = 0; j < h; j++){
            for(k = 0; k < ciag.size() + 3; k++){
                if(k == 0){
                    rysunek[j][k] = '|';
                } else if(j == h - 1){
                    rysunek[j][k] = '-';
                } else {
                    rysunek[j][k] = ' ';
                }
            }
        }
        cout << "Case #" << i + 1 << ":\n";
        rysunek[h-1][0] = '+';
        check = rysunek[0];
        rysunek = rysuj(rysunek, ciag, 0, h + mini - 2, 2);
        if(check != rysunek[0])
            cout << rysunek[0] << '\n';
        for(j = 1; j < h; j++){
            cout << rysunek[j] << '\n';
        }
    }

    return 0;
}
