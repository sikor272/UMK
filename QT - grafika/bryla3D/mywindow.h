#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
using namespace std;


namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;

    QImage *img;
    int szer;
    int wys;
    int poczX;
    int poczY;
    // Zmienne przemieszczenia
    int D = -100;
    int przesuniecieOX = 0;
    int przesuniecieOY = 0;
    int przesuniecieOZ = 0;
    double MacierzPrzesun[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    double skalowanieOX = 1;
    double skalowanieOY = 1;
    double skalowanieOZ = 1;
    double MacierzSkal[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    double pochylenieOX = 0;
    double pochylenieOY = 0;
    double pochylenieOZ = 0;
    double MacierzPochylenieOX[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double MacierzPochylenieOY[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double MacierzPochylenieOZ[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    double obrotOX = 0;
    double obrotOY = 0;
    double obrotOZ = 0;
    double MacierzObrotOX[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double MacierzObrotOY[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double MacierzObrotOZ[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    double wynik[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double pomoc[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double wyswietl[4] = {0,0,0,0};
    double a[4] = {-50,-50,-50,1};
    double b[4] = {50,-50,-50,1};
    double c[4] = {-50,50,-50,1};
    double d[4] = {50,50,-50,1};
    double e[4] = {-50,-50,50,1};
    double f[4] = {50,-50,50,1};
    double g[4] = {-50,50,50,1};
    double h[4] = {50,50,50,1};
    // Funkcje
    void czysc();
    void reset();
    void Przesuniecie();
    void ObrotOX();
    void ObrotOY();
    void ObrotOZ();
    void Scalowanie();
    void PochylenieOX();
    void PochylenieOY();
    void PochylenieOZ();
    void Mnozenie(double dane[4][4]);
    void Wynikowe(double dane[4]);
    void Rysowanie();
    void rysujPiksel(int x, int y, int r, int g, int b);
    void wykonaj();
    void rysujPunkty(int x, int y, int r, int g, int b);
    void prosta(int startx, int starty, int koniecx, int koniecy,int r, int g, int c);
private slots:
    void paintEvent(QPaintEvent*);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_dial_valueChanged(int value);
    void on_dial_2_valueChanged(int value);
    void on_dial_3_valueChanged(int value);
    void on_horizontalSlider_7_valueChanged(int value);
    void on_horizontalSlider_8_valueChanged(int value);
    void on_horizontalSlider_9_valueChanged(int value);
    void on_pushButton_clicked();
};

#endif // MYWINDOW_H
