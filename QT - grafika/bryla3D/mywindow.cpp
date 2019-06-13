
#include "mywindow.h"
#include <cmath>
#include <QDebug>
#include "ui_mywindow.h"
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{

    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    wykonaj();
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete ui;
}



// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}
void MyWindow::rysujPunkty(int x, int y, int r, int g, int b){
    int i,j;
    for(i = x - 2; i <= x + 2; i++){
        for(j = y - 2; j <= y + 2; j++){
            rysujPiksel(i,j,r,g,b);
        }
    }
}
void MyWindow::rysujPiksel(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = static_cast<unsigned char>(b);
        ptr[szer * 4 * y + 4 * x + 1] = static_cast<unsigned char>(g);
        ptr[szer * 4 * y + 4 * x + 2] = static_cast<unsigned char>(r);
    }
}
void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    przesuniecieOX = value - 250;
    wykonaj();
}

void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    przesuniecieOY = 250 - value;
    wykonaj();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    przesuniecieOZ = 250 - value;
    wykonaj();
}
void MyWindow::wykonaj(){
    czysc();
    reset();
    Scalowanie();
    Przesuniecie();
    ObrotOX();
    ObrotOY();
    ObrotOZ();
    PochylenieOX();
    PochylenieOY();
    PochylenieOZ();
    for(int i = 0; i < 4; i++){
        wynik[i][i] = 1;
    }
    Mnozenie(MacierzObrotOX);
    Mnozenie(MacierzObrotOY);
    Mnozenie(MacierzObrotOZ);
    Mnozenie(MacierzPochylenieOX);
    Mnozenie(MacierzPochylenieOY);
    Mnozenie(MacierzPochylenieOZ);
    Mnozenie(MacierzSkal);
    Mnozenie(MacierzPrzesun);
    Rysowanie();
    update();
}
void MyWindow::reset(){
    int i,j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            MacierzPrzesun[i][j] = 0;
            MacierzSkal[i][j] = 0;
            MacierzObrotOX[i][j] = 0;
            MacierzObrotOY[i][j] = 0;
            MacierzObrotOZ[i][j] = 0;
            MacierzPochylenieOX[i][j] = 0;
            MacierzPochylenieOY[i][j] = 0;
            MacierzPochylenieOZ[i][j] = 0;
            wynik[i][j] = 0;
        }
    }

}
void MyWindow::Przesuniecie(){
    MacierzPrzesun[0][0] = 1;
    MacierzPrzesun[1][1] = 1;
    MacierzPrzesun[2][2] = 1;
    MacierzPrzesun[3][3] = 1;
    MacierzPrzesun[0][3] = przesuniecieOX;
    MacierzPrzesun[1][3] = przesuniecieOY;
    MacierzPrzesun[2][3] = przesuniecieOZ;
}
void MyWindow::Scalowanie(){
    MacierzSkal[0][0] = skalowanieOX;
    MacierzSkal[1][1] = skalowanieOY;
    MacierzSkal[2][2] = skalowanieOZ;
    MacierzSkal[3][3] = 1;
}
void MyWindow::ObrotOX(){
    MacierzObrotOX[0][0] = 1;
    MacierzObrotOX[1][1] = round(cos(obrotOX)*10000)/10000;
    MacierzObrotOX[1][2] = -round(sin(obrotOX)*10000)/10000;
    MacierzObrotOX[2][1] = round(sin(obrotOX)*10000)/10000;
    MacierzObrotOX[2][2] = round(cos(obrotOX)*10000)/10000;
    MacierzObrotOX[3][3] = 1;
}
void MyWindow::ObrotOY(){
    MacierzObrotOY[0][0] = round(cos(obrotOY)*10000)/10000;
    MacierzObrotOY[0][2] = -round(sin(obrotOY)*10000)/10000;
    MacierzObrotOY[1][1] = 1;
    MacierzObrotOY[2][0] = round(sin(obrotOY)*10000)/10000;
    MacierzObrotOY[2][2] = round(cos(obrotOY)*10000)/10000;
    MacierzObrotOY[3][3] = 1;
}
void MyWindow::ObrotOZ(){
    MacierzObrotOZ[0][0] = round(cos(obrotOZ)*10000)/10000;
    MacierzObrotOZ[0][1] = -round(sin(obrotOZ)*10000)/10000;
    MacierzObrotOZ[1][0] = round(sin(obrotOZ)*10000)/10000;
    MacierzObrotOZ[1][1] = round(cos(obrotOZ)*10000)/10000;
    MacierzObrotOZ[2][2] = 1;
    MacierzObrotOZ[3][3] = 1;
}
void MyWindow::PochylenieOX(){
    MacierzPochylenieOX[0][0] = 1;
    MacierzPochylenieOX[1][0] = pochylenieOY;
    MacierzPochylenieOX[1][1] = 1;
    MacierzPochylenieOX[2][0] = pochylenieOZ;
    MacierzPochylenieOX[2][2] = 1;
    MacierzPochylenieOX[3][3] = 1;
}
void MyWindow::PochylenieOY(){
    MacierzPochylenieOY[0][0] = 1;
    MacierzPochylenieOY[0][1] = pochylenieOX;
    MacierzPochylenieOY[1][1] = 1;
    MacierzPochylenieOY[2][1] = pochylenieOZ;
    MacierzPochylenieOY[2][2] = 1;
    MacierzPochylenieOY[3][3] = 1;
}
void MyWindow::PochylenieOZ(){
    MacierzPochylenieOZ[0][0] = 1;
    MacierzPochylenieOZ[0][2] = pochylenieOX;
    MacierzPochylenieOZ[1][1] = 1;
    MacierzPochylenieOZ[1][2] = pochylenieOY;
    MacierzPochylenieOZ[2][2] = 1;
    MacierzPochylenieOZ[3][3] = 1;
}
void MyWindow::Rysowanie(){
    double xA,xB,xC,xD,xE,xF,xG,xH;
    double yA,yB,yC,yD,yE,yF,yG,yH;
    bool ba,bb,bc,bd,be,bf,bg,bh;
    ba=bb=bc=bd=be=bf=bg=bh=false;
    Wynikowe(a);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        ba = true;
    }
    xA = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yA = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(b);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        bb = true;
    }
    xB = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yB = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(c);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        bc = true;
    }
    xC = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yC = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(d);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        bd = true;
    }
    xD = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yD = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(e);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        be = true;
    }
    xE = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yE = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(f);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        bf = true;
    }
    xF = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yF = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(g);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        bg = true;
    }
    xG = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yG = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    Wynikowe(h);
    if(D + wyswietl[2] >= 0){
        wyswietl[2] = -D - 1;
        bh = true;
    }
    xH = wyswietl[0] * D / (D + wyswietl[2]) + 250;
    yH = wyswietl[1] * D / (D + wyswietl[2]) + 250;
    /*qDebug()<<static_cast<int>(xA-1)<<static_cast<int>(yA-1);
    qDebug()<<static_cast<int>(xB-1)<<static_cast<int>(yB-1);
    qDebug()<<static_cast<int>(xC-1)<<static_cast<int>(yC-1);
    qDebug()<<static_cast<int>(xD-1)<<static_cast<int>(yD-1);
    qDebug()<<static_cast<int>(xE-1)<<static_cast<int>(yE-1);
    qDebug()<<static_cast<int>(xF-1)<<static_cast<int>(yF-1);
    qDebug()<<static_cast<int>(xG-1)<<static_cast<int>(yG-1);
    qDebug()<<static_cast<int>(xH-1)<<static_cast<int>(yH-1);*/

    if(!ba || !bb)prosta(static_cast<int>(xA),static_cast<int>(yA),static_cast<int>(xB),static_cast<int>(yB),0,0,0);
    if(!ba || !bc)prosta(static_cast<int>(xA),static_cast<int>(yA),static_cast<int>(xC),static_cast<int>(yC),0,0,0);
    if(!ba || !be)prosta(static_cast<int>(xA),static_cast<int>(yA),static_cast<int>(xE),static_cast<int>(yE),0,0,0);

    if(!bf || !be)prosta(static_cast<int>(xF),static_cast<int>(yF),static_cast<int>(xE),static_cast<int>(yE),0,0,0);
    if(!bf || !bb)prosta(static_cast<int>(xF),static_cast<int>(yF),static_cast<int>(xB),static_cast<int>(yB),0,0,0);
    if(!bf || !bh)prosta(static_cast<int>(xF),static_cast<int>(yF),static_cast<int>(xH),static_cast<int>(yH),0,0,0);

    if(!bd || !bb)prosta(static_cast<int>(xD),static_cast<int>(yD),static_cast<int>(xB),static_cast<int>(yB),0,0,0);
    if(!bd || !bc)prosta(static_cast<int>(xD),static_cast<int>(yD),static_cast<int>(xC),static_cast<int>(yC),0,0,0);
    if(!bd || !bh)prosta(static_cast<int>(xD),static_cast<int>(yD),static_cast<int>(xH),static_cast<int>(yH),0,0,0);

    if(!bg || !bh)prosta(static_cast<int>(xG),static_cast<int>(yG),static_cast<int>(xH),static_cast<int>(yH),0,0,0);
    if(!bg || !bc)prosta(static_cast<int>(xG),static_cast<int>(yG),static_cast<int>(xC),static_cast<int>(yC),0,0,0);
    if(!bg || !be)prosta(static_cast<int>(xG),static_cast<int>(yG),static_cast<int>(xE),static_cast<int>(yE),0,0,0);

    rysujPunkty(static_cast<int>(xA),static_cast<int>(yA),255,215,0);
    rysujPunkty(static_cast<int>(xB),static_cast<int>(yB),255,215,0);
    rysujPunkty(static_cast<int>(xC),static_cast<int>(yC),255,215,0);
    rysujPunkty(static_cast<int>(xD),static_cast<int>(yD),255,215,0);
    rysujPunkty(static_cast<int>(xE),static_cast<int>(yE),255,215,0);
    rysujPunkty(static_cast<int>(xF),static_cast<int>(yF),255,215,0);
    rysujPunkty(static_cast<int>(xG),static_cast<int>(yG),255,215,0);
    rysujPunkty(static_cast<int>(xH),static_cast<int>(yH),255,215,0);
}
void MyWindow::Mnozenie(double dane[4][4]){
    int i,j,k;
    double s;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            s = 0;
            for(k = 0; k < 4; k++){
                s += wynik[i][k] * dane[k][j];
            }
            pomoc[i][j] = s;
        }
    }
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            wynik[i][j] = pomoc[i][j];
        }
    }
}
void MyWindow::Wynikowe(double dane[4]){
    int i,j;
    double s;
    for(i = 0; i < 4; i++){
        s = 0;
        for(j = 0; j < 4; j++){
                s += wynik[i][j] * dane[j];
        }
        wyswietl[i] = s;
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
        a = (koniecy - starty) / static_cast<double>(koniecx - startx);
        b = starty - a * startx;
        for(i = startx; i <= koniecx; i++){
            pom = static_cast<int>(a * i + b) ;
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
        a = (koniecx - startx) / static_cast<double>(koniecy - starty);
        b = startx - a * starty;
        for(i = starty; i <= koniecy; i++){
            pom = static_cast<int>(a * i + b);
            rysujPiksel(pom,i,r,g,c);
        }
    }
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    skalowanieOX = value / 250.0;
    wykonaj();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    skalowanieOY = value / 250.0;
    wykonaj();
}

void MyWindow::on_horizontalSlider_6_valueChanged(int value)
{
    skalowanieOZ = value / 250.0;
    wykonaj();
}

void MyWindow::on_dial_valueChanged(int value)
{
    obrotOX = value / 180.0 * M_PI;
    wykonaj();
}

void MyWindow::on_dial_2_valueChanged(int value)
{
    obrotOY = value / 180.0 * M_PI;
    wykonaj();
}

void MyWindow::on_dial_3_valueChanged(int value)
{
    obrotOZ = value / 180.0 * M_PI;
    wykonaj();
}

void MyWindow::on_horizontalSlider_7_valueChanged(int value)
{
    pochylenieOX = 1 - (value/250.0);
    wykonaj();
}

void MyWindow::on_horizontalSlider_8_valueChanged(int value)
{
    pochylenieOY = 1 - (value/250.0);
    wykonaj();
}

void MyWindow::on_horizontalSlider_9_valueChanged(int value)
{
    pochylenieOZ = 1 - (value/250.0);
    wykonaj();
}

void MyWindow::on_pushButton_clicked()
{
    przesuniecieOX = 0;
    przesuniecieOY = 0;
    przesuniecieOZ = 0;
    skalowanieOX = 1;
    skalowanieOY = 1;
    skalowanieOZ = 1;
    pochylenieOX = 0;
    pochylenieOY = 0;
    pochylenieOZ = 0;
    obrotOX = 0;
    obrotOY = 0;
    obrotOZ = 0;
    ui->horizontalSlider->setValue(250);
    ui->horizontalSlider_2->setValue(250);
    ui->horizontalSlider_3->setValue(250);
    ui->horizontalSlider_4->setValue(250);
    ui->horizontalSlider_5->setValue(250);
    ui->horizontalSlider_6->setValue(250);
    ui->horizontalSlider_7->setValue(250);
    ui->horizontalSlider_8->setValue(250);
    ui->horizontalSlider_9->setValue(250);
    ui->dial->setValue(0);
    ui->dial_2->setValue(0);
    ui->dial_3->setValue(0);
    wykonaj();
}
