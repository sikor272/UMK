// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji
// Szkielet tego pliku jest tworzony przez QtCreator
// Mozemy do niego dodac deklaracje wlasnych pol i metod

#ifndef MYWINDOW_H
#define MYWINDOW_H

// Dolaczamy plik naglowkowy klasy QMainWindow,
// Klasa QMainWindow posiada swoj wlasny layout.
// latwo mozna do niej dodac pasek menu, widzety dokujace,
// pasek narzedzi i pasek statusu. Na srodku okna
// wyswietlanego przez QMainWindow znajduje sie obszar,
// ktory mozna wypelnic roznymi widgetami.
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
#include <vector>
#include <utility>
using namespace std;
namespace Ui {
    class MyWindow;
}

// MyWindow jest podklasa klasy QMainWindow.
class MyWindow : public QMainWindow
{
    // Q_OBJECT jest to makro, ktore musi sie znajdowac
    // we wszystkich klasach definiujacych wlasne sygnaly i sloty
    // W naszej klasie nie jest ono potrzebne,
    // ale QtCreator dodaje je automatycznie do kazdej klasy.
    Q_OBJECT

public:
    // Typowa deklaracja konstruktora w Qt.
    // Parametr "parent" okresla rodzica komponenetu.
    // W przypadku naszej klasy parametr ten wskazuje na null
    // co oznacza, ze komponenet nie ma rodzica, jest to
    // komponenet najwyzszego poziomu
    explicit MyWindow(QWidget *parent = 0);

    // Deklaracja destruktora
    ~MyWindow();

private:
    // QtCreator pozwala na tworzenie GUI za pomoca graficznego kreatora.
    // Skladniki interfejsu i ich wlasciwosci zapisane sa wowczas
    // w pliku XML "nazwa_klasy.ui"
    // Do poszczegolnych elementow GUI odwolujemy sie za pomoca zmiennej "ui"
    Ui::MyWindow *ui;

    // Pole przechowujace obrazek
    QImage *img;
    QImage *img2;
    QImage *img3;
    QImage **wynik;
    QImage *copy;
    QImage *copy2;
    int szer;
    int wys;
    int poczX,poczX2,poczX3;
    int poczY,poczY2,poczY3;
    unsigned long long licznik = 1;
    unsigned long long podzial = 2;
    pair<int,int> **punkty;
    pair<int,int> **punkty2;
    int moveX = 0,moveY = 0;
    bool kontorla = false;
    bool kontorla2 = false;


    void prosta(int, int, int, int, int, int, int);
    void prosta2(int, int, int, int, int, int, int);

    void sprawdz(int x, int y);
    void sprawdz2(int x, int y);

    void rysujPiksel(int x, int y, int r, int g, int b);
    void rysujPiksel2(int x, int y, int r, int g, int b);
    void rysujPiksel3(int x, int y, int r, int g, int b, int i);

    void rysujPunkty(int x, int y, int r, int g, int b);
    void rysujPunkty2(int x, int y, int r, int g, int b);

    void punkt();
    void krzywe();
    void punkt2();
    void krzywe2();
    void Teksturowanie(int s, pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> At, pair<int,int> Bt, pair<int,int> Ct);
    void czysc();

    double Interpolacja(int x,int y,double dx);

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
    void on_pushButton_3_clicked();
};

#endif // MYWINDOW_H
