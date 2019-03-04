#ifndef GRAF_CLASS
#define GRAF_CLASS

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
class Graf {
private:
    vector<vector<unsigned int> > lista;
    unsigned int rozmiar;
public:
    Graf(){};
    Graf(unsigned int);
    Graf(unsigned int, vector<vector<unsigned int> >);
    Graf(const Graf &);
    Graf & operator=(const Graf &);
    vector<unsigned int>::iterator sprawdz(unsigned int, unsigned int);
    void dodajKrawedz(unsigned int, unsigned int);
    void usunKrawedz(unsigned int, unsigned int);
    vector<unsigned int> najkrotszaDroga(unsigned int, unsigned int );
    Graf drzewoRozpinajace();
    friend ostream & operator<<(ostream &,const Graf &);
};
#endif
