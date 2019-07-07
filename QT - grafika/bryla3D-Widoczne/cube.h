#ifndef CUBE_H
#define CUBE_H
#include "punkt.h"
#include <algorithm>
using namespace std;
class Cube
{
private:
    Punkt A,B,C,D,E,F,G,H;
    Punkt center;
    double Dwidza = -500;
    double MacierzWynik[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    pair<int,int> a,b,c,d,e,f,g,h;

public:
    Cube();
    Cube(double x, double y, double z, double large);
    void set(double x, double y, double z, double large);
    // Przeksztalcenia
    void rotate(double obrotOX, double obrotOY, double obrotOZ);
    void scale(double skalowanieOX, double skalowanieOY, double skalowanieOZ);
    void slope(double pochylenieOX, double pochylenieOY, double pochylenieOZ);
    void move(double przesuniecieOX, double przesuniecieOY, double przesuniecieOZ);
    void matrix(double B[4][4]);
    pair<int,int> convert(Punkt punkt);
    void update();
    bool checkTriangle(Punkt gora, Punkt dol, Punkt prawy);

    bool checkFront();
    bool checkUp();
    bool checkDown();
    bool checkLeft();
    bool checkRight();
    bool checkBack();

    int **Front();
    int **Up();
    int **Down();
    int **Left();
    int **Right();
    int **Back();

};

#endif // CUBE_H
