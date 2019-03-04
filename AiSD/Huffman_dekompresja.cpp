#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

struct litera{
    char znak;
    int ile;
};
struct hofman{
    int value;
    char znak;
    hofman *lewy;
    hofman *prawy;
    string ciag;
};
struct compare
{
    template < class T > bool operator ()( const T & A, const T & B ) const {
        return A->value > B->value;
    }
};
void wypisz(hofman *element,string napis,int *i){
    if(element->lewy==NULL){
        cout<<element->znak;
        return;
    }
   if(napis[*i]=='0'){
   *i=*i+1;
    wypisz(element->lewy,napis,i);
   }
   else{
   *i=*i+1;
    wypisz(element->prawy,napis,i);
   }
}
int main(){
    string napis;
    priority_queue <hofman*,vector<hofman*>,compare> kolejka;
    hofman *element,*element2;
    int i,liter=0,j,*u;
    u=new int;
    litera tab[255];
    int m;
    cin>>m;
    for(i=0;i<m;i++){
        element = new hofman;
        cin>>element->znak;
        cin>>element->value;
        element->prawy=NULL;
        element->lewy=NULL;
        kolejka.push(element);
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
    cin>>napis;
    for(*u=0;*u<napis.size();){
	if(m==1)*u++;
    	wypisz(element,napis,u);

    }
    return 0;
}