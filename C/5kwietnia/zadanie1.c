#include <stdio.h>
#include <stdlib.h>

struct element{
    int wartosc;
    struct element *nastepny;
};

struct element *list_insert_begining(int val, struct element *lst){
        /* Dodajemy wartosc na poczatku */
        lst->wartosc = val;
        /* Nadajemu wskaznik na nastepny element */
        lst->nastepny = NULL;
        /* Zwracamy poczatek listy */
        return lst;
}

struct element *list_insert_end(int val, struct element *lst){
        struct element *tmp = lst, *new;

        new =  malloc(sizeof(struct element));
        /* Dodajemy wartosc nowego elementu */
        new->wartosc = val;
        /* Nadajemu wskaznik na nastepny element */
        new->nastepny = NULL;

        /* Szukamy ostatniego elementu na liscie */
        while(tmp->nastepny != NULL){
                tmp = tmp->nastepny;
        }
        /* Wskazujemy na nowy element na koniec listy */
        tmp->nastepny = new;
        /* Zwracamy liste */
        return lst;
}

void list_print(struct element *lst){
    struct element *tmp = lst;

    /* Wyswielamy zawartosc */
    while (tmp != NULL) {
        printf("%d\n", tmp->wartosc);
        /* Przesuwamy sie na anstepny element */
        tmp = tmp->nastepny;
    }

}

int list_index_left(int val, struct element *lst){
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

int list_index_right(int val, struct element *lst){
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

int main(int argc, char **argv)
{
        struct element *lista;

        /* Nadajemy pamiec nowej liscie */
        lista = malloc(sizeof(struct element));
        /* Tworzymy nowa liste */
        lista = list_insert_begining(5, lista);

        /* Dodajemy element na koniec listy */
        lista = list_insert_end(15, lista);
        lista = list_insert_end(6, lista);
        lista = list_insert_end(9, lista);
        lista = list_insert_end(87, lista);
        lista = list_insert_end(91, lista);
        lista = list_insert_end(0, lista);
        lista = list_insert_end(67, lista);
        lista = list_insert_end(45, lista);

        /* Wyswietlamy zawartosc listy */
        list_print(lista);

        /* Wyswietlanie pierwszego indeksu z lewej strony wystapienia liczy 9 */
        printf("\n%d\n", list_index_left(9, lista));
        /* Wyswietlanie pierwszego indeksu z prawej strony wystapienia liczy 9 */
        printf("%d\n\n", list_index_right(9, lista));
        /* Sortujemy liste */
        lista = list_sort(lista);
        /* Wyswietlamy zawartosc listy */
        list_print(lista);
		
        /* Zwalniamy pamiec listy */
        delete_list(lista);

        return 0;
}
