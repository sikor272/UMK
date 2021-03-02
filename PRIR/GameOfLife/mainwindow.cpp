#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <QTimerEvent>
#include <QTimer>
#include <QDebug>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Pobieramy wymiary i wspolrzedne lewego gornego naroznika ramki
    // i ustawiamy wartosci odpowiednich pol
    // Uwaga: ramke "rysujFrame" wykorzystujemy tylko do
    // wygodnego ustaiwenia tych wymiarow. Rysunek bedziemy wyswietlac
    // bezposrednio w glownym oknie aplikacji.
    szerokosc = ui->PaintFrame->width();
    wysokosc = ui->PaintFrame->height();
    poczatekX = ui->PaintFrame->x();
    poczatekY = ui->PaintFrame->y();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szerokosc, wysokosc, QImage::Format_RGB32);
    timer = new QTimer(this);
    czysc();
    omp_set_num_threads(omp_get_max_threads());
    iloscWiersz = static_cast<int>(ceil(wysokosc / static_cast<double>(rozmiar)));
    iloscKolumna = static_cast<int>(ceil(szerokosc / static_cast<double>(rozmiar)));
    tablica = new int*[iloscWiersz];
    int i, j;
    // Przyporzadkowywanie watku do obrotu petli
    #pragma omp parallel for private(i, j) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        tablica[i] = new int[iloscKolumna];
        for(j = 0; j < iloscKolumna; j++)
        {
            tablica[i][j] = 0;
        }
    }
    srand(static_cast<unsigned>(time(NULL)));
    losowanie();
}

MainWindow::~MainWindow()
{
    int i;
    #pragma omp parallel for private(i) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        delete [] tablica[i];
    }
    delete [] tablica;
    delete ui;
}

// Funkcja "odmalowujaca" komponent
void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczatekX,poczatekY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczatekX, poczatekY, *img);
}

void MainWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;
    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();
    int i,j;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wysokosc; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szerokosc; j++)
        {
            ptr[szerokosc*4*i + 4*j + 0] = 255; // Skladowa BLUE
            ptr[szerokosc*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szerokosc*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
    update();
}

void MainWindow::reset()
{
    int i, j;
    #pragma omp parallel for private(i) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
         delete [] tablica[i];
    }
    delete [] tablica;
    iloscWiersz = static_cast<int>(ceil(wysokosc / static_cast<double>(rozmiar)));
    iloscKolumna = static_cast<int>(ceil(szerokosc / static_cast<double>(rozmiar)));
    tablica = new int*[iloscWiersz];
    #pragma omp parallel for private(i, j) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        tablica[i] = new int[iloscKolumna];
        for(j = 0; j < iloscKolumna; j++)
        {
            tablica[i][j] = 0;
        }
    }
}

void MainWindow::rysujPiksel(int x, int y, int red, int green, int blue)
{
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szerokosc && y < wysokosc){
        ptr[szerokosc * 4 * y + 4 * x] = static_cast<unsigned char>(blue);
        ptr[szerokosc * 4 * y + 4 * x + 1] = static_cast<unsigned char>(green);
        ptr[szerokosc * 4 * y + 4 * x + 2] = static_cast<unsigned char>(red);
    }
}
void MainWindow::rysujPole(int y, int x)
{
    int i, j;
    for(i = x; i < x + rozmiar; i++)
    {
        for(j = y; j < y + rozmiar; j++)
        {
            rysujPiksel(i, j, 255, 0, 0);
        }
    }
}
// Sprawdzenie czy sasiad zyje
int MainWindow::sasiedzi(int x, int y)
{
    if(x >= 0 && x < iloscWiersz && y >= 0 && y < iloscKolumna)
    {
        return tablica[x][y];
    }
    return 0;
}
// Okreslenie czy dalej zyjemy, czy nie
int MainWindow::zycie(int x, int y)
{
    int suma = 0, i, j;
    for(i = x - 1; i <= x + 1; i++)
    {
        for(j = y - 1; j <= y + 1; j++)
        {
            suma += sasiedzi(i, j);
        }
    }
    suma -= tablica[x][y];
    if(tablica[x][y] == 1 && (suma == 2 || suma == 3)){
        return 1;
    }
    if(tablica[x][y] == 0 && suma == 3)
    {
        return 1; // Ozywa bo ma 3 zywych wokolo
    }
    return 0;
}

void MainWindow::obliczKrok()
{
    int **pomoc;
    int i, j;
    pomoc = new int*[iloscWiersz];

    #pragma omp parallel for private(i, j) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        pomoc[i] = new int[iloscKolumna];
        for(j = 0; j < iloscKolumna; j++)
        {
            pomoc[i][j] = zycie(i, j);
        }
    }
    #pragma omp parallel for private(i, j) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        for(j = 0; j < iloscKolumna; j++)
        {
            tablica[i][j] = pomoc[i][j];
        }
    }

    #pragma omp parallel for schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        delete [] pomoc[i];
    }
    delete [] pomoc;
}

void MainWindow::rysuj()
{
    int i, j;
    #pragma omp parallel for private(i, j) schedule(dynamic, 1)
    for(i = 0; i < iloscWiersz; i++)
    {
        for(j = 0; j < iloscKolumna; j++)
        {
            if(tablica[i][j] == 1)
            {
                rysujPole(i * rozmiar, j * rozmiar);
            }
        }
    }
}

void MainWindow::petla()
{
    if(!wykonuj)
    {
        timer->stop();
        return;
    }
    czysc();
    obliczKrok();
    rysuj();
    update();
}

void MainWindow::on_start_clicked()
{
    timer->setInterval(szybkosc);
    connect(timer, SIGNAL(timeout()), this, SLOT(petla()));
    timer->start();
    wykonuj = true;
    petla();
}



void MainWindow::on_stop_clicked()
{
    wykonuj = false;
    timer->stop();
}

void MainWindow::on_reset_clicked()
{
    wykonuj = false;
    timer->stop();
    reset();
    czysc();
    losowanie();
}

void MainWindow::on_size_valueChanged(int arg1)
{
    wykonuj = false;
    timer->stop();
    rozmiar = arg1;
    reset();
    czysc();
    losowanie();
}

void MainWindow::losowanie()
{
    int i, j;
    czysc();

    for(i = 0; i < iloscWiersz; i++)
    {
        for(j = 0; j < iloscKolumna; j++)
        {
            tablica[i][j] = 0;
            if(2 * rand() % 100 < populacja)
            {
                tablica[i][j] = 1;
            }
        }
    }
    qDebug() << tablica[50][110];
    rysuj();
    update();
}
void MainWindow::on_ppl_valueChanged(int arg1)
{
    wykonuj = false;
    timer->stop();
    populacja = arg1;
    losowanie();
}

void MainWindow::on_speed_valueChanged(int arg1)
{
    szybkosc = arg1;
    wykonuj = false;
    timer->stop();
}
