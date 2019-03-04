#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

struct litera{
    char znak;
    int ile;
    string ciag;
};
struct hofman{
    int value;
    char znak;
    hofman *lewy;
    hofman *prawy;
};
struct compare
{
    template < class T > bool operator ()( const T & A, const T & B ) const {
        return A->value > B->value;
    }
};
void wypisz(hofman *element,string ciag,litera *tab){
    if(element->lewy==NULL){
        tab[element->znak].ciag=ciag;
        return;
    }
    wypisz(element->lewy,ciag+"0",tab);
    wypisz(element->prawy,ciag+"1",tab);
}
int main(){
    string napis;
    priority_queue <hofman*,vector<hofman*>,compare> kolejka;
    hofman *element;
    int i,liter=0;
    litera tab[255];
    for(i=0;i<255;i++){
        tab[i].znak=i;
        tab[i].ile=0;
    }
    getline(cin,napis);
    for(i=0;i<napis.size();i++){
        tab[napis[i]].ile++;
    }
    for(i=0;i<255;i++){
        element = new hofman;
        if(tab[i].ile>0){
            liter++;
            element->prawy=NULL;
            element->lewy=NULL;
            element->znak=tab[i].znak;
            element->value=tab[i].ile;
            kolejka.push(element);
        }
    }
    while(kolejka.size()>1){
        element = new hofman;
        element->lewy=kolejka.top();
        kolejka.pop();
        element->prawy=kolejka.top();
        kolejka.pop();
        element->value=element->lewy->value+element->prawy->value;
        kolejka.push(element);
    }
    element = kolejka.top();
    if(liter==1){
        tab[element->znak].ciag="0";
    } else {
        wypisz(element,"",tab);
    }
    for(i=0;i<napis.size();i++){
        cout<<tab[napis[i]].ciag;
    }
    return 0;
}