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
    kopia = new QImage(szer,wys,QImage::Format_RGB32);
    oryginal = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    *kopia = *oryginal = img->copy();
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
void MyWindow::toBlack(){
    unsigned char *ptr;
    int i,j;
    int r,g,b;
    ptr = img->bits();
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            b = ptr[szer*4*i + 4*j];
            g = ptr[szer*4*i + 4*j + 1];
            r = ptr[szer*4*i + 4*j + 2];
            r = 0.299 * r + 0.587 * g + 0.114 * b;
            if(r < 128){
                r = 0;
            }
            else {
                r = 255;
            }
            ptr[szer*4*i + 4*j] = r;
            ptr[szer*4*i + 4*j + 1] = r;
            ptr[szer*4*i + 4*j + 2] = r;
        }
    }
    update();
}

void MyWindow::on_pushButton_clicked()
{
    QString plik = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png *.jpeg *.bmp *.gif)"));
    if(QString::compare(plik,QString()) != 0){
        delete img;
        delete oryginal;
        delete kopia;
        img = new QImage(plik);
        oryginal = new QImage(plik);
        kopia = new QImage(plik);
        toBlack();
        *oryginal = img->copy();
        *kopia = img->copy();
    }
}

void MyWindow::on_pushButton_2_clicked()
{

    *img = oryginal->copy();
    update();

}

void MyWindow::on_comboBox_currentIndexChanged(int index)
{
    rozmiar = 1 +  index;
}
bool MyWindow::check_black(int x, int y){
    unsigned char *ptr;
    if(x < 0 || x >= wys || y < 0 || y >= szer)
        return false;
    ptr = img->bits();
    if(ptr[szer*4*x + 4*y] == 0 &&
            ptr[szer*4*x + 4*y + 1] == 0 &&
                ptr[szer*4*x + 4*y + 2] == 0)
        return true;
   return false;
}
bool MyWindow::check_white(int x, int y){
    unsigned char *ptr;
    if(x < 0 || x >= wys || y < 0 || y >= szer)
        return true;
    ptr = img->bits();
    if(ptr[szer*4*x + 4*y] == 0 &&
            ptr[szer*4*x + 4*y + 1] == 0 &&
                ptr[szer*4*x + 4*y + 2] == 0)
        return false;
   return true;
}
void MyWindow::on_pushButton_3_clicked()
{
    // Dyladacja
    *kopia = img->copy();
    unsigned char *ptr;
    unsigned char *org;
    int i,j,k,n;
    bool wykonaj;
    ptr = kopia->bits();
    org = img->bits();
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            if(org[szer*4*i + 4*j] == 255 &&
                    org[szer*4*i + 4*j + 1] == 255 &&
                        org[szer*4*i + 4*j + 2] == 255)
            {
                for(n =  - rozmiar, wykonaj = false; !wykonaj && n <= rozmiar; n++){
                    for(k = - rozmiar; k <= rozmiar; k++){
                        if(check_black(i+n,j+k)){
                            ptr[szer*4*i + 4*j] = 0;
                            ptr[szer*4*i + 4*j + 1] = 0;
                            ptr[szer*4*i + 4*j + 2] = 0;
                            wykonaj = true;
                            break;
                        }
                    }
                }
            }

        }
    }
    *img = kopia->copy();
    update();
}

void MyWindow::on_pushButton_4_clicked()
{
    // Erozja
    *kopia = img->copy();
    unsigned char *ptr;
    unsigned char *org;
    int i,j,k,n;
    bool wykonaj;
    ptr = kopia->bits();
    org = img->bits();
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            if(org[szer*4*i + 4*j] == 0 &&
                    org[szer*4*i + 4*j + 1] == 0 &&
                        org[szer*4*i + 4*j + 2] == 0)
            {
                for(n =  - rozmiar, wykonaj = false; !wykonaj && n <= rozmiar; n++){
                    for(k = - rozmiar; k <= rozmiar; k++){
                        if(check_white(i+n,j+k)){
                            ptr[szer*4*i + 4*j] = 255;
                            ptr[szer*4*i + 4*j + 1] = 255;
                            ptr[szer*4*i + 4*j + 2] = 255;
                            wykonaj = true;
                            break;
                        }
                    }
                }
            }

        }
    }
    *img = kopia->copy();
    update();
}

void MyWindow::on_pushButton_5_clicked()
{
    on_pushButton_4_clicked();
    on_pushButton_3_clicked();
}

void MyWindow::on_pushButton_6_clicked()
{
    on_pushButton_3_clicked();
    on_pushButton_4_clicked();
}
