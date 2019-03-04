#include <iostream>
using namespace std;

class wierzcholek{
    private:
       double x;
       double y;
    public:
        void czytaj(){
            cin >> x;
            cin >> y;
        }
        double zx(){
            return x;
        }
        double zy(){
            return y;
        }
        void oddajx(wierzcholek a){
            x = a.x;
        }
        void oddajy(wierzcholek a){
            y = a.y;
        }
        void zapiszx(double liczba){
            x = liczba;
        }
        void zapiszy(double liczba){
            y = liczba;
        }
};
class prostokat{
    private:
        wierzcholek w[4];
    public:
        void przepisz(int i, wierzcholek a){
            w[i].oddajx(a);
            w[i].oddajy(a);
        }
        void sprawdz(){
            double x1,x2,x3;
            double y1,y2,y3;
            double wsp1,wsp2,wsp3;
            x1 = w[0].zx();
            y1 = w[0].zy();
            x2 = w[1].zx();
            y2 = w[1].zy();
            x3 = w[2].zx();
            y3 = w[2].zy();
            if(x2 - x1 == 0){
                wsp1 = 0;
            } else{
                wsp1 = (y2 - y1) / (x2 - x1);
            }
            if(x3 - x1 == 0){
                wsp2 = 0;
            } else{
                wsp2 = (y3 - y1) / (x3 - x1);
            }
            if(x3 - x2 == 0){
                wsp3 = 0;
            } else{
                wsp3 = (y3 - y2) / (x3 - x2);
            }

            if((wsp1/wsp2 == -1 && wsp2 != 0) || wsp1 == wsp2){
                w[3].zapiszx(x3+x2-x1);
                w[3].zapiszy(y3+y2-y1);
            } else if((wsp1/wsp3 == -1 && wsp3 != 0) || wsp1 == wsp3){
                w[3].zapiszx(x1+x3-x2);
                w[3].zapiszy(y1+y3-y2);
            } else if((wsp2/wsp3 == -1 && wsp3 != 0) || wsp2 == wsp3){
                w[3].zapiszx(x1+x2-x3);
                w[3].zapiszy(y1+y2-y3);
            } else {
              // cout<<"blad jak nic";
            }
        }
        void wypisz(){
            cout << w[3].zx();
            cout << " ";
            cout << w[3].zy();
        }
};

int main(){
    wierzcholek a,b,c;
    prostokat spr;
    a.czytaj();
    b.czytaj();
    c.czytaj();
    spr.przepisz(0,a);
    spr.przepisz(1,b);
    spr.przepisz(2,c);
    spr.sprawdz();
    spr.wypisz();
    return 0;
}
