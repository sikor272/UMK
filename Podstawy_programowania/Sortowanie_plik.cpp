#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
using namespace std;
/*
	Sortowanie przez scalanie danych w pliku
	Dawid Sikorski
*/
void scalanie(string nazwa,string nazwa_old,int ilosc){
	int podzial=0;
	int aktualny=0;
	int prawa,lewa;
	int nastepny=aktualny+1;
	string nazwa_zapis,nazwa_odczyt_1,nazwa_odczyt_2;
	fstream zapis,odczyt_jeden,odczyt_dwa;
	string usun_prawy,usun_lewy;
	bool jest_prawa,jest_lewa;
	while(podzial<(ilosc/2)+1){
		stringstream ss,ss2,ss3;
		// Zamieniamy liczbe na ciag znakow
		ss3 << podzial;
		ss3 >> nazwa_zapis;
		
		// Zamieniamy liczbe na ciag znakow
		ss << aktualny;
		ss >> nazwa_odczyt_1;
		
		// Zamieniamy liczbe na ciag znakow
		ss2 << nastepny;
		ss2 >> nazwa_odczyt_2;
		// Jezelimamy wylacznie jeden plik do scalenia zostanie zmieniona mu nazwa
		if(nastepny>ilosc){
			usun_lewy=nazwa_old+nazwa_odczyt_1+".txt";
			nazwa_zapis=nazwa+nazwa_zapis+".txt";
			char * usun=new char[usun_lewy.size()+1];
			char * nowa=new char[nazwa_zapis.size()+1];
			copy(usun_lewy.begin(),usun_lewy.end(),usun);
			usun[usun_lewy.size()]='\0';
			copy(nazwa_zapis.begin(),nazwa_zapis.end(),nowa);
			nowa[nazwa_zapis.size()]='\0';
			rename(usun,nowa);
			delete[] usun;
			delete[] nowa;
		}else{
			// Otwieramy plik do zapisu
			zapis.open(nazwa+nazwa_zapis+".txt",ios::out);
			// Oraz pliki do odczytu
			odczyt_jeden.open(nazwa_old+nazwa_odczyt_1+".txt",ios::in);
			odczyt_dwa.open(nazwa_old+nazwa_odczyt_2+".txt",ios::in);
			// W przeciwnym przypadku pobieramy element z jednego i drugiego pliku az do wyczerpania
			jest_prawa=false;
			jest_lewa=false;
			if(!odczyt_jeden.eof()){
				odczyt_jeden>>lewa;
				jest_lewa=true;
			}
			if(!odczyt_dwa.eof()){
				odczyt_dwa>>prawa;
				jest_prawa=true;
			}
			while(jest_prawa || jest_lewa){
				// Jezeli element z 1 pliku jest mniejszy bad rowny od elementu z 2 pliku i oba pliki sa niepuste
				if(lewa<=prawa && jest_prawa && jest_lewa){
					zapis<<lewa<<"\n";
					if(!odczyt_jeden.eof()){
						odczyt_jeden>>lewa;
						if(!odczyt_jeden.eof())
							jest_lewa=true;
						else
							jest_lewa=false;
					}
				}else // Jezeli element z 1 pliku jest wiekszy od elementu z 2 pliku i oba pliki sa niepuste
				if(lewa>prawa && jest_prawa && jest_lewa){
					zapis<<prawa<<"\n";
					if(!odczyt_dwa.eof()){
						odczyt_dwa>>prawa;
						if(!odczyt_dwa.eof())
							jest_prawa=true;
						else
							jest_prawa=false;
					}
				}else // Jezeli pozostal nam tylko 2 plik to przepisujemy dalej
				if(jest_prawa){
					zapis<<prawa<<"\n";
					if(!odczyt_dwa.eof()){
						odczyt_dwa>>prawa;
						if(!odczyt_dwa.eof())
							jest_prawa=true;
						else
							jest_prawa=false;
					}
				}else // Jezeli pozostal nam tylko 1 plik to przepisujemy dalej
				if(jest_lewa){
					zapis<<lewa<<"\n";
					if(!odczyt_jeden.eof()){
						odczyt_jeden>>lewa;
						if(!odczyt_jeden.eof())
							jest_lewa=true;
						else
							jest_lewa=false;
					}
				}
			}
			// Zamykamy oraz usuwamy niepotrzebne pliki
			odczyt_jeden.close();
			odczyt_dwa.close();
			usun_lewy=nazwa_old+nazwa_odczyt_1+".txt";
			usun_prawy=nazwa_old+nazwa_odczyt_2+".txt";
			char * usun_left=new char[usun_lewy.size()+1];
			char * usun_right=new char[usun_prawy.size()+1];
			copy(usun_lewy.begin(),usun_lewy.end(),usun_left);
			copy(usun_prawy.begin(),usun_prawy.end(),usun_right);
			usun_left[usun_lewy.size()]='\0';
			usun_right[usun_prawy.size()]='\0';
			remove(usun_left);
			remove(usun_right);
			delete[] usun_left;
			delete[] usun_right;
			zapis.close();
		}
		podzial++;
		aktualny+=2;
		nastepny+=2;
	}
}
int main(){
	// Wykonujemy podzial na pliki w ktorych tworzymy niemalejace ciagi
	fstream plik,nowy;
	stringstream ss;
	plik.open("dane.txt",ios::in);
	int aktualna,ostatnia,licznik,ilosc;
	ilosc=0;
	licznik=0;
	string nazwa,nazwa_zapis;
	nazwa="podzial";
	ss << ilosc;
	ss >> nazwa_zapis;
	nowy.open(nazwa+nazwa_zapis+".txt",ios::out);
	// Przeszukujemy az do konca pliku
	while(!plik.eof()){
		plik>>aktualna;
		// Na poczatku musimy zapamietac element z ktorym bedziemy porownywac
		// w dalszej czesci bedizemy go zmieniac
		if(licznik==0){
			ostatnia=aktualna;
			licznik=1;
		}
		// Jezeli sany element nie jesst mniejszy dopisujemy do zawartosci i-tego pliku
		if(aktualna>=ostatnia){
			nowy<<aktualna<<"\n";
			ostatnia=aktualna;
		}else{
			// W przeciwnym razie zamykamy plik i otwieramy nowy
			ilosc++;
			nowy.close();
			// Zamieniamy liczbe na ciag znakow
			stringstream ss;
			ss << ilosc;
			ss >> nazwa_zapis;
			nowy.open(nazwa+nazwa_zapis+".txt",ios::out);
			nowy<<aktualna<<"\n";
			ostatnia=aktualna;
		}
	}
	nowy.close();
	string nazwa_plik,numer;
	nazwa_plik="sortowanie";
	int nr_sortowania=0;
	// Sortujemy az pozostanie nam jeden plik
	while(ilosc!=0){
		stringstream ss;
		ss << nr_sortowania;
		ss >> numer;
		// Podajemy nowa nazwe pliku, stara oraz aktualna ilosc
		// Nowa nazwa jest rozna od starej ze wzgledu na kolizje zapisu i odczytu
		scalanie(nazwa_plik+numer,nazwa,ilosc);
		nazwa=nazwa_plik+numer;
		// Ilosc plikow zostaje zmiejszona o polowe
		ilosc/=2;
		nr_sortowania++;
	}
	string dane,wynik;
	dane=nazwa_plik+numer+"0.txt";
	wynik="wynik_sortowania.txt";
	char * zamiana=new char[dane.size()+1];
	char * nowka=new char[wynik.size()+1];
	copy(dane.begin(),dane.end(),zamiana);
	zamiana[dane.size()]='\0';
	copy(wynik.begin(),wynik.end(),nowka);
	nowka[wynik.size()]='\0';
	rename(zamiana,nowka);
	delete[] zamiana;
	delete[] nowka;
	return 0;
}
