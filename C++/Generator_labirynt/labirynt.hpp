#ifndef LABIRYNT_CLASS
#define LABIRYNT_CLASS

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
class Labirynt{
private:
    int n, m;
    char **sciezki;
public:
    Labirynt(){};
    Labirynt(unsigned int);
    Labirynt(unsigned int, unsigned int);
    Labirynt(const Labirynt &);
    Labirynt & operator=(const Labirynt &);
    void generator_BFS();
    void generator_DFS();
    void sasiedzi_DFS(unsigned int, unsigned int);
    ~Labirynt();
    friend ostream & operator<<(ostream &,const Labirynt &);
};
#endif
