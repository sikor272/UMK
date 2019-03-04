#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>
#define inf 1<<30
using namespace std;
bool check(int *pre,int act){
    int start;
    start=act;
    while(true){
        if(act == -1 || act == 0){
            return true;
        }
        act = pre[act];
        if(act == start){
            return false;
        }
    }
}
void szukaj(vector<int> *dane,bool *bylo,int *pre,float **dlu,float *odl){
    queue<int> kolejka;
    int i,a,b;
    bool can;
    kolejka.push(0);
    odl[0]=0;
    bylo[0]=0;
    while(!kolejka.empty()){
        a=kolejka.front();
        kolejka.pop();
        for(i=0;i<dane[a].size();i++){
            b=pre[dane[a][i]];
            pre[dane[a][i]]=a;
            can=check(pre,a);

            pre[dane[a][i]]=b;
            if(odl[dane[a][i]]>(dlu[a][dane[a][i]])&&can){
                odl[dane[a][i]]=dlu[a][dane[a][i]];
                pre[dane[a][i]]=a;
            }
        }
        for(i=0;i<dane[a].size();i++){
            if(bylo[dane[a][i]]){
                kolejka.push(dane[a][i]);
                bylo[dane[a][i]]=0;
            }
        }
    }
    return;
}
int main(){
    int wierz,kraw,i,j,k,a,b;
    float c,suma=0;
    cin>>wierz;
    cin>>kraw;
    int pre[wierz];
    vector<int>dane[wierz];
    bool bylo[wierz];
    float **dlug;
    dlug=new float*[wierz];
    float odl[wierz];
    for(i=0;i<wierz;i++){
        *(dlug+i)=new float[wierz];
        odl[i]=inf;
        pre[i]=-1;
        bylo[i]=1;
    }
    for(i=0;i<kraw;i++){
        cin>>a>>b>>c;
        dane[a].push_back(b);
        dane[b].push_back(a);
        dlug[a][b] = dlug[b][a] = c;
    }
    szukaj(dane,bylo,pre,dlug,odl);
    for(i=0;i<wierz;i++){
     suma+=odl[i];
    }
    printf("%.2f",suma);
    return 0;
}
