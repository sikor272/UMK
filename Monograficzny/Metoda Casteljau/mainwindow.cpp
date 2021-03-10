#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();
    img = new QImage(szer,wys,QImage::Format_RGB32);
    copy = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    *copy = img->copy();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}
void MainWindow::on_cleanButton_clicked()
{
    czysc();
    update();
}
void MainWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();
    licznik = 0;
    kontrola = false;
    punkty.clear();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255;
            ptr[szer*4*i + 4*j + 1] = 255;
            ptr[szer*4*i + 4*j + 2] = 255;
        }
    }
    *copy = img->copy();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    *img = copy->copy();
    x -= poczX;
    y -= poczY;
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
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    *img = copy->copy();
    x -= poczX;
    y -= poczY;
    if(event->button() == Qt::LeftButton)
    {
        if((x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            if(usun){
                sprawdz(x,y);
                if(kontrola){
                    punkty.erase(przesun);
                    licznik--;
                    kontrola = false;
                }
            } else if(!usun){
                punkty.push_back(make_pair(x,y));
                licznik++;
            }
        }
    }
    else
    {
        if(kontrola == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            pair<double, double> przesuniety;
            przesuniety = make_pair(x,y);
            *przesun = przesuniety;
            kontrola = false;
        }
    }
    krzywe();
    punkt();
    update();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    *img = copy->copy();
    x -= poczX;
    y -= poczY;
    if(event->button() == Qt::LeftButton)
    {

    }
    else
    {
        if(kontrola == true && (x>=0)&&(y>=0)&&(x<szer)&&(y<wys)){
            pair<double, double> przesuniety;
            przesuniety = make_pair(x,y);
            *przesun = przesuniety;
        }
    }
    krzywe();
    punkt();
    update();
}
void MainWindow::rysujPunkty(int x, int y, int r, int g, int b, int size){
    int i,j;
    for(i = x - size; i <= x + size; i++){
        for(j = y - size; j <= y + size; j++){
            rysujPiksel(i,j,r,g,b);
        }
    }
}
void MainWindow::rysujPiksel(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = static_cast<unsigned char>(b);
        ptr[szer * 4 * y + 4 * x + 1] = static_cast<unsigned char>(g);
        ptr[szer * 4 * y + 4 * x + 2] = static_cast<unsigned char>(r);
    }
}
void MainWindow::prosta(int startx, int starty, int koniecx, int koniecy,int r, int g, int c){
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
            pom = static_cast<int>(a * i + b);
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
        a = (koniecx - startx) / static_cast<double> (koniecy - starty);
        b = startx - a * starty;
        for(i = starty; i <= koniecy; i++){
            pom = static_cast<int>(a * i + b);
            rysujPiksel(pom,i,r,g,c);
        }
    }
}
void MainWindow::sprawdz(int x, int y){
    for(vector<pair<double, double> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        if(it->first + 5 >= x && it->first - 5 <= x && it->second + 5 >= y && it->second - 5 <= y){
            przesun = it;
            kontrola = true;
            return;
        }
    }
}
void MainWindow::punkt(){
    if(punkty.empty())
        return;
    for(vector<pair<double, double> >::iterator it = punkty.begin(); it != punkty.end(); it++){
        rysujPunkty(static_cast<int>(it->first),static_cast<int>(it->second), 255, 0, 0, 5);
    }
}
void MainWindow::krzywe(){
    vector<pair<double, double> > help, output;
    pair<double,double> pkt_1, pkt_2;
    double t = 0;
    vector<pair<double, double> >::iterator it;
    if(punkty.empty())
        return;
    //while(t <= 1.0) {
        help = wylicz(licznik, punkty, 1 - steps);
        it = help.begin();
        output.push_back(*(it));
        pkt_1 = *(it);
        rysujPunkty(static_cast<int>(pkt_1.first), static_cast<int>(pkt_1.second), 0, 0, 255, 2);
     //   t += steps;
    //}
    /*pkt_1 = *(output.begin());
    for(it = output.begin(); it != output.end();it++) {
        pkt_2 = *(it);
        prosta(static_cast<int>(pkt_1.first), static_cast<int>(pkt_1.second), static_cast<int>(pkt_2.first), static_cast<int>(pkt_2.second), 0, 0, 0);
        pkt_1 = pkt_2;
    }
    it = punkty.end();
    pkt_2 = *(it - 1);
    prosta(static_cast<int>(pkt_1.first), static_cast<int>(pkt_1.second), static_cast<int>(pkt_2.first), static_cast<int>(pkt_2.second), 0, 0, 0);
*/}

vector<pair<double, double> > MainWindow::wylicz(int count, vector<pair<double, double> > points, double step)
{
    int i = 0;
    double x, y;
    vector<pair<double, double> > help;
    pair<double, double> tmp_1, tmp_2;
    if(count == 1) {
        return points;
    }
    for(vector<pair<double, double> >::iterator it = points.begin(); i < count - 1; i++, it += 1) {
        tmp_1 = *(it);
        tmp_2 = *(it + 1);
        x = (tmp_1.first + (1-step) * (tmp_2.first - tmp_1.first));
        y = (tmp_1.second + (1-step) * (tmp_2.second - tmp_1.second));
        help.push_back(make_pair(x, y));
    }
    return wylicz(count - 1, help, step);
}


void MainWindow::on_pushButton_clicked()
{
    *img = copy->copy();
    krzywe();
    punkty.clear();
    licznik = 0;
    kontrola = false;
    *copy = img->copy();
    update();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        usun = true;
    } else {
        usun = false;
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    steps = static_cast<double>(value) / 1000.0;
    *img = copy->copy();
    krzywe();
    punkt();
    update();
}
