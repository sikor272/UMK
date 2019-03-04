#include <stdio.h>
#include <stdlib.h>

struct element{
    long long int wartosc;
    struct element *nastepny;
};

struct element *list_insert_begining(long long int val, struct element *lst){
        /* Dodajemy wartosc na poczatku */
        lst->wartosc = val;
        /* Nadajemu wskaznik na nastepny element */
        lst->nastepny = NULL;
        /* Zwracamy poczatek listy */
        return lst;
}

struct element *list_insert_end(long long int val, struct element *lst){
        struct element *tmp = lst, *nowy;

        nowy =  malloc(sizeof(struct element));
        /* Dodajemy wartosc nowego elementu */
        nowy->wartosc = val;
        /* Nadajemu wskaznik na nastepny element */
        nowy->nastepny = NULL;

        /* Szukamy ostatniego elementu na liscie */
        while(tmp->nastepny != NULL){
                tmp = tmp->nastepny;
        }
        /* Wskazujemy na nowy element na koniec listy */
        tmp->nastepny = nowy;
        /* Zwracamy liste */
        return lst;
}

void list_print(struct element *lst){
    struct element *tmp = lst;

    /* Wyswielamy zawartosc */
    while (tmp != NULL) {
        printf("%lli\n", tmp->wartosc);
        /* Przesuwamy sie na anstepny element */
        tmp = tmp->nastepny;
    }

}

int list_index_left(long long int val, struct element *lst){
        int j = 0;
        struct element *tmp = lst;

    /* Przeszukujemy liste */
    while (tmp != NULL) {
                /* Przy znaleziemu danego elementu zwracamy aktualny indeks */
        if(tmp->wartosc == val){
                        return j;
                }
                tmp = tmp->nastepny;
        j++;
    }
    /* Jezeli dany element nie znajdowal sie w liscie zwracamy -1 */
    return -1;
}

int list_index_right(long long int val, struct element *lst){
        int indeks = -1, j = 0;
        struct element *tmp = lst;

    /* Przeszukujemy liste */
    while (tmp != NULL) {
                /* Przy znaleziemu danego elementu zapamietujemy aktualny indeks */
        if(tmp->wartosc == val){
                        indeks = j;
                }
                tmp = tmp->nastepny;
        j++;
    }
    /* Zwracamy wartosc indeksu */
    return indeks;
}

void delete_list(struct element *lst){
    struct element *tmp = lst;

    /* Czyscimy liste */
    while (tmp != NULL) {
                /* Wzkazujemy na nastepny element */
        tmp = tmp->nastepny;
        /* Czyscimy wartosc aktualnego */
        free(lst);
        /* Zapamietujemy nastepny jako aktualny */
        lst = tmp;
    }
}
struct element *list_sort(struct element *lst){
        struct element *nowa = lst;
        struct element *tmp;
        struct element *next;
        struct element *last;
        
        /* Zapamietujemy nastepny element */
        tmp = lst->nastepny;
        /* Ustawiamy pierwszy element jako jedyny*/
        nowa->nastepny = NULL;
        
        /* Do puki nie posortujemy calej listy wejsicowej */
        while(tmp != NULL){
        	/* Zapamietujemy aktualny element do wstawienia */
        	next = tmp;
        	/* Przesuwamy sie o jeden element w gore rzeby nie zgubic reszty listy */
        	tmp = tmp->nastepny;
        	/* Jezeli aktualna wartosc jest mniejsza od poczatku ustawiamy nowy poczatek na nia i wskazujemy cala liste jako nastepny */
        	if(next->wartosc < nowa->wartosc){
        		next->nastepny = nowa;
        		nowa = next;
			} else {
				last = nowa;
				/* W przeciwnym wypadku szukamy ostatniego niepustego elementu jednoczescnie nie wiekszego od aktualnego */
				while(last->nastepny != NULL && next->wartosc > last->nastepny->wartosc ){
					last = last->nastepny;
				}
				/* Zapisujemy ogon listy od aktualnego elementu do aktualnie sprawdzanego */
				next->nastepny = last->nastepny;
				/* Zapamietujemy aktualny element */
				last->nastepny = next;
			}
		}
		/* Zwracamy posortowana liste */
		return nowa;
        
}
int parzyste(struct element *lst){
    struct element *tmp = lst;
	int j = 0;
    
	while (tmp != NULL) {
    	/* Jezeli element jest przysty dodajemy do sumu 1 */
        if(tmp->wartosc % 2 == 0){
        	j++;
		}
        /* Przesuwamy sie na nastepny element */
        tmp = tmp->nastepny;
    }
	/* Zwracamy ilosc parzystych elementow */
	return j;
}

