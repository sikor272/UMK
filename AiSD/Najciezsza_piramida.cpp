#include <iostream>
using namespace std;

int main() {
	int n;
	cin>>n;
	if(n==0){
		cout<<0;
		return 0;
	}
	int tab[n][n],i,j,s=0,p=0;
	for(i=0;i<n,s<n;i++){
		for(j=0;j<=i && s<n;j++,s++){
			cin>>tab[i][j];
		}
		p++;
	}
	p-=2;
	for(i=p;i>=0;i--){
		for(j=0;j<=i;j++){
			tab[i][j]+=max(tab[i+1][j],tab[i+1][j+1]);
		}
	}
	cout<<tab[0][0];
	return 0;
}