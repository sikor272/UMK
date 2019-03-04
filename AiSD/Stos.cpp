#include <iostream>
using namespace std;
struct stos{
	string napis;
	stos *next;
};
stos *dodaj(stos *start, string nap){
	stos *niu;
	niu = new stos;
	niu->next = start;
	niu->napis = nap;
	return niu;
}

int main() {
	stos *start;
	string linia;
	
	start = new stos;
	start = NULL;
	while(getline(cin,linia)){
		if(linia == "KONIEC"){
			break;
		}
		start=dodaj(start,linia);
	}
	while(start != NULL){
		cout<<start->napis<<endl;
		start = start->next;
	}
	return 0;
}