int mini(struct element *lst){
    struct element *tmp = lst;
	int j = tmp->wartosc;
    
	while (tmp != NULL) {
    	/* Jezeli element jest mniejszy zamieniamy */
        if(tmp->wartosc < j){
        	j = tmp->wartosc;
		}
        /* Przesuwamy sie na nastepny element */
        tmp = tmp->nastepny;
    }
	/* Zwracamy najmniejszy element */
	return j;
}

int maxi(struct element *lst){
    struct element *tmp = lst;
	int j = tmp->wartosc;
    
	while (tmp != NULL) {
    	/* Jezeli element jest wiekszy zamieniamy */
        if(tmp->wartosc > j){
        	j = tmp->wartosc;
		}
        /* Przesuwamy sie na nastepny element */
        tmp = tmp->nastepny;
    }
	/* Zwracamy najwiekszy element */
	return j;
}

int main(int argc, char **argv)
{
        struct element *lista,*tmp;
		FILE *plik,*plik2;
		char linia[15];
		long long int liczba;
		
		/* Otwieramy plik */
		plik = fopen("liczby.txt","r");
		plik2 = fopen("wynik.txt","w");
        if(plik == NULL || plik2 == NULL){
        	printf("Nie udalo sie otworzyc pliku!\n");
        	return -1;
		}
		
		fscanf(plik, "%lli", &liczba);
		/* Nadajemy pamiec nowej liscie */
        lista = malloc(sizeof(struct element));
        /* Tworzymy nowa liste */
        lista = list_insert_begining(liczba, lista);
		while(fscanf(plik, "%s", &linia) != EOF)
		{
			sscanf(linia, "%lli", &liczba);
			/* Dodajemy element na koniec listy */
			lista = list_insert_end(liczba, lista);
			
		}
        
		/* Wyswietlanie pierwszego indeksu z lewej strony wystapienia liczy 17 */
        printf("\nPierwsze wystapienie 17: %d\n", list_index_left(17, lista));
        /* Wyswietlanie pierwszego indeksu z prawej strony wystapienia liczy 17 */
        printf("Ostatnie wystapienie 17: %d\n\n", list_index_right(17, lista));

		/* Sortujemy liste */
      	lista = list_sort(lista);
        /* Wyswietlamy zawartosc listy */
        printf("Posortowana lista:\n");
        list_print(lista);
        
        /* Sprawdzamy ile jest parzystych elementow */
        printf("Ilosc parzystych: %d\n\n", parzyste(lista));
		
		/* Sprawdzamy minimalny oraz maksymalny element */
		printf("Min: %d, Max: %d\n", mini(lista), maxi(lista));
		
		/* Zapisujemy liczby mniejsze od pierwszej */
		liczba = 1;
		while(liczba < lista->wartosc){
			fprintf(plik2, "%lli\n", liczba);
			liczba++;
		}
		/* Zapisujemy posortowana liste */
		tmp = lista;
		while(tmp != NULL){
			fprintf(plik2, "%lli\n", tmp->wartosc);
			tmp = tmp->nastepny;
		}
		
        /* Zwalniamy pamiec listy */
        delete_list(lista);
		fclose(plik);
        return 0;
}
