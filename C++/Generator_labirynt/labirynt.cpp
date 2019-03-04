#include "labirynt.hpp"

Labirynt::Labirynt(unsigned int _rozmiar){
    n = 2 * _rozmiar - 1;
    m = 2 * _rozmiar - 1;
    sciezki = new char*[n];
    for(int i = 0; i < n; i++){
        sciezki[i] = new char[m];
        for(int j = 0 ;j < m; j++){
            sciezki[i][j] = ' ';
        }
    }
}
Labirynt::Labirynt(unsigned int _rozmiar,unsigned int _rozmiar2){
    n = 2 * _rozmiar - 1;
    m = 2 * _rozmiar2 - 1;
    sciezki = new char*[n];
    for(int i = 0; i < n; i++){
        sciezki[i] = new char[m];
        for(int j = 0 ;j < m; j++){
            sciezki[i][j] = ' ';
        }
    }
}
Labirynt::Labirynt(const Labirynt & old){
    for(int i = 0; i < n; i++){
        delete [] sciezki[i];
    }
    delete [] sciezki;
    n = old.n;
    m = old.m;
    sciezki = new char*[n];
    for(int i = 0; i < n; i++){
        sciezki[i] = new char[m];
        for(int j = 0 ;j < m; j++){
            sciezki[i][j] = old.sciezki[i][j];
        }
    }
}
Labirynt& Labirynt::operator=(const Labirynt & old){
    if(this != &old){
        for(int i = 0; i < n; i++){
            delete [] sciezki[i];
        }
        delete [] sciezki;
        n = old.n;
        m = old.m;
        sciezki = new char*[n];
        for(int i = 0; i < n; i++){
            sciezki[i] = new char[m];
            for(int j = 0 ;j < m; j++){
                sciezki[i][j] = old.sciezki[i][j];
            }
        }
    }
    return *this;
}
ostream & operator<<(ostream & wypisz, const Labirynt & G){
    for(int i = 0; i < G.n; i++){
        for(int j = 0 ;j < G.m; j++){
            wypisz << G.sciezki[i][j] << " ";
        }
        wypisz << endl;
    }
    return wypisz;
}
struct compare
{
    bool operator()(pair<int, int> p1,pair<int,int> p2) {
        return rand()%2;
    }
};
void Labirynt::generator_BFS(){
    if(sciezki[0][0] == '.' || sciezki[0][0] == 'p' || sciezki[0][0] == 'k'){
        for(int i = 0; i < n; i++){
            for(int j = 0 ;j < m; j++){
                sciezki[i][j] = ' ';
            }
        }
    }
    unsigned int x,y;
    int a,b;
    bool koniec;
    priority_queue<pair<unsigned int, unsigned int>, vector<pair<unsigned int, unsigned int> >, compare> kolej;
    pair<unsigned int, unsigned int> punkt,pomoc;
    y = rand() % n;
    x = rand() % m;
    if(x%2)x--;
    if(y%2)y--;
    koniec = true;
    punkt.first = y;
    punkt.second = x;
    kolej.push(punkt);
    sciezki[y][x] = 'p';
    while(!kolej.empty()){
        punkt = kolej.top();
        a = punkt.first;
        b = punkt.second;
        kolej.pop();
        if((a - 2) >= 0){
            if(sciezki[a - 2][b] == ' ' ){
                sciezki[a - 1][b] = '|';
                sciezki[a - 2][b] = '.';
                pomoc.first = a-2;
                pomoc.second = b;
                kolej.push(pomoc);
            }
        }
        if((a + 2) < n){
            if(sciezki[a + 2][b] == ' '){
                sciezki[a + 1][b] = '|';
                sciezki[a + 2][b] = '.';
                pomoc.first = a+2;
                pomoc.second = b;
                kolej.push(pomoc);
            }
        }
        if((b - 2) >= 0){
            if(sciezki[a][b - 2] == ' '){
                sciezki[a][b - 1] = '_';
                sciezki[a][b - 2] = '.';
                pomoc.first = a;
                pomoc.second = b-2;
                kolej.push(pomoc);
            }
        }
        if((b + 2) < m){
            if(sciezki[a][b + 2] == ' '){
                sciezki[a][b + 1] = '_';
                sciezki[a][b + 2] = '.';
                pomoc.first = a;
                pomoc.second = b+2;
                kolej.push(pomoc);
            }
        }
    }
    if(n!=1 || m!=1)
    sciezki[a][b] = 'k';
}
bool end_game;
void Labirynt::sasiedzi_DFS(unsigned int y, unsigned int x){
    int sasiedzi[4][3]={{0,y-2,x},{1,y+2,x},{2,y,x-2},{3,y,x+2}};
    int kolejnosc[4]={0,1,2,3};
    int i,a,b,c,d,e,f,g,h,ile = 0;
    for(i = 0; i < 4; i++){
        a = rand() % 4;
        swap(kolejnosc[i],kolejnosc[a]);
    }
    a = sasiedzi[kolejnosc[0]][1];
    b = sasiedzi[kolejnosc[0]][2];
    c = sasiedzi[kolejnosc[1]][1];
    d = sasiedzi[kolejnosc[1]][2];
    e = sasiedzi[kolejnosc[2]][1];
    f = sasiedzi[kolejnosc[2]][2];
    g = sasiedzi[kolejnosc[3]][1];
    h = sasiedzi[kolejnosc[3]][2];
    if(a >= 0 && a < n && b >= 0 && b < m){
        if(sciezki[a][b] == ' '){
            if(sasiedzi[kolejnosc[0]][0] == 0){
                sciezki[a+1][b] = '|';
            }
            if(sasiedzi[kolejnosc[0]][0] == 1){
                sciezki[a-1][b] = '|';
            }
            if(sasiedzi[kolejnosc[0]][0] == 2){
                sciezki[a][b+1] = '_';
            }
            if(sasiedzi[kolejnosc[0]][0] == 3){
                sciezki[a][b-1] = '_';
            }
            sciezki[a][b] = '.';
            sasiedzi_DFS(a,b);
            ile++;
        }
    }
    if(c >= 0 && c < n && d >= 0 && d < m){
        if(sciezki[c][d] == ' '){
            if(sasiedzi[kolejnosc[1]][0] == 0){
                sciezki[c+1][d] = '|';
            }
            if(sasiedzi[kolejnosc[1]][0] == 1){
                sciezki[c-1][d] = '|';
            }
            if(sasiedzi[kolejnosc[1]][0] == 2){
                sciezki[c][d+1] = '_';
            }
            if(sasiedzi[kolejnosc[1]][0] == 3){
                sciezki[c][d-1] = '_';
            }
            sciezki[c][d] = '.';
            sasiedzi_DFS(c,d);
            ile++;
        }
    }
    if(e >= 0 && e < n && f >= 0 && f < m){
        if(sciezki[e][f] == ' '){
            if(sasiedzi[kolejnosc[2]][0] == 0){
                sciezki[e+1][f] = '|';
            }
            if(sasiedzi[kolejnosc[2]][0] == 1){
                sciezki[e-1][f] = '|';
            }
            if(sasiedzi[kolejnosc[2]][0] == 2){
                sciezki[e][f+1] = '_';
            }
            if(sasiedzi[kolejnosc[2]][0] == 3){
                sciezki[e][f-1] = '_';
            }
            sciezki[e][f] = '.';
            sasiedzi_DFS(e,f);
            ile++;
        }
    }
    if(g >= 0 && g < n && h >= 0 && h < m){
        if(sciezki[g][h] == ' '){
            if(sasiedzi[kolejnosc[3]][0] == 0){
                sciezki[g+1][h] = '|';
            }
            if(sasiedzi[kolejnosc[3]][0] == 1){
                sciezki[g-1][h] = '|';
            }
            if(sasiedzi[kolejnosc[3]][0] == 2){
                sciezki[g][h+1] = '_';
            }
            if(sasiedzi[kolejnosc[3]][0] == 3){
                sciezki[g][h-1] = '_';
            }
            sciezki[g][h] = '.';
            sasiedzi_DFS(g,h);
            ile++;
        }
    }
    if(end_game && ile == 0){
        sciezki[y][x] = 'k';
        end_game = false;
    }
}
void Labirynt::generator_DFS(){
    if(sciezki[0][0] == '.' || sciezki[0][0] == 'p' || sciezki[0][0] == 'k'){
        for(int i = 0; i < n; i++){
            for(int j = 0 ;j < m; j++){
                sciezki[i][j] = ' ';
            }
        }
    }
    end_game = true;
    unsigned int x,y;
    y = rand() % n;
    x = rand() % m;
    if(x%2)x--;
    if(y%2)y--;
    sciezki[y][x] = 'p';
    if(n!=1 || m!=1)
    sasiedzi_DFS(y,x);
}
Labirynt::~Labirynt(){
    for(int i = 0; i < n; i++){
        delete [] sciezki[i];
    }
    delete [] sciezki;
}

