// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include <QFileDialog>
// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <QDebug>
#include <cmath>
#include <QTimer>
using namespace std;
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej, nastepnie tworzymy
// obiekt klasy Ui_MyWindow reprezentujacy GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();
    poczX2 = ui->rysujFrame_2->x();
    poczY2 = ui->rysujFrame_2->y();
    poczX3 = ui->rysujFrame_3->x();
    poczY3 = ui->rysujFrame_3->y();
    img = new QImage(szer,wys,QImage::Format_RGB32);
    img2 = new QImage(szer,wys,QImage::Format_RGB32);
    img3 = new QImage(szer,wys,QImage::Format_RGB32);
    wynik = new QImage*[2];
    wynik[0] = new QImage(szer,wys,QImage::Format_RGB32);
    wynik[1] = new QImage(szer,wys,QImage::Format_RGB32);
    copy = new QImage(szer,wys,QImage::Format_RGB32);
    copy2 = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    on_spinBox_2_valueChanged(1);
}
void MyWindow::czysc()
{
    unsigned char *ptr;
    unsigned char *ptr2;
    ptr = img->bits();
    ptr2 = img2->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
            ptr2[szer*4*i + 4*j] = 0; // Skladowa BLUE
            ptr2[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr2[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
}
MyWindow::~MyWindow()
{
    delete ui;
}
void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
    p.drawImage(poczX2,poczY2,*img2);
    p.drawImage(poczX3,poczY3,*img3);
}
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int x2,y2;
    *img = copy->copy();
    *img2 = copy2->copy();
    x2 = x - poczX2;
    y2 = y - poczY2;
    x -= poczX;
    y -= poczY;


    if(event->button() == Qt::LeftButton)
    {

    }
    else
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
        {
            sprawdz(x,y);
        }
        if((x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys))
        {
            sprawdz2(x2,y2);
        }

    }
    krzywe();
    punkt();
    krzywe2();
    punkt2();
    update();
}
void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int x2,y2;
    *img = copy->copy();
    *img2 = copy2->copy();
    x2 = x - poczX2;
    y2 = y - poczY2;
    x -= poczX;
    y -= poczY;
    if(event->button() == Qt::LeftButton)
    {
    }
    else
    {
        if(kontorla == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            punkty[moveX][moveY].first = x;
            punkty[moveX][moveY].second = y;
            kontorla = false;
        }
        if(kontorla2 == true && (x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys)){
            punkty2[moveX][moveY].first = x2;
            punkty2[moveX][moveY].second = y2;
            kontorla2 = false;
        }
    }
    krzywe();
    punkt();
    krzywe2();
    punkt2();
    update();
}
void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int x2,y2;
    *img = copy->copy();
    *img2 = copy2->copy();
    x2 = x - poczX2;
    y2 = y - poczY2;
    x -= poczX;
    y -= poczY;

    if(event->button() == Qt::LeftButton)
    {

    }
    else
    {
        if(kontorla == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            punkty[moveX][moveY].first = x;
            punkty[moveX][moveY].second = y;
        }
        if(kontorla2 == true && (x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys)){
            punkty2[moveX][moveY].first = x2;
            punkty2[moveX][moveY].second = y2;
        }
    }
    krzywe();
    punkt();
    krzywe2();
    punkt2();
    update();
}
void MyWindow::rysujPunkty(int x, int y, int r, int g, int b){
    int i,j;
    for(i = x - 5; i <= x + 5; i++){
        for(j = y - 5; j <= y + 5; j++){
            rysujPiksel(i,j,r,g,b);
        }
    }
}
void MyWindow::rysujPunkty2(int x, int y, int r, int g, int b){
    int i,j;
    for(i = x - 5; i <= x + 5; i++){
        for(j = y - 5; j <= y + 5; j++){
            rysujPiksel2(i,j,r,g,b);
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
void MyWindow::rysujPiksel2(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img2->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = static_cast<unsigned char>(b);
        ptr[szer * 4 * y + 4 * x + 1] = static_cast<unsigned char>(g);
        ptr[szer * 4 * y + 4 * x + 2] = static_cast<unsigned char>(r);
    }
}
void MyWindow::rysujPiksel3(int x, int y, int r, int g, int b,int i){
    unsigned char *ptr;
    ptr = wynik[i]->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = static_cast<unsigned char>(b);
        ptr[szer * 4 * y + 4 * x + 1] = static_cast<unsigned char>(g);
        ptr[szer * 4 * y + 4 * x + 2] = static_cast<unsigned char>(r);
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
void MyWindow::prosta2(int startx, int starty, int koniecx, int koniecy,int r, int g, int c){
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
            rysujPiksel2(i,pom,r,g,c);
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
            rysujPiksel2(pom,i,r,g,c);
        }
    }
}
void MyWindow::sprawdz(int x, int y){
    unsigned long long i,j;
    for(i = 1; i < licznik-1; i++){
        for(j = 1; j < licznik-1; j++){
            if(punkty[i][j].first + 5 >= x && punkty[i][j].first -5 <= x && punkty[i][j].second + 5 >= y && punkty[i][j].second -5 <= y){
                moveX = i;
                moveY = j;
                kontorla = true;
                return;
            }
        }
    }
}
void MyWindow::sprawdz2(int x, int y){
    unsigned long long i,j;
    for(i = 1; i < licznik-1; i++){
        for(j = 1; j < licznik-1; j++){
            if(punkty2[i][j].first + 5 >= x && punkty2[i][j].first -5 <= x && punkty2[i][j].second + 5 >= y && punkty2[i][j].second -5 <= y){
                moveX = i;
                moveY = j;
                kontorla2 = true;
                return;
            }
        }
    }
}
void MyWindow::punkt(){
    unsigned long long i,j;
    for(i = 1; i < licznik-1; i++){
        for(j = 1; j < licznik-1; j++){
            if(i == moveX && j == moveY && (kontorla || kontorla2)){
                rysujPunkty(punkty[i][j].first,punkty[i][j].second,0,0,255);
            } else {
                rysujPunkty(punkty[i][j].first,punkty[i][j].second,255,0,0);
            }
        }
    }
}
void MyWindow::punkt2(){
    unsigned long long i,j;
    for(i = 1; i < licznik-1; i++){
        for(j = 1; j < licznik-1; j++){
            if(i == moveX && j == moveY && (kontorla || kontorla2)){
                rysujPunkty2(punkty2[i][j].first,punkty2[i][j].second,0,0,255);
            } else {
                rysujPunkty2(punkty2[i][j].first,punkty2[i][j].second,255,0,0);
            }
        }
    }
}
void MyWindow::krzywe(){
    unsigned long long i,j;
    for(i = 0; i < licznik-1; i++){
        for(j = 0; j < licznik-1; j++){
            prosta(punkty[i][j].first,punkty[i][j].second,punkty[i+1][j].first,punkty[i+1][j].second,0,255,0);
            prosta(punkty[i][j].first,punkty[i][j].second,punkty[i][j+1].first,punkty[i][j+1].second,0,255,0);
            prosta(punkty[i][j].first,punkty[i][j].second,punkty[i+1][j+1].first,punkty[i+1][j+1].second,0,255,0);
        }
        prosta(punkty[i][j].first,punkty[i][j].second,punkty[i+1][j].first,punkty[i+1][j].second,0,255,0);
    }

}
void MyWindow::krzywe2(){
    unsigned long long i,j;
    for(i = 0; i < licznik-1; i++){
        for(j = 0; j < licznik-1; j++){
            prosta2(punkty2[i][j].first,punkty2[i][j].second,punkty2[i+1][j].first,punkty2[i+1][j].second,0,255,0);
            prosta2(punkty2[i][j].first,punkty2[i][j].second,punkty2[i][j+1].first,punkty2[i][j+1].second,0,255,0);
            prosta2(punkty2[i][j].first,punkty2[i][j].second,punkty2[i+1][j+1].first,punkty2[i+1][j+1].second,0,255,0);
        }
        prosta2(punkty2[i][j].first,punkty2[i][j].second,punkty2[i+1][j].first,punkty2[i+1][j].second,0,255,0);
    }
}
double MyWindow::Interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}
void MyWindow::Teksturowanie(int s, pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> At, pair<int,int> Bt, pair<int,int> Ct){

    int Xmin,Xmax,Ymin,Ymax;
    double xa,xb,ya,yb,v,w,u,delta;
    int i,j,x,y,xn,yn;
    int r,g,blue;
    unsigned char *org;
    unsigned char *skad;
    unsigned char *dokad;
    skad = copy->bits();
    dokad = copy2->bits();
    pair<int, int> An((1-s/(double)podzial)*A.first+s/(double)podzial*At.first,(1-s/(double)podzial)*A.second+s/(double)podzial*At.second);
    pair<int, int> Bn((1-s/(double)podzial)*B.first+s/(double)podzial*Bt.first,(1-s/(double)podzial)*B.second+s/(double)podzial*Bt.second);
    pair<int, int> Cn((1-s/(double)podzial)*C.first+s/(double)podzial*Ct.first,(1-s/(double)podzial)*C.second+s/(double)podzial*Ct.second);

    Xmin = Xmax = An.first;
    Ymin = Ymax = An.second;
    if(Bn.first < Xmin){
        Xmin = Bn.first;
    }
    if(Cn.first < Xmin){
        Xmin = Cn.first;
    }
    if(Bn.first > Xmax){
        Xmax = Bn.first;
    }
    if(Cn.first > Xmax){
        Xmax = Cn.first;
    }
    if(Bn.second < Ymin){
        Ymin = Bn.second;
    }
    if(Cn.second < Ymin){
        Ymin = Cn.second;
    }
    if(Bn.second > Ymax){
        Ymax = Bn.second;
    }
    if(Cn.second > Ymax){
        Ymax = Cn.second;
    }
    delta = (((Bn.first - An.first) * (Cn.second - An.second)) - ((Cn.first - An.first) * (Bn.second - An.second)));
    for(i=Ymin; i<Ymax; i++)
    {
        for(j=Xmin; j<Xmax; j++)
        {
            v = (((j - An.first) * (Cn.second - An.second)) - ((Cn.first - An.first) * (i - An.second))) / delta;
            w = (((Bn.first - An.first) * (i - An.second)) - ((j - An.first) * (Bn.second - An.second))) / delta;
            u = 1 - v - w;
            if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && w >= 0 && w <= 1){
               x = static_cast<int>(u * A.first + v * B.first + w * C.first);
               y = static_cast<int>(u * A.second + v * B.second + w * C.second);
               xn = static_cast<int>(u * At.first + v * Bt.first + w * Ct.first);
               yn = static_cast<int>(u * At.second + v * Bt.second + w * Ct.second);
               /*x = static_cast<int>(a);
               y = static_cast<int>(b);
               xn = x + 1;
               yn = y + 1;
               a -=x;
               b -=y;
               if(yn == wys)
                   yn--;
               if(xn == szer)
                   xn--;
               r = static_cast<int>(round(Interpolacja(static_cast<int>(Interpolacja(org[szer*4*y + 4*x + 2],org[szer*4*yn + 4*x + 2],b)),static_cast<int>(Interpolacja(org[szer*4*y + 4*xn + 2],org[szer*4*yn + 4*xn + 2],b)),a)));
               g = static_cast<int>(round(Interpolacja(static_cast<int>(Interpolacja(org[szer*4*y + 4*x + 1],org[szer*4*yn + 4*x + 1],b)),static_cast<int>(Interpolacja(org[szer*4*y + 4*xn + 1],org[szer*4*yn + 4*xn + 1],b)),a)));
               blue = static_cast<int>(round(Interpolacja(static_cast<int>(Interpolacja(org[szer*4*y + 4*x],org[szer*4*yn + 4*x],b)),static_cast<int>(Interpolacja(org[szer*4*y + 4*xn],org[szer*4*yn + 4*xn],b)),a)));
               */
               blue = (1-s/(double)podzial)*skad[wys*4*y + 4*x]+s/(double)podzial*dokad[wys*4*yn + 4*xn];
               g = (1-s/(double)podzial)*skad[wys*4*y + 4*x+1]+s/(double)podzial*dokad[wys*4*yn + 4*xn+1];
               r = (1-s/(double)podzial)*skad[wys*4*y + 4*x+2]+s/(double)podzial*dokad[wys*4*yn + 4*xn+2];
               rysujPiksel3(j,i,r,g,blue,s);
            }

        }
    }
}

