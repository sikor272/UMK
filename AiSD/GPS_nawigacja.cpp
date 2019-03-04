#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#define inf 1<<30
using namespace std;
int nr_miasta(string *miasta,string miasto){
    int i=0;
    while(miasta[i]!="."){
        if(miasta[i]==miasto){
            return i;
        }
        i++;
    }
    miasta[i]=miasto;
    return i;
}
void szukaj(vector <int> *tab,int **odleglosc,int *droga,int start,int *pre,string *miasta){
    queue <int> kolejka;
    int i,a;
    kolejka.push(start);
    droga[start]=0;
    while(!kolejka.empty()){
        a=kolejka.front();
        kolejka.pop();
        for(i=0;i<tab[a].size();i++){
            if(droga[tab[a][i]]>droga[a]+odleglosc[a][tab[a][i]]){
                kolejka.push(tab[a][i]);
                droga[tab[a][i]]=droga[a]+odleglosc[a][tab[a][i]];
                pre[tab[a][i]]=a;
            }
        }
    }
}
void wypisz(int act,string *miasta,int *pre){
    if(pre[act]==-1){
        cout<<miasta[act];
        return;
    }
    wypisz(pre[act],miasta,pre);
    cout<<" -> "<<miasta[act];
    return;
}
int main(){
    int m,i,j,k,a,b,d;
    char poczatek[255],koniec[255];
    cin>>m;
    cin.ignore();
    int **dlugosc,*droga,*pre;
    dlugosc = new int * [2*m];
    droga = new int[2*m];
    pre = new int[2*m];
    vector <int> tab[2*m];
    string *miasta;
    miasta = new string[2*m];
    for(i=0;i<2*m;i++){
        droga[i]=inf;
        miasta[i]=".";
        pre[i]=-1;
        dlugosc[i]=new int[2*m];
    }
    for(i=0;i<m;i++){
        gets(poczatek);
        a=nr_miasta(miasta,poczatek);

        gets(koniec);
        b=nr_miasta(miasta,koniec);

        cin>>d;
        cin.ignore();

        dlugosc[a][b]=d;
        tab[a].push_back(b);
    }

    gets(poczatek);
    a=nr_miasta(miasta,poczatek);
    gets(koniec);
    b=nr_miasta(miasta,koniec);
    szukaj(tab,dlugosc,droga,a,pre,miasta);
    if(droga[b]!=inf){
        wypisz(b,miasta,pre);
        cout<<endl<<droga[b];
    } else {
        cout<<"nie ma drogi";
    }
    return 0;
}
