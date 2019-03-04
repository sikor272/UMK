#include "graf.hpp"
#include <iostream>
using namespace std;
int main()
{
    unsigned int i, n, m;
    string v, w;
    cin >> n >> m;
    Graf<string> nowy(n);
    for(i = 0; i < m; i++){
        cin >> v >> w;
        nowy.dodajKrawedz(v, w);
    }
    cout << endl;
    cout << nowy.drzewoRozpinajace();
    return 0;
}