void MyWindow::on_pushButton_clicked()
{
    QString plik = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png *.jpeg *.bmp *.gif)"));
    if(QString::compare(plik,QString()) != 0){
        delete img;
        delete copy;
        img = new QImage(plik);
        copy = new QImage(plik);
        on_spinBox_2_valueChanged(licznik-1);
    }
    update();
}

void MyWindow::on_pushButton_2_clicked()
{
    QString plik = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png *.jpeg *.bmp *.gif)"));
    if(QString::compare(plik,QString()) != 0){
        delete img2;
        delete copy2;
        img2 = new QImage(plik);
        copy2 = new QImage(plik);
        on_spinBox_2_valueChanged(licznik-1);
    }
}

void MyWindow::on_pushButton_4_clicked()
{
    ui->progressBar->setValue(0);
    QTimer  *t= new QTimer(this);
    t->setInterval(100);
    int i = 0;
    connect(t, &QTimer::timeout, [=]() mutable{
        *img3 = wynik[i]->copy();
        i++;
        ui->progressBar->setValue(100*i/(double)podzial);
        if(i >= podzial){
            t->stop();
        }
        update();

    });

    t->start();
}

void MyWindow::on_spinBox_2_valueChanged(int arg1)
{
    licznik = arg1 + 1;
    punkty = new pair<int,int>*[licznik];
    punkty2 = new pair<int,int>*[licznik];
    unsigned long long i,j;
    for(i = 0; i < licznik; i++){
        punkty[i] = new pair<int,int>[licznik];
        punkty2[i] = new pair<int,int>[licznik];
        for(j = 0; j < licznik; j++){
            punkty[i][j].first = wys * (i/(double)arg1);
            punkty[i][j].second = szer * (j/(double)arg1);
            punkty2[i][j].first = wys * (i/(double)arg1);
            punkty2[i][j].second = szer * (j/(double)arg1);
        }
    }
    *img = copy->copy();
    *img2 = copy2->copy();
    krzywe();
    krzywe2();
    punkt();
    punkt2();
    update();
}

