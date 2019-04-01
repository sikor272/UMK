// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include <cmath>
#include <QDebug>
// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"

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
    czysc();
    update();
}
void MyWindow::on_cleanButton_2_clicked()
{
   czysc2();
   update();
}
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
void MyWindow::czysc2()
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
            ptr[szer*4*i + 4*j]=0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
}
// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();

    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku

    x -= poczX;
    y -= poczY;
    *copy = img->copy();

    unsigned char *ptr;
    ptr = img->bits();



    // Sprawdzamy czy klikniecie nastapilo w granicach rysunku
    if ((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        clickX = x;
        clickY = y;
        if(tryb == 4){
            if(pX == -1 && pY == -1){
                pX = x;
                pY = y;
                lX = x;
                lY = y;
                start = false;
            }

            if(x-10 < pX && x+10>pX && y-10 < pY && y+10>pY && start){
                prosta(lX,lY,pX,pY);
                pX = pY = -1;
            } else {
                prosta(x,y,lX,lY);
                lX = x;
                lY = y;
                start = true;
            }

        }
    } else {
        clickX = -1;
        clickY = -1;
    }

    // Odswiezamy komponent
    update();
}
void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(tryb == 0){
        linia(event);
    }
    if(tryb == 1){
        okrag(event);
    }
    if(tryb == 2){
        elipsa(event);
    }
    if(tryb == 3){
        wielokat(event);
    }
}
void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(tryb == 0){
        linia_mouse(event);
    }
    if(tryb == 1){
        okrag_mouse(event);
    }
    if(tryb == 2){
        elipsa_mouse(event);
    }
    if(tryb == 3){
        wielokat_mouse(event);
    }
}
void MyWindow::on_radioButton_clicked()
{
    tryb = 0;
}
void MyWindow::on_radioButton_2_clicked()
{
    tryb = 1;
}
void MyWindow::on_radioButton_3_clicked()
{
    tryb = 2;
}
void MyWindow::on_radioButton_4_clicked()
{
    tryb = 3;
}
void MyWindow::on_radioButton_5_clicked()
{
    tryb = 4;
}
void MyWindow::on_spinBox_valueChanged(int arg1)
{
    boki = arg1;
}
void MyWindow::rysujPiksel(int x, int y){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = kolor;
        ptr[szer * 4 * y + 4 * x + 1] = kolor;
        ptr[szer * 4 * y + 4 * x + 2] = kolor;
    }
}
void MyWindow::linia(QMouseEvent *event){
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    double a, b, w;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    // Jezeli wyjechalismy poza zakres to nadajemy maksymalne wartosci osiaglane w danym miejscu
    if(endX < 0){
        endX = 0;
    }
    if(endX > szer){
        endX = szer - 1;
    }
    if(endY < 0){
        endY = 0;
    }
    if(endY > wys){
        endY = wys - 1;
    }
    if(clickX > endX){
        pom = clickX;
        clickX = endX;
        endX = pom;
        pom = clickY;
        clickY = endY;
        endY = pom;
    }
    // Jezeli jest wieksza roznica x'ow miedzy y'kami to liczymy traktujac x jako dziedzine
    if(abs(endX - clickX) > abs(endY - clickY)){
        a = (endY - clickY) / (double)(endX - clickX);
        b = clickY - a * clickX;
        for(int i = clickX;i >= 0 && i <= endX && i < szer; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = round(w);
            rysujPiksel(i,pom);
        }
    } else {
        if(clickY > endY){
            pom = clickX;
            clickX = endX;
            endX = pom;
            pom = clickY;
            clickY = endY;
            endY = pom;
        }
        if(endY - clickY != 0){
            a = (endX - clickX) / (double)(endY - clickY);
        }
        else {
            a = 0;
        }
        b = clickX - a * clickY;
        for(int i = clickY; i >= 0 && i <= endY && i < wys; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = round(w);
            rysujPiksel(pom,i);
        }
    }
    clickX = useX;
    clickY = useY;
    // Odswiezamy komponent
    update();
}
void MyWindow::linia_mouse(QMouseEvent *event){
    // Pobieramy wspolrzedne punktu klikniecia
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    double a, b, w;
    *img = copy->copy();
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku

    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    unsigned char *ptr;
    ptr = img->bits();


    endX = x;
    endY = y;
    // Jezeli jest wieksza roznica x'ow miedzy y'kami to liczymy traktujac x jako dziedzine
    if(endX < 0){
        endX = 0;
    }
    if(endX > szer){
        endX = szer - 1;
    }
    if(endY < 0){
        endY = 0;
    }
    if(endY > wys){
        endY = wys - 1;
    }
    if(clickX > endX){
        pom = clickX;
        clickX = endX;
        endX = pom;
        pom = clickY;
        clickY = endY;
        endY = pom;
    }
    if(abs(endX - clickX) > abs(endY - clickY)){
        a = (endY - clickY) / (double)(endX - clickX);
        b = clickY - a * clickX;
        for(int i = clickX;i >= 0 && i <= endX && i < szer; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = round(w);
            rysujPiksel(i,pom);
        }
    } else {
        if(clickY > endY){
            pom = clickX;
            clickX = endX;
            endX = pom;
            pom = clickY;
            clickY = endY;
            endY = pom;
        }
        a = (endX - clickX) / (double)(endY - clickY);
        b = clickX - a * clickY;
        for(int i = clickY; i >= 0 && i <= endY && i < wys; i++){
            // Ustawiamy kolor kliknietego piksela na bialy lub czarny
            w = a * i + b;
            pom = (int)round(w);
            rysujPiksel(pom,i);
        }
    }
    clickX = useX;
    clickY = useY;
    // Odswiezamy komponent
    update();
}
void MyWindow::okrag(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    int r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    r = (clickX - endX) * (clickX - endX) + (clickY - endY) * (clickY - endY);
    for(x = 0; x * x <= r / 2; x++){
        y = sqrt(r - x * x);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
        rysujPiksel(clickX + y,clickY + x);
        rysujPiksel(clickX + y,clickY + -x);
        rysujPiksel(clickX + -y,clickY + x);
        rysujPiksel(clickX + -y,clickY + -x);
    }
    update();
}
void MyWindow::okrag_mouse(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int pom;
    int r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    r = (clickX - endX) * (clickX - endX) + (clickY - endY) * (clickY - endY);
    for(x = 0; x * x <= r / 2; x++){
        y = sqrt(r - x * x);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
        rysujPiksel(clickX + y,clickY + x);
        rysujPiksel(clickX + y,clickY + -x);
        rysujPiksel(clickX + -y,clickY + x);
        rysujPiksel(clickX + -y,clickY + -x);
    }
    update();
}
void MyWindow::elipsa(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int a, b;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    for(r = 0; r < 2 * M_PI; r += 0.001){
        x = a * cos(r);
        y = b * sin(r);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
    }
    update();
}
void MyWindow::elipsa_mouse(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int a, b;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    for(r = 0; r <= 2 * M_PI; r += 0.001){
        x = a * cos(r);
        y = b * sin(r);
        rysujPiksel(clickX + x,clickY + y);
        rysujPiksel(clickX + x,clickY + -y);
        rysujPiksel(clickX + -x,clickY + y);
        rysujPiksel(clickX + -x,clickY + -y);
    }
    update();
}
void MyWindow::prosta(int startx, int starty, int koniecx, int koniecy){
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
            rysujPiksel(i,pom);
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
            rysujPiksel(pom,i);
        }
    }
}
void MyWindow::wielokat(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int a, b;
    int xx,yy;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    x = a * cos(0);
    y = b * sin(0);
    for(r = 2 * M_PI / boki; r <= 2 * M_PI + 0.1; r += 2 * M_PI / boki){
        xx = a * cos(r);
        yy = b * sin(r);
        prosta(clickX + x,clickY + y,clickX + xx,clickY + yy);
        x = xx;
        y = yy;
    }
    update();
}
void MyWindow::wielokat_mouse(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    int endX;
    int endY;
    int useX;
    int useY;
    int a, b;
    int xx,yy;
    double r;
    // Sa to wspolrzedne wzgledem glownego okna,
    // Musimy odjac od nich wpolrzedne lewego gornego naroznika rysunku
    if(clickX < 0 || clickY < 0){
        return;
    }
    useX = clickX;
    useY = clickY;
    x -= poczX;
    y -= poczY;
    *img = copy->copy();
    unsigned char *ptr;
    ptr = img->bits();
    endX = x;
    endY = y;
    a = abs(clickX - endX);
    b = abs(clickY - endY);
    x = a * cos(0);
    y = b * sin(0);
    for(r = 2 * M_PI / boki; r <= 2 * M_PI + 0.1; r += 2 * M_PI / boki){
        xx = a * cos(r);
        yy = b * sin(r);
        prosta(clickX + x,clickY + y,clickX + xx,clickY + yy);
        x = xx;
        y = yy;
    }
    update();
}
void MyWindow::on_pushButton_clicked()
{
    kolor = 120;
    unsigned char *ptr;
    ptr = img->bits();
    int i, j;
    int x,y,a,b;
    x = y = -1;
    for(i=0; i<wys; i++)
    {
        x = -1;
        for(j=0; j<szer; j++)
        {
            if(ptr[szer*4*i + 4*j] == 0 && ptr[szer*4*i + 4*j + 1] == 0 &&  ptr[szer*4*i + 4*j + 2] == 0){
                if(x == -1){
                    x = j;
                } else {
                    prosta(x,i,j,i);
                    if(x == j-1){
                        x = j;
                    }
                    else {
                        x = -1;
                    }
                }
            }
        }
        if(x != -1){
            prosta(x,i,szer,i);
        }
    }
    kolor = 0;
    update();
}
