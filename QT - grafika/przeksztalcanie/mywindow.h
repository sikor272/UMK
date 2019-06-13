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
#include <QFileDialog>
// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>

// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>

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
    QImage *img,*kopia,*oryginal;
    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    // Zmienne przemieszczenia
    double obrot = 0;
    int pion = 0;
    int poziom = 0;
    int krzywapion = 0;
    int krzywapoziom = 0;
    double skalowanieOX = 1;
    double skalowanieOY = 1;
    double pochylenieOX = 0;
    double pochylenieOY = 0;
    double przesuniecie[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double MacierzSkal[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double MacierzObrot[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double MacierzPochylenie[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double wynik[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    double pomoc[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    // Deklaracje funkcji
    void czysc();
    void reset();
    void czysc_kopia();
    void wywolywanie();
    void Przesuniecie();
    void Obrot();
    void Scal();
    void Pochylenie();
    void Mnozenie(double dane[3][3]);
    double Interpolacja(int x, int y, double dx);
    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void paintEvent(QPaintEvent*);
    void on_szerokosc_valueChanged(int value);
    void on_wysokosc_valueChanged(int value);
    void on_rotacja_sliderMoved(int position);
    void on_horizontalSlider_valueChanged(int value);
    void on_scalszer_valueChanged(int value);
    void on_scalwys_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
    void on_pushButton_clicked();
};

#endif // MYWINDOW_H
