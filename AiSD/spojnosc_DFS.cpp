#include <iostream>
#include <vector>
using namespace std;
void dfs(vector <int> *w, bool *o, int n){
	int i;
	o[n]=1;
	for(i=0;i<w[n].size();i++){
		if(o[w[n][i]]==0){
			dfs(w,o,w[n][i]);
		}
	}
	return;
}
bool spr(bool *o,int n){
	int i;
	for(i=0;i<n;i++){
		if(o[i]==0){
			return 0;
		}
	}
	return 1;
}
int main() {
	int n,i,j,k,a,b,c;
	cin>>n;
	vector <int> w[n];
	bool o[n];
	for(i=0;i<n;i++){
		o[i]=0;
	}
	cin>>k;
	for(i=0;i<k;i++){
		cin>>a>>b;
		w[a].push_back(b);
		w[b].push_back(a);
	}
	dfs(w,o,0);
	if(spr(o,n)){
		cout<<"graf spojny";
	} else {
		cout<<"graf niespojny";
	}
	return 0;
}