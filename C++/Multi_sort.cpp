#include <iostream>
#include <string>
using namespace std;
unsigned int ktora(string nazwa, string *nazwy, unsigned int k){
	unsigned int i;
	for(i=0;i<k;i++){
		if(nazwa == nazwy[i])
			return i;
	}
	return 0;
}
unsigned int sprawdz(unsigned int *wypis,unsigned int n,string **dane,unsigned int ktory){
    unsigned int i;
    for(i=0;i<n;i++){
        if(dane[ktory][wypis[i]] != dane[ktory+1][wypis[i]])
            return 0;
    }
    return 1;
}
void sortuj(unsigned int indeks, string **dane,unsigned int ile,unsigned int *wypis, unsigned int kontrol){
	unsigned int i,j;

	for(i=0;i<ile;i++){
		for(j=0;j<ile-1;j++){
		    if(sprawdz(wypis,kontrol,dane,j)){
                if(dane[j][indeks] > dane[j+1][indeks]){
                    swap(dane[j],dane[j+1]);
                }
			}
		}
	}
}
int main() {
	unsigned int ind,n,k,w,i,j,lk,last,*wypis,m;
	string *nazwy;
	string **dane;
	string name;
	cin>>n>>k>>w;
	nazwy = new string[k];
	dane = new string*[n];

	for(i=0;i<k;i++){
		cin>>nazwy[i];
	}
	for(i=0;i<n;i++){
		dane[i] = new string[k];
		for(j=0;j<k;j++){
			cin>>dane[i][j];
		}
	}

	for(i=0;i<w;i++){
		cin>>lk;
		if(lk>0){
        wypis = new unsigned int[lk];
		for(j=0;j<lk;j++){
			cin>>name;
			ind = ktora(name,nazwy,k);
			sortuj(ind,dane,n,wypis,j);
			wypis[j]=ind;
		}

		for(j=0;j<lk;j++){
            if(j>0)cout<<" ";
            cout<<nazwy[wypis[j]];
		}cout<<endl;
		for(j=0;j<n;j++){
            for(m=0;m<lk;m++){
                if(m>0)cout<<" ";
                cout<<dane[j][wypis[m]];
            }cout<<endl;
		}
		delete []wypis;
		}
	}

	for(i=0;i<n;i++){
		delete []dane[i];
	}
	delete []nazwy;
	delete []dane;
	return 0;
}
