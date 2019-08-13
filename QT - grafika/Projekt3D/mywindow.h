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
   explicit MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

private:
    Ui::MyWindow *ui;
    QImage *img;
    int szer;
    int wys;
    int poczX;
    int poczY;
    // Zmienne przemieszczenia
    int rowniki = 18;
    int poludniki = 36;
    int przesuniecieOX = 0;
    int przesuniecieOY = 0;
    int przesuniecieOZ = 0;
    double skalowanieOX = 1;
    double skalowanieOY = 1;
    double skalowanieOZ = 1;
    double obrotOX = 0;
    double obrotOY = 0;
    double obrotOZ = 0;
    int swiatloOX = 0;
    int swiatloOY = 0;
    int swiatloOZ = 500;
    double R = 0.5;
    double G = 0.5;
    double B = 0.5;

    // Funkcje
    void czysc();
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
    void on_pushButton_clicked();
    void on_horizontalSlider_16_valueChanged(int value);
    void on_horizontalSlider_17_valueChanged(int value);
    void on_horizontalSlider_18_valueChanged(int value);
    void on_horizontalSlider_13_valueChanged(int value);
    void on_horizontalSlider_14_valueChanged(int value);
    void on_horizontalSlider_15_valueChanged(int value);
    void on_pushButton_3_clicked();
    void on_horizontalScrollBar_valueChanged(int value);
    void on_horizontalScrollBar_2_valueChanged(int value);
};

#endif // MYWINDOW_H
