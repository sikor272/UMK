#include <iostream>
using namespace std;
struct drzewo{
	int value;
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
				korz->lewy = lisc;
				return;
			} else {
				buduj(korz->lewy,lisc);
			}
		} else {
			if(korz->prawy == NULL){
				korz->prawy = lisc;
				return;
			} else {
				buduj(korz->prawy,lisc);
			}
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

void preorder(drzewo *korzen){
	if(korzen == NULL){
		return;
	}
	preorder(korzen->lewy);
	preorder(korzen->prawy);
	cout<<korzen->value<<" ";
}

void postorder(drzewo *korzen){
	if(korzen == NULL){
		return;
	}
	cout<<korzen->value<<" ";
	postorder(korzen->lewy);
	postorder(korzen->prawy);
}

int main(){
	drzewo *lisc;
	int n;
	while(cin>>n){
		if(n==-999){
			break;
		}
		lisc = new drzewo;
		lisc->lewy = NULL;
		lisc->prawy = NULL;
		lisc->value = n;
		buduj(korzen,lisc);
	}
	inorder(korzen);cout<<"\n";
	postorder(korzen);cout<<"\n";
	preorder(korzen);
	return 0;
}