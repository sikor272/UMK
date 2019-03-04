#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

/* Deklaracja funkcji uzywanych w programie */
/* Pelne dzialanie funkcji ponizej maina */
void uprawnienia(struct stat statp);
void write_more_time(struct tm *czas);
void write_time(struct tm *czas);
void info(struct stat statp);
void more_info(struct stat statp, char *name);

int main(int argc, char *argv[]) {
	/* Zmienne potrzebne do zapamietywania inforamcji o katalogu, plikach */
	DIR* dirp;
	struct dirent* direntp;
	struct stat statp;
	int rozmiar;
	char *link;

	/* Jezeli uruchomimy bez dodatkowych argumentow dzialanie jak 'ls -al' */
	if(argc == 1){
		/* Otwieramy aktualny katalog i sprawdzamy czy mamy dostep */
		dirp = opendir(".");
		if(dirp == NULL){
			perror("Odmowa dostepu");
			return -1;
		}
		/* Przegladamy wszystkie pliki znajdujace sie w aktualnym katalogu */
		for(;;) {
			direntp = readdir(dirp);
			/* Jezeli nie mamy juz plikow konczymy */
			if(direntp == NULL){
				break;
			}
			/* Pobieramy inforacje o pliku */
			if(stat(direntp->d_name, &statp) < 0){
				perror("Nie ma takiego pliku lub katalogu lub odmowa dostepu");
				return -1;
			}
			/* Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje */
			if((S_IFLNK & statp.st_mode) && lstat(direntp->d_name, &statp) < 0){
				perror("Nie ma takiego pliku lub katalogu lub odmowa dostepu");
				return -1;
			}
			/* Wypisujemy podstawowe informacje za pomoca funkcji */
			info(statp);
			printf("%s", direntp->d_name);
			/* Jezeli byl to link, wypisujemy na co wskazuje */
			if((S_IFLNK & statp.st_mode) == S_IFLNK){
				link = malloc(statp.st_size + 1);
				rozmiar = readlink(direntp->d_name, link, statp.st_size + 1);
				link[rozmiar] = '\0';
				printf(" -> %s", link);
			}
			printf("\n");
		}
		/* Zamykamy katalog i konczymy powodzeniem*/
		closedir(dirp);
		return 0;
	} else if(argc == 2){ /* Jezeli uruchamiamy program z dodatkowym argumentem */
		/* Pobieramy inforacje o pliku */
		if(stat(argv[1], &statp) < 0){
			perror("Nie ma takiego pliku lub katalogu lub odmowa dostepu");
			return -1;
		}
		/* Jezeli byl to link to o nim, a nie o pliku na ktory wskazuje */
		if((S_IFLNK & statp.st_mode) && lstat(argv[1], &statp) < 0){
			perror("Nie ma takiego pliku lub katalogu lub odmowa dostepu");
			return -1;
		}
		/* Wypisujemy wszystkie informacje za pomoca funkcji */
		more_info(statp, argv[1]);
	} else {
		/* Jezeli podalismy za duzo argumentow konczymy bledem */
		perror("Za duzo argumentow");
		return -1;
	}
	return 0;
}
/* Funkcja wypisujaca uprawnienia pliku */
void uprawnienia(struct stat statp){
	if(statp.st_mode & S_IRUSR){
		printf("r");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IWUSR){
		printf("w");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IXUSR){
		printf("x");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IRGRP){
		printf("r");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IWGRP){
		printf("w");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IXGRP){
		printf("x");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IROTH){
		printf("r");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IWOTH){
		printf("w");
	} else {
		printf("-");
	}
	if(statp.st_mode & S_IXOTH){
		printf("x");
	} else {
		printf("-");
	}
	return;
}
/* Funckja wypisujaca czas podstawowy */
void write_time(struct tm *czas){
	/* Tablica z nazwami miesiaca */
	char miesiace[12][4]={{"sty\0"},{"lut\0"},{"mar\0"},{"kwi\0"},{"maj\0"},{"cze\0"},{"lip\0"},{"sie\0"},{"wrz\0"},{"paz\0"},{"lis\0"},{"gru\0"}};
	
	printf("%2d ", czas->tm_mday);
    printf("%s ", miesiace[czas->tm_mon]);
	printf("%2d:", czas->tm_hour);
	if(czas->tm_min < 10){
		printf("0%d ", czas->tm_min);
	} else {
		printf("%d ", czas->tm_min);
	}
}
/* Funkcja wypisujaca dokladniejsza date */
void write_more_time(struct tm *czas){
	/* Tablica z nazwami miesiaca */
	char miesiace[12][14]={"stycznia\0","lutego\0","marca\0","kwietnia\0","maja\0","czerwca\0","lipca\0","sierpnia\0","wrzesnia\0","pazdziernika\0","listopada\0","grudnia\0"};
	
	printf("%2d ", czas->tm_mday);
	printf("%13s", miesiace[czas->tm_mon]);
	printf("%5d roku o ", czas->tm_year + 1900);
	printf("%2d:", czas->tm_hour);
	if(czas->tm_min < 10){
		printf("0%d:", czas->tm_min);
	} else {
		printf("%d:", czas->tm_min);
	}
	if(czas->tm_sec < 10){
		printf("0%d", czas->tm_sec);
	} else {
		printf("%d", czas->tm_sec);
	}
}
/* Funcka do wypisania szczegolowych informacji o pliku */
void more_info(struct stat statp, char *name){
	struct tm *czas;
	char *link;
	FILE *plik;
	char napis;
	int i = 0;

	printf("Informacje o %s:\n", name);
	printf("Typ pliku:   ");
	/* Sprawdzenie jaki to typ pliku */
	if((S_IFDIR & statp.st_mode) == S_IFDIR){
		printf("katalog\n");
	} else if((S_IFLNK & statp.st_mode) == S_IFLNK){
		printf("link symboliczny\n");
	} else if((S_IFSOCK & statp.st_mode) == S_IFSOCK){
		printf("socket\n");
	} else if((S_IFIFO & statp.st_mode) == S_IFIFO){
		printf("fifo\n");
	} else if((S_IFCHR & statp.st_mode) == S_IFCHR){
		printf("urzadzenie\n");
	} else if((S_IFBLK & statp.st_mode) == S_IFBLK){
		printf("urzadzenie blokowe\n");
	} else if((S_IFREG & statp.st_mode) == S_IFREG){
		printf("zwykly plik\n");
		i = 1;
	} else {
		printf("nieznany typ\n");
	}

	/* Sprawdzenie sciezki do pliku */
	printf("Sciezka:     ");
	/* Jezeli niebyl to link */
	if(!((S_IFLNK & statp.st_mode) == S_IFLNK)){
		link = realpath(name, NULL);
		printf("%s\n", link);
	} else {
		/* Jezeli byl to link */
		link = realpath(".", NULL);
		printf("%s/%s\n", link, name);
		printf("Wskazuje na: ");
		link = realpath(name, NULL);
		printf("%s\n", link);
	}

	/* Wypisanie rozmiaru */
	printf("Rozmiar:     %ld ", statp.st_size);
	if(statp.st_size == 1){
		printf("bajt\n");
	} else if((statp.st_size%10) < 4){
		printf("bajty\n");
	} else {
		printf("bajtow\n");
	}

	printf("Uprawnienia: ");
	uprawnienia(statp);
	printf("\n");

	/* Wypisanie ostatniego czasu dostepu */
	czas = localtime(&statp.st_atime);
	printf("Ostatnio uzywany:        ");
	write_more_time(czas);
	printf("\n");
	/* Wypisanie ostatniego czasu modyfikacji */
	czas = localtime(&statp.st_mtime);
	printf("Ostatnio modyfikowany:   ");
	write_more_time(czas);
	printf("\n");
	/* Wypisanie ostatniego czasu zmiany */
	czas = localtime(&statp.st_ctime);
	printf("Ostatnio zmieniany stan: ");
	write_more_time(czas);
	printf("\n");

	/* Jezeli byl to zwykly plik wypisujemy 80 pierwszych znakow */
	if(i){
		printf("Poczatek zawartosci:\n");
		if((plik=fopen(name,"r"))== NULL){
			perror("Nie udalo sie otworzyc pliku");
			exit(-1);
		}
		for(i=0;i<80;i++){
			fscanf(plik, "%c" , &napis);
			printf("%c", napis);
		}
		printf("\n");

		fclose(plik);
	}

	return;
}
/* Funcka do wypisania podstawowych informacji o pliku */
void info(struct stat statp){
	struct passwd *user;
	struct group *groups;
	struct tm *czas;
	
	/* Pobieramy informacje o uzytkowniku */
	if((user = getpwuid(statp.st_uid)) == NULL){
		perror("Nie ma dostepu do danych uzytkownika");
		exit(-1);
	}
	/* Pobieramy inforamcje o grupie */
	if((groups = getgrgid(statp.st_gid)) == NULL){
		perror("Nie ma dostepu do danych grupy uzytkownika");
		exit(-1);
	}

	czas = localtime(&statp.st_mtime);
	/* Sprawdzenie jaki to typ pliku */
	if((S_IFDIR & statp.st_mode) == S_IFDIR){
		printf("d");
	} else if((S_IFLNK & statp.st_mode) == S_IFLNK){
		printf("l");
	} else if((S_IFSOCK & statp.st_mode) == S_IFSOCK){
		printf("s");
	} else if((S_IFIFO & statp.st_mode) == S_IFIFO){
		printf("p");
	} else if((S_IFCHR & statp.st_mode) == S_IFCHR){
		printf("c");
	} else if((S_IFBLK & statp.st_mode) == S_IFBLK){
		printf("b");
	} else {
		printf("-");
	}
	/* Wypisanie uprawnien */
	uprawnienia(statp);
	/* Wypisanie ilosci twardych dowiazan */
	printf("%4d", (int)statp.st_nlink);
	/* Wypisanie nazwy uzytkownika */
	printf("%10s", user->pw_name);
	/* Wypisanie grupy uzytkownika */
	printf("%10s", groups->gr_name);
	/* Wypisanie rozmiaru pliku */
	printf("%7ld ", statp.st_size);
	/* Wypisanie ostatniego czasu modyfikacji */
	write_time(czas);
	return;
}

