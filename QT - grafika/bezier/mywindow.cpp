// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <QDebug>
using namespace std;
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej, nastepnie tworzymy
// obiekt klasy Ui_MyWindow reprezentujacy GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    // Wywolujemy funkcje tworzaca elementy GUI
    // Jej definicja znajduje sie w pliku "ui_mywindow.h"
    ui->setupUi(this);

    // Pobieramy wymiary i wspolrzedne lewego gornego naroznika ramki
    // i ustawiamy wartosci odpowiednich pol
    // Uwaga: ramke "rysujFrame" wykorzystujemy tylko do
    // wygodnego ustaiwenia tych wymiarow. Rysunek bedziemy wyswietlac
    // bezposrednio w glownym oknie aplikacji.
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    copy = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    *copy = img->copy();

}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete ui;
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Wyjscie" (exitButton)
// Uwaga: polaczenie tej funkcji z sygnalem "clicked"
// emitowanym przez przycisk jest realizowane
// za pomoca funkcji QMetaObject::connectSlotsByName(MyWindow)
// znajdujacej sie w automatycznie generowanym pliku "ui_mywindow.h"
// Nie musimy wiec sami wywolywac funkcji "connect"
void MyWindow::on_exitButton_clicked()
{
    // qApp to globalny wskaznik do obiektu reprezentujacego aplikacje
    // quit() to funkcja (slot) powodujaca zakonczenie aplikacji z kodem 0 (brak bledu)
    qApp->quit();
}
// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}
// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::on_cleanButton_clicked()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();
    licznik = -1;
    linii = 0;
    kontorla = false;
    punkty.clear();
    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
    *copy = img->copy();
}
// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    *img = copy->copy();
    x -= poczX;
    y -= poczY;

    // Sprawdzamy ktory przycisk myszy zostal klkniety
    if(event->button() == Qt::LeftButton)
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
        {

        }
    }
    else
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
        {
            sprawdz(x,y);
        }

    }
    krzywe();
    punkt();
    update();
}
void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku

    *img = copy->copy();
    x -= poczX;
    y -= poczY;

    // Sprawdzamy ktory przycisk myszy zostal klkniety
    if(event->button() == Qt::LeftButton)
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            if(usun){
                sprawdz(x,y);
                if(kontorla){
                    punkty.erase(przesun);
                    if(licznik % 3 == 0 && licznik != 0){
                        linii--;
                    }
                    licznik--;
                    kontorla = false;
                }
            } else if(!usun){
                punkty.push_back(std::make_pair(x,y));
                licznik++;
                if(licznik % 3 == 0 && licznik != 0){
                    linii++;
                }
            }
        }
    }
    else
    {
        if(kontorla == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x,y);
            *przesun = przesuniety;
            kontorla = false;
        }
    }
    krzywe();
    punkt();
    update();
}
void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku

    *img = copy->copy();
    x -= poczX;
    y -= poczY;

    // Sprawdzamy ktory przycisk myszy zostal klkniety
    if(event->button() == Qt::LeftButton)
    {

    }
    else
    {
        if(kontorla == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x,y);
            *przesun = przesuniety;
        }
    }
    krzywe();
    punkt();
    update();
}
void MyWindow::rysujPunkty(int x, int y){
    int i,j;
    for(i = x - 5; i <= x + 5; i++){
        for(j = y - 5; j <= y + 5; j++){
            rysujPiksel(i,j,255,0,0);
        }
    }
}
void MyWindow::rysujPiksel(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = b;
        ptr[szer * 4 * y + 4 * x + 1] = g;
        ptr[szer * 4 * y + 4 * x + 2] = r;
    }
}
void MyWindow::prosta(int startx, int starty, int koniecx, int koniecy,int r, int g, int c){
    double a, b;
    int pom;
    int i;
    if(abs(startx - koniecx) > abs(starty - koniecy)){
        if(startx > koniecx){
            pom = startx;
            startx = koniecx;
            koniecx = pom;
            pom = starty;
            starty = koniecy;
            koniecy = pom;
        }
        a = (koniecy - starty) / (double) (koniecx - startx);
        b = starty - a * startx;
        for(i = startx; i <= koniecx; i++){
            pom = a * i + b;
            rysujPiksel(i,pom,r,g,c);
        }
    } else {
        if(starty > koniecy){
            pom = startx;
            startx = koniecx;
            koniecx = pom;
            pom = starty;
            starty = koniecy;
            koniecy = pom;
        }
        a = (koniecx - startx) / (double) (koniecy - starty);
        b = startx - a * starty;
        for(i = starty; i <= koniecy; i++){
            pom = a * i + b;
            rysujPiksel(pom,i,r,g,c);
        }
    }
}
void MyWindow::sprawdz(int x, int y){
    for(vector<pair<int, int> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        if(it->first + 5 >= x && it->first - 5 <= x && it->second + 5 >= y && it->second - 5 <= y){
            przesun = it;
            kontorla = true;
            return;
        }
    }
}
void MyWindow::punkt(){
    if(punkty.empty())
        return;
    for(vector<pair<int, int> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        rysujPunkty(it->first,it->second);
    }
}
void MyWindow::krzywe(){
    pair<int,int> p1,p2,p3,p4;
    int x, y, a, b;
    int i = 0;
    double t;
    if(punkty.empty())
        return;
    vector<pair<int, int> >::iterator it = punkty.begin();
    p1 = *it;
    for(vector<pair<int, int> >::iterator it = punkty.begin() + 1; i < linii; i++, it += 3){
        p4 = *(it);
        p2 = *(it + 1);
        p3 = *(it + 2);
        for(t = 0; t <= 1; t += 0.001){
            x = (double)(p1.first * (1 - t) * (1 - t) * (1 - t) + 3 * (1 - t) * (1 - t) * t * p2.first + 3 * (1 - t) * t * t * p3.first + t * t * t * p4.first);
            y = (double)(p1.second * (1 - t) * (1 - t) * (1 - t) + 3 * (1 - t) * (1 - t) * t * p2.second + 3 * (1 - t) * t * t * p3.second + t * t * t *p4.second);
            if(t > 0){
                prosta(a, b, x, y, 0, 0, 0);
            }
            a = x;
            b = y;
        }
        p1 = p4;
    }
}




void MyWindow::on_pushButton_clicked()
{
    *img = copy->copy();
    krzywe();
    punkty.clear();
    linii = 0;
    licznik = -1;
    kontorla = false;
    *copy = img->copy();
    update();
}

void MyWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        usun = true;
    } else {
        usun = false;
    }
}
