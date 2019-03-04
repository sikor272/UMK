#include <iostream>
#include <algorithm>
using namespace std;
struct zadanie{
	int s;
	int k;
};
void MergeSort(zadanie dane[],int poczatek, int koniec)
{
	if(poczatek==koniec)
		return;

	int srodek;
	srodek=(poczatek+koniec)/2;
	MergeSort(dane,poczatek,srodek);
	MergeSort(dane,srodek+1,koniec);
	zadanie pomocnicza[koniec+1];
	for(int i=poczatek;i<=koniec;i++){
		pomocnicza[i].s=dane[i].s;
		pomocnicza[i].k=dane[i].k;
	}
	int i,j,r;
	i=poczatek;
	r=poczatek;
	j=srodek+1;
	while(i<=srodek && j<=koniec){
		 if(pomocnicza[i].k<pomocnicza[j].k){
		 	dane[r].s=pomocnicza[i].s;
		 	dane[r].k=pomocnicza[i].k;
		 	i++;
		 }else{
		 	dane[r].s=pomocnicza[j].s;
		 	dane[r].k=pomocnicza[j].k;
		 	j++;
		 }
		 r++;
	}
	while(i<=srodek){
		dane[r].s=pomocnicza[i].s;
		dane[r].k=pomocnicza[i].k;
		i++;
		r++;
	}
}
int main() {
	int n;
	cin>>n;
if(n==0){
cout<<"0";return 0;
}
	zadanie dane[n];
	int i;
	for(i=0;i<n;i++){
		cin>>dane[i].s>>dane[i].k;
	}
	MergeSort(dane,0,n-1);
	int licznik=1;
	int koniec=dane[0].k;
	for(i=1;i<n;i++){
		if(dane[i].s>=koniec){
		licznik++;
		koniec=dane[i].k;	
		}
		
	}
	cout<<licznik;
	return 0;
}