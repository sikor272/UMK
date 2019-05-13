// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"
#include<QDebug>
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
    pictures[0] = new QImage(":/picture_one.jpg");
    pictures[1] = new QImage(":/picture_two.jpg");
    pictures[2] = new QImage(":/picture_three.jpg");
    pictures[3] = new QImage(":/picture_four.jpg");
    pictures[4] = new QImage(":/picture_five.jpg");
    pictures[5] = new QImage(":/picture_six.jpg");
    pictures[6] = new QImage(":/picture_seven.jpg");
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
            ptr[szer*4*i + 4*j] = 255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
    update();
}


void MyWindow::blending()
{
    unsigned char *oryginal;
    unsigned char *dodatek;
    int i,j,n;
    int r,g,b,r2,g2,b2;
    double alfa,beta;
    czysc();
    for(n=0;n<7;n++){
        if(widoczne[n]){
            alfa = moc[n] / 100.0;
            beta = 1.0 - alfa;
            for(i=0;i<wys;i++){
                oryginal = img->scanLine(i);
                dodatek = pictures[n]->scanLine(i);
                for(j=0;j<szer;j++){
                   r = oryginal[4*j + 2];
                   g = oryginal[4*j + 1];
                   b = oryginal[4*j];
                   r2 = dodatek[4*j + 2];
                   g2 = dodatek[4*j + 1];
                   b2 = dodatek[4*j];
                   if(tryb[n] == 1){
                       r2 = Average(r,r2);
                       g2 = Average(g,g2);
                       b2 = Average(b,b2);
                   }
                   if(tryb[n] == 2){
                       r2 = Multiply(r,r2);
                       g2 = Multiply(g,g2);
                       b2 = Multiply(b,b2);
                   }
                   if(tryb[n] == 3){
                       r2 = Darken(r,r2);
                       g2 = Darken(g,g2);
                       b2 = Darken(b,b2);
                   }
                   if(tryb[n] == 4){
                       r2 = Lighten(r,r2);
                       g2 = Lighten(g,g2);
                       b2 = Lighten(b,b2);
                   }
                   if(tryb[n] == 5){
                       r2 = Difference(r,r2);
                       g2 = Difference(g,g2);
                       b2 = Difference(b,b2);
                   }
                   if(tryb[n] == 6){
                       r2 = Sum(r,r2);
                       g2 = Sum(g,g2);
                       b2 = Sum(b,b2);
                   }
                   if(tryb[n] == 7){
                       r2 = Xor(r,r2);
                       g2 = Xor(g,g2);
                       b2 = Xor(b,b2);
                   }
                   if(tryb[n] == 8){
                       r2 = And(r,r2);
                       g2 = And(g,g2);
                       b2 = And(b,b2);
                   }
                   if(tryb[n] == 9){
                       r2 = Or(r,r2);
                       g2 = Or(g,g2);
                       b2 = Or(b,b2);
                   }
                   oryginal[4*j+2] = alfa * r2 + beta * oryginal[4*j+2];
                   oryginal[4*j+1] = alfa * g2 + beta * oryginal[4*j+1];
                   oryginal[4*j] = alfa * b2 + beta * oryginal[4*j];
                }
            }
        }
    }
    update();
}



int MyWindow::Average(int a, int b){
    return ((a+b)/2);
}
int MyWindow::Multiply(int a, int b){
    return ((a*b)%256);
}
int MyWindow::Darken(int a, int b){
    return (a < b ? a : b);
}
int MyWindow::Lighten(int a, int b){
    return (a < b ? b : a);
}
int MyWindow::Difference(int a, int b){
    return (abs(a-b));
}
int MyWindow::Sum(int a, int b){
    return (a+b)%256;
}
int MyWindow::Xor(int a, int b){
    return (a^b);
}
int MyWindow::And(int a, int b){
    return (a&b);
}
int MyWindow::Or(int a, int b){
    return (a|b);
}


void MyWindow::on_checkBox_stateChanged(int arg1)
{
    widoczne[6]=arg1;
    blending();
}

void MyWindow::on_checkBox_2_stateChanged(int arg1)
{
    widoczne[5]=arg1;
    blending();
}

void MyWindow::on_checkBox_3_stateChanged(int arg1)
{
    widoczne[4]=arg1;
    blending();
}

void MyWindow::on_checkBox_4_stateChanged(int arg1)
{
    widoczne[3]=arg1;
    blending();
}

void MyWindow::on_checkBox_5_stateChanged(int arg1)
{
    widoczne[2]=arg1;
    blending();
}
void MyWindow::on_checkBox_6_stateChanged(int arg1)
{
    widoczne[1]=arg1;
    blending();
}

void MyWindow::on_checkBox_7_stateChanged(int arg1)
{
    widoczne[0]=arg1;
    blending();
}

void MyWindow::on_comboBox_currentIndexChanged(int index)
{
    tryb[6]=index;
    blending();
}

void MyWindow::on_comboBox_2_currentIndexChanged(int index)
{
    tryb[5]=index;
    blending();
}

void MyWindow::on_comboBox_3_currentIndexChanged(int index)
{
    tryb[4]=index;
    blending();
}

void MyWindow::on_comboBox_4_currentIndexChanged(int index)
{
    tryb[3]=index;
    blending();
}

void MyWindow::on_comboBox_5_currentIndexChanged(int index)
{
    tryb[2]=index;
    blending();
}
void MyWindow::on_comboBox_6_currentIndexChanged(int index)
{
    tryb[1]=index;
    blending();
}

void MyWindow::on_comboBox_7_currentIndexChanged(int index)
{
    tryb[0]=index;
    blending();
}


void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    moc[6]=value;
    blending();
}

void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    moc[5]=value;
    blending();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    moc[4]=value;
    blending();
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    moc[3]=value;
    blending();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    moc[2]=value;
    blending();
}

void MyWindow::on_horizontalSlider_6_valueChanged(int value)
{
    moc[1]=value;
    blending();
}

void MyWindow::on_horizontalSlider_7_valueChanged(int value)
{
    moc[0]=value;
    blending();
}
