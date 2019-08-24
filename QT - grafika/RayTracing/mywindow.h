#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

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

    void czysc();

private slots:
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void paintEvent(QPaintEvent*);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MYWINDOW_H
