#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define inf 1<<10
bool rosnaco(int a, int b) {
	return a > b;
}
int main() {
	int i, j, k, n, m;
	cin >> k >> n;
	if (n == 0) {
		cout << "NIE";
		return 0;
	}
	int nom[inf];
	int tab[inf];
	vector <int> wypis[inf];
	for (i = 0; i<n; i++) {
		cin >> nom[i];
	}
	sort(nom, nom + n);
	tab[0] = 0;
	for (i = 1; i<k + 1; i++) {
		tab[i] = inf;
	}
	for (i = 0; i<n; i++) {
		for (j = 0; j <= k - nom[i]; j++) {
			if (tab[j] + 1 < tab[j + nom[i]]) {
				tab[j + nom[i]] = tab[j] + 1;
				wypis[j + nom[i]].clear();
				for (m = 0; m<wypis[j].size(); m++) {
					wypis[j + nom[i]].push_back(wypis[j][m]);
				}
				wypis[j + nom[i]].push_back(nom[i]);
			}
		}
	}
	if (wypis[k].size()) {
		sort(wypis[k].begin(), wypis[k].end(),rosnaco);
		cout << wypis[k].size() << endl;
		for (i = 0; i < wypis[k].size(); i++) {
			cout << wypis[k][i] << " ";
		}
	}
	else {
		cout << "NIE";
	}

	return 0;
}