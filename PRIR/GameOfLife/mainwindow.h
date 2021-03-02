#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// QPainter to klasa umozliwiajaca niskopoziomowe rysowanie
// na elementach GUI
#include <QPainter>
// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>
// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    // Pole przechowujace obrazek
    QImage *img;

    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szerokosc;
    int wysokosc;
    int poczatekX;
    int poczatekY;

    // Zmienne pomocnicze
    int rozmiar = 6;
    int iloscWiersz = 1;
    int iloscKolumna = 1;
    int populacja = 50;
    int szybkosc = 500;
    int **tablica; // {0, 1} = {Death, Alive}

    bool wykonuj = false;
    QTimer *timer;
    // Deklaracje funkcji
    void czysc();
    void reset();
    void rysujPiksel(int x, int y, int red, int green, int blue);
    void rysujPole(int x, int y);
    void rysuj();
    int sasiedzi(int x, int y);
    int zycie(int x, int y);
    void obliczKrok();
    void losowanie();


private slots:
    void petla();
    void paintEvent(QPaintEvent*) override;
    void on_start_clicked();
    void on_stop_clicked();
    void on_reset_clicked();
    void on_size_valueChanged(int arg1);
    void on_ppl_valueChanged(int arg1);
    void on_speed_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
