// Glowny plik aplikacji, utworzony automatycznie przez QtCreator
// W wiekszosci przypadkow nie musimy tu nic zmieniac

// Dolaczamy plik naglowkowy klasy QApplication
#include <QApplication>

// Dolaczamy plik naglowkowy klasy glownego widgetu (okna) aplikacji
#include "mywindow.h"

int main(int argc, char *argv[])
{

    // Tworzymy objekt QApplication. Zarzadza on zasobami calej aplikacji
    // i jest niezbedny do stworzenia jakiejkolwiek aplikacji Qt posiadajacej GUI.
    // Przekazujemy mu dwa argumenty argc i argv, poniewaz Qt moze rowniez
    // przyjmowac argumenty z linii komend.
    QApplication a(argc, argv);

    // Tworzymy obiekt klasy MyWindow - glownego okna naszej aplikacji.
    // Jest to klasa zdefiniowana przez nas.
    // Jej definicja znajduje sie w plikach mainwindow.h i mainwindow.cpp
    MyWindow w;

    // Pokazujemy glowne okno aplikacji na ekranie. Domyslnie jest ono niewidoczne.
    // Wszystkie widgety (elementy GUI) zawarte w glownym oknie beda rowniez widoczne.
    w.show();

    // Przekazujemy kontrole nad aplikacja do Qt. Program wchodzi w petle zdarzen
    // tzn. zaczyna oczekiwac na akcje uzytkownika - klikniecia przycisku myszy,
    // lub klawisza klawiatury itp.
    return a.exec();
}
