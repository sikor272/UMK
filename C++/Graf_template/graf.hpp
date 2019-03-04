#ifndef GRAF_CLASS
#define GRAF_CLASS

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
template<typename T>
class Graf {
private:
    vector<vector<unsigned int> > lista;
    unsigned int rozmiar;
    T *dane;
    unsigned int used;
public:
    Graf<T>(){};
    Graf<T>(unsigned int);
    Graf<T>(unsigned int, vector<vector<unsigned int> >, T*);
    Graf<T>(const Graf<T> &);
    Graf<T> & operator=(const Graf<T> &);
    vector<unsigned int>::iterator sprawdz(unsigned int, unsigned int);
    void dodajKrawedz(T, T);
    void usunKrawedz(T, T);
    vector<unsigned int> najkrotszaDroga(unsigned int, unsigned int );
    Graf<T> drzewoRozpinajace();
    template<typename S>
    friend ostream & operator<<(ostream &,const Graf<S> &);
    unsigned int nazwa(T);
    ~Graf<T>();
};
template<typename T>
Graf<T>::~Graf(){
    delete [] dane;
}
template<typename T>
Graf<T>::Graf(unsigned int _rozmiar){
    rozmiar = _rozmiar;
    lista.resize(rozmiar);
    dane = new T[rozmiar];
    used = 0;
}
template<typename T>
Graf<T>::Graf(unsigned int _rozmiar, vector<vector<unsigned int> > _lista, T *_dane){
    unsigned int i = 0;
    rozmiar = _rozmiar;
    lista.resize(rozmiar);
    dane = new T[rozmiar];
    used = rozmiar;
    for(vector<vector<unsigned int> >::const_iterator it = _lista.begin(); it != _lista.end(); it++, i++){
        for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
            lista[i].push_back(*ti);
        }
    }
    for(i=0;i<rozmiar;i++){
        dane[i] = _dane[i];
    }
}
template<typename T>
Graf<T>::Graf(const Graf<T> & old){
    rozmiar = old.rozmiar;
    lista.resize(rozmiar);
    dane = new T[rozmiar];
    used = old.used;
    unsigned int i = 0;
    for(vector<vector<unsigned int> >::const_iterator it = lista.begin(); it != lista.end(); it++, i++){
        for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
            lista[i].push_back(*ti);
        }
    }
    for(i=0;i<rozmiar;i++){
        dane[i] = old.dane[i];
    }
}
template<typename T>
Graf<T>& Graf<T>::operator=(const Graf<T> & old){
    if(this != &old){
        rozmiar = old.rozmiar;
        lista.resize(rozmiar);
        dane = new T[rozmiar];
        used = old.used;
        unsigned int i = 0;
        for(vector<vector<unsigned int> >::const_iterator it = old.lista.begin(); it != old.lista.end(); it++, i++){
            lista[i].clear();
            for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
                lista[i].push_back(*ti);
            }
        }
        for(i=0;i<rozmiar;i++){
            dane[i] = old.dane[i];
        }
    }
    return *this;
}
template<typename T>
typename vector<unsigned int>::iterator Graf<T>::sprawdz(unsigned int _x, unsigned int _y){
        return find( lista[_x].begin(), lista[_x].end(), _y);
}
template<typename T>
unsigned int Graf<T>::nazwa(T name){
    unsigned int i;
    for(i = 0; i < used; i++){
        if(dane[i] == name){
            return i;
        }
    }
    dane[used] = name;
    used++;
    return i;
}
template<typename T>
void Graf<T>::dodajKrawedz(T _x,T _y){
    unsigned int x, y;
    x = nazwa(_x);
    y = nazwa(_y);
    vector<unsigned int>::iterator point = sprawdz(x, y);
    if(point == lista[x].end()){
        lista[x].push_back(y);
        lista[y].push_back(x);
    }
}
template<typename T>
void Graf<T>::usunKrawedz(T _x,T _y){
    unsigned int x, y;
    x = nazwa(_x);
    y = nazwa(_y);
    vector<unsigned int>::iterator point_x = sprawdz(x, y);
    vector<unsigned int>::iterator point_y = sprawdz(y, x);
    if(point_x != lista[_x].end()){
        lista[x].erase(point_x);
        lista[y].erase(point_y);
    }
}
template<typename T>
vector<unsigned int> Graf<T>::najkrotszaDroga(unsigned int _x, unsigned int _y){
    vector<unsigned int> droga;
    queue<unsigned int> nastepni;
    bool odwiedzone[rozmiar];
    unsigned int pomoc, poprzedni[rozmiar];
    unsigned int i;
    if(_x >= rozmiar || _y >= rozmiar){
        return droga;
    }
    for(i = 0; i < rozmiar; i++){
        odwiedzone[i] = false;
        poprzedni[i] = -1;
    }
    odwiedzone[_x] = true;
    for(vector<unsigned int>::iterator it = lista[_x].begin(); it != lista[_x].end(); it++){
        nastepni.push(*it);
        poprzedni[*it] = _x;
        odwiedzone[*it] = true;
    }
    while(!nastepni.empty()){
        pomoc = nastepni.front();
        nastepni.pop();
        odwiedzone[pomoc] = true;
        for(vector<unsigned int>::iterator it = lista[pomoc].begin(); it != lista[pomoc].end(); it++){
            if(!odwiedzone[*it]){
                nastepni.push(*it);
                poprzedni[*it] = pomoc;
                odwiedzone[*it] = true;
            }
        }
    }
    if(odwiedzone[_y]){
        i = _y;
        droga.push_back(_y);
        while(poprzedni[i] != -1){
            droga.push_back(poprzedni[i]);
            i = poprzedni[i];
        }
    }
    return droga;
}
template<typename T>
Graf<T> Graf<T>::drzewoRozpinajace(){
    if(rozmiar == 0){
        return Graf();
    }
    bool odwiedzone[rozmiar];
    unsigned int i, pomoc;
    queue<unsigned int> nastepny;
    vector<vector<unsigned int> > wynik;
    wynik.resize(rozmiar);
    for(i = 0; i < rozmiar; i++){
        odwiedzone[i] = false;
    }
    odwiedzone[0] = true;
    for(vector<unsigned int>::const_iterator it = lista[0].begin(); it != lista[0].end(); it++){
            wynik[0].push_back(*it);
            wynik[*it].push_back(0);
            nastepny.push(*it);
            odwiedzone[*it] = true;
    }

    while(!nastepny.empty()){
        pomoc = nastepny.front();
        nastepny.pop();
        odwiedzone[pomoc] = true;
        for(vector<unsigned int>::iterator it = lista[pomoc].begin(); it != lista[pomoc].end(); it++){
            if(!odwiedzone[*it]){
                nastepny.push(*it);
                wynik[pomoc].push_back(*it);
                wynik[*it].push_back(pomoc);
                odwiedzone[*it] = true;
            }
        }
    }

    return Graf(rozmiar,wynik,dane);
}
template<typename T>
ostream & operator<<(ostream & wypisz, const Graf<T> & G){
    unsigned int i = 0;
    for(vector<vector<unsigned int> >::const_iterator it = G.lista.begin(); it != G.lista.end(); it++, i++){
        wypisz << G.dane[i] << ": ";
        for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
            wypisz << G.dane[*ti] << " ";
        }
        wypisz << endl;
    }
    return wypisz;
}

#endif
