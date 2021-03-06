#include "graf.hpp"
int main()
{
    unsigned int i, v, w, n, m;
    vector<unsigned int> droga;
    vector<vector<unsigned int> > wczytaj;
    cin >> n >> m;
    wczytaj.resize(n);
    for(i = 0; i < m; i++){
        cin >> v >> w;
        wczytaj[v].push_back(w);
        wczytaj[w].push_back(v);
    }
    Graf nowy(n, wczytaj);
    cin >> m;
    for(i = 0; i < m; i++){
        cin >> v >> w;
        droga = nowy.najkrotszaDroga(v, w);
        if(droga.size() > 0){
            cout << droga.size() - 1 << endl;
        } else
            cout << "Brak drogi" << endl;
    }

    return 0;
}
