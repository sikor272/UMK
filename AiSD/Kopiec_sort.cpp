#include <iostream>
using namespace std;
void heap(int *tab,int n,int x){
	int lewy=2*x+1,prawy=2*x+2,max;
	if(lewy<n && tab[lewy]>tab[x]){
		max = lewy;
	} else {
		max = x;
	}
	if(prawy<n && tab[prawy]>tab[lewy]){
		max = prawy;
	}
	if(max!=x){
		swap(tab[x],tab[max]);
		heap(tab,n,max);
	}
}
void buildheap(int *tab,int n){
	int i;
	for(i=n/2;i>=0;i--){
		heap(tab,n,i);
	}
}
void heapsort(int *tab,int n){
	int i=n-1;
	while(i){
		swap(tab[0],tab[i]);
		i--;
		heap(tab,i,0);
	}
}
int main() {
	int i,j,*tab,n;
	cin>>n;
	tab = new int[n];
	for(i=0;i<n;i++){
		cin>>tab[i];
	}
	buildheap(tab,n);
	heapsort(tab,n);
	for(j=0;j<n;j++){
		cout<<tab[j]<<" ";
	}
	return 0;
}