#include "graf.hpp"
Graf::Graf(unsigned int _rozmiar){
    rozmiar = _rozmiar;
    lista.resize(rozmiar);
}
Graf::Graf(unsigned int _rozmiar, vector<vector<unsigned int> > _lista){
    rozmiar = _rozmiar;
    lista.resize(rozmiar);
    unsigned int i = 0;
    for(vector<vector<unsigned int> >::const_iterator it = _lista.begin(); it != _lista.end(); it++, i++){
        for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
            lista[i].push_back(*ti);
        }
    }
}
Graf::Graf(const Graf & old){
    rozmiar = old.rozmiar;
    lista.resize(rozmiar);
    unsigned int i = 0;
    for(vector<vector<unsigned int> >::const_iterator it = lista.begin(); it != lista.end(); it++, i++){
        for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
            lista[i].push_back(*ti);
        }
    }
}
Graf& Graf::operator=(const Graf & old){
    if(this != &old){
        rozmiar = old.rozmiar;
        lista.resize(rozmiar);
        unsigned int i = 0;
        for(vector<vector<unsigned int> >::const_iterator it = old.lista.begin(); it != old.lista.end(); it++, i++){
            lista[i].clear();
            for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
                lista[i].push_back(*ti);
            }
        }
    }
    return *this;
}
vector<unsigned int>::iterator Graf::sprawdz(unsigned int _x, unsigned int _y){
        return find( lista[_x].begin(), lista[_x].end(), _y);
}
void Graf::dodajKrawedz(unsigned int _x, unsigned int _y){
    vector<unsigned int>::iterator point = sprawdz(_x, _y);
    if(point == lista[_x].end()){
        lista[_x].push_back(_y);
        lista[_y].push_back(_x);
    }
}
void Graf::usunKrawedz(unsigned int _x, unsigned int _y){
    vector<unsigned int>::iterator point_x = sprawdz(_x, _y);
    vector<unsigned int>::iterator point_y = sprawdz(_y, _x);
    if(point_x != lista[_x].end()){
        lista[_x].erase(point_x);
        lista[_y].erase(point_y);
    }
}
vector<unsigned int> Graf::najkrotszaDroga(unsigned int _x, unsigned int _y){
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
Graf Graf::drzewoRozpinajace(){
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

    return Graf(rozmiar,wynik);
}
ostream & operator<<(ostream & wypisz, const Graf & G){
    unsigned int i = 0;
    for(vector<vector<unsigned int> >::const_iterator it = G.lista.begin(); it != G.lista.end(); it++, i++){
        wypisz << i << ": ";
        for(vector<unsigned int>::const_iterator ti = it->begin(); ti != it->end(); ti++){
            wypisz << *ti << " ";
        }
        wypisz << endl;
    }
    return wypisz;
}
