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
#include <cmath>
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
    img = new QImage(":/dubaj.jpg");
    img2 = new QImage(szer,wys,QImage::Format_RGB32);
    copy = new QImage(":/dubaj.jpg");
    copy2 = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    *copy2 = img2->copy();
}
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img2->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
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
    if(licznik == 3 && licznik2 == 3){
        Teksturowanie();
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
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            if(licznik < 3){
                punkty.push_back(std::make_pair(x,y));
                licznik++;
            }
        }
        if((x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys)){
            if(licznik2 < 3){
                punkty2.push_back(std::make_pair(x2,y2));
                licznik2++;
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
        if(kontorla2 == true && (x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys)){
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x2,y2);
            *przesun2 = przesuniety;
            kontorla2 = false;
        }
    }
    if(licznik == 3 && licznik2 == 3){
        Teksturowanie();
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
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x,y);
            *przesun = przesuniety;
        }
        if(kontorla2 == true && (x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys)){
            pair<int, int> przesuniety;
            przesuniety = std::make_pair(x2,y2);
            *przesun2 = przesuniety;
        }
    }
    if(licznik == 3 && licznik2 == 3){
        Teksturowanie();
    }
    krzywe();
    punkt();
    krzywe2();
    punkt2();
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
void MyWindow::rysujPunkty2(int x, int y){
    int i,j;
    for(i = x - 5; i <= x + 5; i++){
        for(j = y - 5; j <= y + 5; j++){
            rysujPiksel2(i,j,255,0,0);
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
    for(vector<pair<int, int> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        if(it->first + 5 >= x && it->first - 5 <= x && it->second + 5 >= y && it->second - 5 <= y){
            przesun = it;
            kontorla = true;
            return;
        }
    }
}
void MyWindow::sprawdz2(int x, int y){
    for(vector<pair<int, int> >::iterator it = punkty2.begin(); it != punkty2.end(); it++){
        if(it->first + 5 >= x && it->first - 5 <= x && it->second + 5 >= y && it->second - 5 <= y){
            przesun2 = it;
            kontorla2 = true;
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
void MyWindow::punkt2(){
    if(punkty2.empty())
        return;
    for(vector<pair<int, int> >::iterator it = punkty2.begin(); it != punkty2.end(); it++){
        rysujPunkty2(it->first,it->second);
    }
}
void MyWindow::krzywe(){
    pair<int,int> p1;
    if(punkty.empty())
        return;
    vector<pair<int, int> >::iterator it = punkty.begin();
    p1 = *it;
    for(vector<pair<int, int> >::iterator it = punkty.begin() + 1; it != punkty.end(); it++){
        prosta(p1.first, p1.second, it->first, it->second, 0, 255, 0);
        p1 = *it;
    }
    prosta(p1.first, p1.second, punkty.begin()->first, punkty.begin()->second, 0, 255, 0);
}
void MyWindow::krzywe2(){
    pair<int,int> p1;
    if(punkty2.empty())
        return;
    vector<pair<int, int> >::iterator it = punkty2.begin();
    p1 = *it;
    for(vector<pair<int, int> >::iterator it = punkty2.begin() + 1; it != punkty2.end(); it++){
        prosta2(p1.first, p1.second, it->first, it->second, 0, 255, 0);
        p1 = *it;
    }
    prosta2(p1.first, p1.second, punkty2.begin()->first, punkty2.begin()->second, 0, 255, 0);
}
double MyWindow::Interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}
void MyWindow::Teksturowanie(){
    pair<int,int> A,B,C,At,Bt,Ct;
    int Xmin,Xmax,Ymin,Ymax;
    double a,b,v,w,u,delta;
    int i,j,x,y,xn,yn;
    int r,g,blue;
    unsigned char *org;
    org = img->bits();
    A = *punkty2.begin();
    B = *(punkty2.begin()+1);
    C = *(punkty2.begin()+2);
    At = *punkty.begin();
    Bt = *(punkty.begin()+1);
    Ct = *(punkty.begin()+2);
    Xmin = Xmax = A.first;
    Ymin = Ymax = A.second;
    for(vector<pair<int, int> >::iterator it = punkty2.begin(); it != punkty2.end(); it++){
        if(it->first < Xmin)
            Xmin = it->first;
        if(it->first > Xmax)
            Xmax = it->first;
        if(it->second < Ymin)
            Ymin = it->second;
        if(it->second > Ymax)
            Ymax = it->second;
    }
    delta = (((B.first - A.first) * (C.second - A.second)) - ((C.first - A.first) * (B.second - A.second)));
    for(i=Ymin; i<Ymax; i++)
    {
        for(j=Xmin; j<Xmax; j++)
        {
            v = (((j - A.first) * (C.second - A.second)) - ((C.first - A.first) * (i - A.second))) / delta;
            w = (((B.first - A.first) * (i - A.second)) - ((j - A.first) * (B.second - A.second))) / delta;
            u = 1 - v - w;
            if (u > 0 && u < 1 && v > 0 && v < 1 && w > 0 && w < 1){
               a = static_cast<double>(u * At.first + v * Bt.first + w * Ct.first);
               b = static_cast<double>(u * At.second + v * Bt.second + w * Ct.second);
               x = static_cast<int>(a);
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
               rysujPiksel2(j,i,r,g,blue);
            }

        }
    }

}
