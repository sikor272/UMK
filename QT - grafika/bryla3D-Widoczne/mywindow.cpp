
#include "mywindow.h"
#include <cmath>
#include <QDebug>
#include "ui_mywindow.h"
#include <iostream>
using namespace std;
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
    copy = new QImage(szer,wys,QImage::Format_RGB32);
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

void MyWindow::wykonaj(){
    czysc();
    Cube kostka(250,250,0,50);
    kostka.rotate(obrotOX,obrotOY,obrotOZ);
    kostka.slope(pochylenieOX,pochylenieOY,pochylenieOZ);
    kostka.scale(skalowanieOX,skalowanieOY,skalowanieOZ);
    kostka.move(przesuniecieOX,przesuniecieOY,przesuniecieOZ);
    if(kostka.checkFront()){
        int **punkt = kostka.Front();
        prosta(punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],0,0,0);
        prosta(punkt[0][0],punkt[0][1],punkt[2][0],punkt[2][1],0,0,0);
        prosta(punkt[1][0],punkt[1][1],punkt[3][0],punkt[3][1],0,0,0);
        prosta(punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1],0,0,0);
    }
    if(kostka.checkUp()){
        int **punkt = kostka.Up();
        prosta(punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],0,0,0);
        prosta(punkt[0][0],punkt[0][1],punkt[2][0],punkt[2][1],0,0,0);
        prosta(punkt[1][0],punkt[1][1],punkt[3][0],punkt[3][1],0,0,0);
        prosta(punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1],0,0,0);
    }
    if(kostka.checkDown()){
        int **punkt = kostka.Down();
        prosta(punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],0,0,0);
        prosta(punkt[0][0],punkt[0][1],punkt[2][0],punkt[2][1],0,0,0);
        prosta(punkt[1][0],punkt[1][1],punkt[3][0],punkt[3][1],0,0,0);
        prosta(punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1],0,0,0);
    }
    if(kostka.checkLeft()){
        int **punkt = kostka.Left();
        prosta(punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],0,0,0);
        prosta(punkt[0][0],punkt[0][1],punkt[2][0],punkt[2][1],0,0,0);
        prosta(punkt[1][0],punkt[1][1],punkt[3][0],punkt[3][1],0,0,0);
        prosta(punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1],0,0,0);
    }
    if(kostka.checkRight()){
        int **punkt = kostka.Right();
        prosta(punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],0,0,0);
        prosta(punkt[0][0],punkt[0][1],punkt[2][0],punkt[2][1],0,0,0);
        prosta(punkt[1][0],punkt[1][1],punkt[3][0],punkt[3][1],0,0,0);
        prosta(punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1],0,0,0);
    }
    if(kostka.checkBack()){
        int **punkt = kostka.Back();
        prosta(punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],0,0,0);
        prosta(punkt[0][0],punkt[0][1],punkt[2][0],punkt[2][1],0,0,0);
        prosta(punkt[1][0],punkt[1][1],punkt[3][0],punkt[3][1],0,0,0);
        prosta(punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1],0,0,0);
    }
    update();

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
