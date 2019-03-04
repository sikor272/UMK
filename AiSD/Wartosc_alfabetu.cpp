#include <iostream>
using namespace std;
string litery(int n,string *napis,string alfabet,char znak){
	int i;
	for(i=0;i<alfabet.size();i++){
		if(alfabet[i]==znak){
			(*napis)[n]=(i+48);
			return alfabet;
		}
	}
	(*napis)[n]=(i+48);
	return alfabet+znak;
}
int main() {
	string *napis,alfabet="";
	int i,j,suma=0;
	napis=new string;
	getline(cin,*napis);
	for(i=0;i<(*napis).size();i++){
		alfabet=litery(i,napis,alfabet,(*napis)[i]);
	}
	for(i=0;i<(*napis).size();i++){
		suma=suma*alfabet.size()+(*napis)[i]-48;
	}
	cout<<suma;
	return 0;
}