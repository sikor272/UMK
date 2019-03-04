struct pliczek{
	int plik;
	int pusty;
};
struct polacz{
	int tryb;
	char nazwa[2048];
};
struct pobieranie{
	int plik;
	int pozycja;
	int przesun;
};
struct zwroc{
	int ilosc;
	char dane[2048];
};
struct wyslij{
	int plik;
	char dane[2048];
};

program NFS{
	version NFS_1{
		pliczek start(polacz) = 1;
		zwroc pull(pobieranie) = 2;
		int push(wyslij) = 3;
		int koniec(int) = 4;
	} = 1;
} = 0x2d24ffa2;