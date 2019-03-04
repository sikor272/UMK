#include <iostream>
using namespace std;

void buduj(int *tab,int n){
	int ojciec = (n-1)/2;
	if(tab[ojciec]<tab[n]){
		swap(tab[ojciec],tab[n]);
		buduj(tab,ojciec);
	}
}
void wymieniaj(int *tab,int n,int x){
	int lewy,prawy,wl,wp;
	lewy = 2*x+1;
	prawy = 2*x+2;
	if(prawy<n){
		if(tab[x]<tab[lewy] && tab[prawy]<tab[lewy]){
			swap(tab[x],tab[lewy]);
			wymieniaj(tab,n,lewy);
		} else if(tab[x]<tab[prawy]){
			swap(tab[x],tab[prawy]);
			wymieniaj(tab,n,prawy);
		}
	} else if(lewy<n){
		if(tab[x]<tab[lewy]){
			swap(tab[x],tab[lewy]);
		}
	}
}
int main() {
	int i,j,*tab,n;
	char znak;
	n = 0;
	tab = new int[1<<20];
	while(cin>>znak){
		if(znak == 'x'){
			break;
		} else if(znak == 'i'){
			cin>>j;
			tab[n]=j;
			n++;
			buduj(tab,n-1);
		} else if(znak == 'e'){
			if(n>0){
				cout<<tab[0]<<" ";
				swap(tab[0],tab[n-1]);
				n--;
				wymieniaj(tab,n,0);
			} else {
				cout<<"! ";
			}
		}
	}
	return 0;
}