// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include <cmath>
// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"
#include <QDebug>
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
    oryginal = new QImage(szer,wys,QImage::Format_RGB32);
    kopia = new QImage(":/logo.jpg");
    czysc();
    *img = kopia->copy();
    *oryginal = kopia->copy();
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




// Funkcja powoduje wyczyszczenie (zamalowanie na bialo)
// obszaru rysowania
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();

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
}
void MyWindow::czysc_kopia()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = kopia->bits();

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
}



void MyWindow::on_szerokosc_valueChanged(int value)
{
    poziom = -value;
    wywolywanie();
}

void MyWindow::on_wysokosc_valueChanged(int value)
{
    pion = value;
    wywolywanie();
}

void MyWindow::on_rotacja_sliderMoved(int position)
{
    obrot = M_PI * (position)/180.0;
    wywolywanie();
}
void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    if(value >= 50){
       pochylenieOY = 1-(value/50.0);
    } else {
        pochylenieOY = ((50 - value)/50.0);
    }
    wywolywanie();
}
void MyWindow::on_verticalSlider_valueChanged(int value)
{
    if(value >= 50){
       pochylenieOX = (value/50.0) - 1;
    } else {
        pochylenieOX = - ((50 - value)/50.0);
    }
    wywolywanie();
}
void MyWindow::on_scalszer_valueChanged(int value)
{
    skalowanieOY = 50.0 / (double) value;

    wywolywanie();
}
void MyWindow::on_scalwys_valueChanged(int value)
{
    skalowanieOX = 50.0 / (double) value;

    wywolywanie();
}
void MyWindow::reset(){
    int i,j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            przesuniecie[i][j] = 0;
            MacierzSkal[i][j] = 0;
            MacierzObrot[i][j] = 0;
            MacierzPochylenie[i][j] = 0;
            wynik[i][j] = 0;
        }
    }

}


void MyWindow::Obrot(){
    MacierzObrot[0][0] = cos(obrot);
    MacierzObrot[0][1] = -sin(obrot);
    MacierzObrot[0][2] = (szer/2.0)*(1-cos(obrot))+(wys/2.0)*(sin(obrot));
    MacierzObrot[1][0] = sin(obrot);
    MacierzObrot[1][1] = cos(obrot);
    MacierzObrot[1][2] = (wys/2.0)*(1-cos(obrot))-(szer/2.0)*(sin(obrot));
    MacierzObrot[2][2] = 1;
}
void MyWindow::Scal(){
    MacierzSkal[0][0] = skalowanieOX;
    MacierzSkal[1][1] = skalowanieOY;
    MacierzSkal[2][2] = 1;
    MacierzSkal[0][2] = (szer/2.0)*(1-skalowanieOX);
    MacierzSkal[1][2] = (wys/2.0)*(1-skalowanieOY);
}
void MyWindow::Przesuniecie(){
    przesuniecie[0][0] = 1;
    przesuniecie[0][2] = pion;
    przesuniecie[1][1] = 1;
    przesuniecie[1][2] = poziom;
    przesuniecie[2][2] = 1;
}
void MyWindow::Pochylenie(){
    MacierzPochylenie[0][0] = 1 + pochylenieOX*pochylenieOY;
    MacierzPochylenie[0][1] = pochylenieOX;
    MacierzPochylenie[1][0] = pochylenieOY;
    MacierzPochylenie[1][1] = 1;
    MacierzPochylenie[2][2] = 1;
    MacierzPochylenie[0][2] = -(szer/2.0)*pochylenieOX*pochylenieOY - pochylenieOX*(wys/2.0);
    MacierzPochylenie[1][2] = -(szer/2.0)*pochylenieOY;
}
double MyWindow::Interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}
void MyWindow::wywolywanie(){
    int i,j;
    double a,b;
    int x,y,xn,yn;
    unsigned char *ptr,*org;
    czysc();
    ptr = img->bits();
    org = oryginal->bits();
    reset();
    Obrot();
    Scal();
    Przesuniecie();
    Pochylenie();
    wynik[0][0] = 1;
    wynik[1][1] = 1;
    wynik[2][2] = 1;
    Mnozenie(MacierzObrot);
    Mnozenie(MacierzSkal);
    Mnozenie(MacierzPochylenie);
    Mnozenie(przesuniecie);
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            x = a = wynik[0][0] * i + wynik[0][1] * j + wynik[0][2];
            y = b = wynik[1][0] * i + wynik[1][1] * j + wynik[1][2];
            xn = x + 1;
            yn = y + 1;
            if(xn == wys)
                xn--;
            if(yn == szer)
                yn--;
            if(x >= 0 && y >= 0 && x < wys && y < szer){
                a = a - x;
                b = b - y;
                // Domyslne interpolacja dla <> ^*
                ptr[szer*4*i + 4*j] = round(Interpolacja(Interpolacja(org[szer*4*x + 4*y],org[szer*4*xn + 4*y],a),Interpolacja(org[szer*4*x + 4*yn],org[szer*4*xn + 4*yn],a),b));
                ptr[szer*4*i + 4*j + 1] = round(Interpolacja(Interpolacja(org[szer*4*x + 4*y + 1],org[szer*4*xn + 4*y + 1],a),Interpolacja(org[szer*4*x + 4*yn + 1],org[szer*4*xn + 4*yn + 1],a),b));
                ptr[szer*4*i + 4*j + 2] = round(Interpolacja(Interpolacja(org[szer*4*x + 4*y + 2],org[szer*4*xn + 4*y + 2],a),Interpolacja(org[szer*4*x + 4*yn + 2],org[szer*4*xn + 4*yn + 2],a),b));
            }
        }
    }

    update();
}
void MyWindow::Mnozenie(double dane[3][3]){
    int i,j,k;
    double s;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            s = 0;
            for(k = 0; k < 3; k++){
                s += wynik[i][k] * dane[k][j];
            }
            pomoc[i][j] = s;
        }
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            wynik[i][j] = pomoc[i][j];
        }
    }
}




void MyWindow::on_pushButton_clicked()
{
    obrot = 0;
    pion = 0;
    poziom = 0;
    krzywapion = 0;
    krzywapoziom = 0;
    skalowanieOX = 1;
    skalowanieOY = 1;
    pochylenieOX = 0;
    pochylenieOY = 0;
    ui->szerokosc->setValue(0);
    ui->wysokosc->setValue(0);
    ui->verticalSlider->setValue(50);
    ui->horizontalSlider->setValue(50);
    ui->scalwys->setValue(50);
    ui->scalszer->setValue(50);
    ui->rotacja->setValue(0);
    *img = oryginal->copy();
}
