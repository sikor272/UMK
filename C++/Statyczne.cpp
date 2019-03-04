#include <iostream>
using namespace std;
class statyczne{
private:
    static int wszystkie;
    static int aktualnie;
    static void dodaj(){
        wszystkie++;
        aktualnie++;
    }
    static void odjac(){
        aktualnie--;
    }
public:
    statyczne(){
        dodaj();
    }
    int zwroc_w(){
        return wszystkie;
    }
    int zwroc_a(){
        return aktualnie;
    }
    ~statyczne(){
        odjac();
    }
};

int statyczne::wszystkie = 0;
int statyczne::aktualnie = 0;
int main(){
    statyczne *wsk,*wsk2;
    char znak;
    while(cin >> znak){
        if(znak == '+'){
            wsk = new statyczne;
        } else if(znak == '-'){
            delete wsk;
        } else if(znak == '0'){
            break;
        }
    }
    cout << wsk2->zwroc_w();
    cout << endl;
    cout << wsk2->zwroc_a();
    delete wsk2;
    return 0;
}
