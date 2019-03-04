#include <iostream>
using namespace std;
class Wezel {
private:
    int punkt;
    Wezel *nastepny = NULL;
public:
    Wezel(){}
    Wezel(int _pkt){
        punkt = _pkt;
    }
    friend class Stos;
};
class Stos {
private:
    Wezel *poczatek = NULL;
    unsigned int suma = 0;
public:
    Stos(){};
    bool czyPusty(){
        if(poczatek == NULL)
            return true;
        return false;
    };
    unsigned int rozmiar(){
        return suma;
    }
    void dodaj(int _pkt){
        Wezel *pomoc = poczatek;
        if(czyPusty()){
            poczatek = (new Wezel(_pkt));
            return;
        }
        pomoc = (new Wezel(_pkt));
        pomoc->nastepny = poczatek;
        poczatek = pomoc;
        return;
    }
    int obejrzyj(){
        if(czyPusty()){
            return 0;
        }
        return poczatek->punkt;
    }
    void zdejmij(){
        if(czyPusty()){
            return;
        }
        poczatek = poczatek->nastepny;
        suma--;
        return;
    }
    int znajdz(int _spr){
        Wezel *pomoc = poczatek;
        int i = 0;
        if(czyPusty()){
            return -1;
        }
        while(pomoc != NULL){
            if(pomoc->punkt == _spr)
                return i;
            i++;
            pomoc = pomoc->nastepny;
        }
        return -1;
    }
    ~Stos(){
        if(czyPusty()){
        } else {
            Wezel *pomoc = poczatek, *pomoc2;
            while(pomoc != NULL){
                pomoc2 = pomoc->nastepny;
                delete pomoc;
                pomoc = pomoc2;
            }
        }
    }
};
int main()
{
    Stos stosik;
    stosik.dodaj(10);
    stosik.dodaj(50);
    stosik.dodaj(30);
    stosik.dodaj(20);
    stosik.dodaj(40);
    cout << stosik.obejrzyj() << endl;
    cout << stosik.znajdz(40) << endl;
    stosik.zdejmij();
    cout << stosik.znajdz(40) << endl;
    return 0;
}