void MyWindow::on_spinBox_valueChanged(int arg1)
{
    int i;
    for(i = 0; i < podzial ; i++){
        delete wynik[i];
    }
    podzial = arg1;
    delete wynik;
    wynik = new QImage*[podzial];
    for(i = 0; i < podzial ; i++){
        wynik[i] = new QImage(szer,wys,QImage::Format_RGB32);
    }

}

void MyWindow::on_pushButton_3_clicked()
{
    *wynik[0] = copy->copy();
    *wynik[podzial-1] = copy2->copy();
    unsigned long long i,j,k;
    for(k = 1; k < podzial - 1; k++){
        ui->progress->setValue(100 * (k+1)/(double)podzial);
        for(i = 0; i < licznik - 1; i++){
            for(j = 0; j < licznik - 1; j++){

                Teksturowanie(k,punkty[i][j],punkty[i][j+1],punkty[i+1][j+1],punkty2[i][j],punkty2[i][j+1],punkty2[i+1][j+1]);
                Teksturowanie(k,punkty[i][j],punkty[i+1][j],punkty[i+1][j+1],punkty2[i][j],punkty2[i+1][j],punkty2[i+1][j+1]);
            }
        }
    }
    *img3 = wynik[0]->copy();
    ui->progress->setValue(100);
    update();
}
