// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

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
    czysc();
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




void MyWindow::on_verticalSlider_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255 - i/2; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = j/2; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = value; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_2_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255 - i/2; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = value; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = j/2; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_3_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = value; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255 - i/2; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = j/2; // Skladowa RED
        }
    }
    update();
}
int MyWindow::min(int a, int b){
    if(a < b)
        return a;
    return b;
}
int MyWindow::max(int a, int b){
    if(a > b)
        return a;
    return b;
}
void MyWindow::hsv(int h, double s, double v, int *R, int *G, int *B){
    /*int k1,k2,k3;
    k1 = (5 + h / 60) % 6;
    k2 = (3 + h / 60) % 6;
    k3 = (1 + h / 60) % 6;
    *R = 255*(v - v * s * max(0,min(1,min(k1,4 - k1))));
    *G = 255*(v - v * s * max(0,min(1,min(k2,4 - k2))));
    *B = 255*(v - v * s * max(0,min(1,min(k3,4 - k3))));*/


    double C, X, m;
    double r, g, b;
    C = v * s;
    X = C*(1 - abs(((h/60) % 2) - 1));
    m = v - C;
    if(h>=0 && h<60){r = C; g = X; b = 0;}
    if(h>=60 && h<120){r = X; g = C; b = 0;}
    if(h>=120 && h<180){r = 0; g = C; b = X;}
    if(h>=180 && h<240){r = 0; g = X; b = C;}
    if(h>=240 && h<300){r = X; g = 0; b = C;}
    if(h>=300 && h<360){r = C; g = 0; b = X;}

    *R = (r + m) * 255;
    *G = (g + m) * 255;
    *B = (b + m) * 255;


}
void MyWindow::on_verticalSlider_4_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    int r,g,b;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            hsv(value, 1.0*(szer - j)/szer,1.0*(wys - i)/wys,&r,&g,&b);
            ptr[szer*4*i + 4*j] = b; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = g; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = r; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_5_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    int r,g,b;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            hsv(360.0 * j/szer, value / 100.0,1.0*(wys - i)/wys,&r,&g,&b);
            ptr[szer*4*i + 4*j] = b; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = g; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = r; // Skladowa RED
        }
    }
    update();
}

void MyWindow::on_verticalSlider_6_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    int r,g,b;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            hsv(360.0 * j/szer, 1.0*i/wys, value / 100.0,&r,&g,&b);
            ptr[szer*4*i + 4*j] = b; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = g; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = r; // Skladowa RED
        }
    }
    update();
}
