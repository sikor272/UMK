#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool sprawdz(pair<int,int> a, pair<int,int>b){
	int x = a.first*a.first+a.second*a.second;
	int y = b.first*b.first+b.second*b.second;
	if(x < y)
		return 1;
	if(x > y)
		return 0;
	if(a.first == b.first){
		return a.second <= b.second;
	}
	return a.first < b.first;
}
int main() {
	pair<int, int> x;
	vector <pair<int, int> > t;
	while(cin>>x.first>>x.second){
		t.push_back(x);
	}
	sort(t.begin(), t.end(), sprawdz);
	for(vector<pair<int,int> >::iterator i=t.begin(); i!=t.end(); i++){
		cout << (*i).first << " " << (*i).second << endl;
	}
	return 0;
}