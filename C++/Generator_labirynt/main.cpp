#include "labirynt.hpp"
#include <iostream>
using namespace std;
int main()
{
    srand(time(NULL));
    unsigned int n, m;
    cin >> n >> m;
    Labirynt DFS(n,m),BFS(n,m);
    DFS.generator_DFS();
    BFS.generator_BFS();
    cout << "Generowanie DFS:" << endl;
    cout << DFS;
    cout << endl;
    cout << "Generowanie BFS:" << endl;
    cout << BFS;
    return 0;
}
