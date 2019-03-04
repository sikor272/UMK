#include <iostream>
using namespace std;
struct drzewo {
	int value;
	drzewo *ojciec;
	drzewo *lewy;
	drzewo *prawy;
};
drzewo *korzen = NULL;

void buduj(drzewo *korz, drzewo *lisc) {
	if (korzen == NULL) {
		korzen = lisc;
	}
	else {
		if (lisc->value < korz->value) {
			if (korz->lewy == NULL) {
				lisc->ojciec = korz;
				korz->lewy = lisc;
				return;
			}
			else {
				buduj(korz->lewy, lisc);
			}
		}
		else {
			if (korz->prawy == NULL) {
				lisc->ojciec = korz;
				korz->prawy = lisc;
				return;
			}
			else {
				buduj(korz->prawy, lisc);
			}
		}
	}
}

void szukaj(drzewo *lisc) {
	if (lisc == NULL) {
		cout << "!";
		return;
	}
	while (lisc->prawy != NULL) {
		lisc = lisc->prawy;
	}
	cout << lisc->value;
	
	if(lisc->ojciec == NULL){
		if(lisc->lewy != NULL){
			korzen = lisc->lewy;
			korzen->ojciec = NULL;
			return;
		} else {
			korzen = NULL;
			return;
		}
	}
	
	lisc->ojciec->prawy = NULL;
	
	if(lisc->lewy != NULL){
		lisc->ojciec->prawy = lisc->lewy;
		lisc->lewy->ojciec = lisc->ojciec;
		return;
	}
	
	return;
}


int main() {
	drzewo *lisc;
	char znak,s='s';
	int n;
	while (cin >> znak) {
		if (znak == 'x') {
			break;
		}
		if (znak == 'i') {
			cin >> n;
			lisc = new drzewo;
			lisc->ojciec = NULL;
			lisc->lewy = NULL;
			lisc->prawy = NULL;
			lisc->value = n;
			buduj(korzen, lisc);
		}
		if (znak == 'e') {
			szukaj(korzen);
			cout<<" ";
		}
		
	}
	
		
	

	return 0;
}