#include <iostream>
using namespace std;
struct drzewo{
	int value;
	drzewo *ojciec;
	drzewo *lewy;
	drzewo *prawy;
};
drzewo *korzen = NULL;

void buduj(drzewo *korz,drzewo *lisc){
	if(korzen == NULL){
		korzen = lisc;
	} else {
		if(lisc->value < korz->value){
			if(korz->lewy == NULL){
				lisc->ojciec = korz;
				korz->lewy = lisc;
				return;
			} else {
				buduj(korz->lewy,lisc);
			}
		} else {
			if(korz->prawy == NULL){
				lisc->ojciec = korz;
				korz->prawy = lisc;
				return;
			} else {
				buduj(korz->prawy,lisc);
			}
		}
	}
}
void usun(drzewo *lisc,int n){
	if(lisc == NULL){
		return;
	}
	if(n < lisc->value){
		usun(lisc->lewy,n);
		return;
	}
	if(n > lisc->value){
		usun(lisc->prawy,n);
		return;
	}
	if(lisc->prawy == NULL && lisc->lewy == NULL){
		if(lisc->ojciec->lewy == lisc){
			lisc->ojciec->lewy = NULL;
		} else {
			lisc->ojciec->prawy = NULL;
		}
		return;
	}
	if(lisc->prawy == NULL){
		if(lisc->ojciec->lewy == lisc){
			lisc->ojciec->lewy = lisc->lewy;
		} else {
			lisc->ojciec->prawy = lisc->lewy;
		}
		return;
	}
	if(lisc->lewy == NULL){
		if(lisc->ojciec->lewy == lisc){
			lisc->ojciec->lewy = lisc->prawy;
		} else {
			lisc->ojciec->prawy = lisc->prawy;
		}
	}
	
	
	
}
void inorder(drzewo *korzen){
	if(korzen == NULL){
		return;
	}
	inorder(korzen->lewy);
	cout<<korzen->value<<" ";
	inorder(korzen->prawy);
}



int main(){
	drzewo *lisc;
	int n;
	while(cin>>n){
		if(n==-999){
			break;
		}
		lisc = new drzewo;
		lisc->ojciec = NULL;
		lisc->lewy = NULL;
		lisc->prawy = NULL;
		lisc->value = n;
		buduj(korzen,lisc);
	}
	while(cin>>n){
		if(n==-999){
			break;
		}
		usun(korzen,n);
	}
	inorder(korzen);
	
	return 0;
}