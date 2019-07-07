#include "cube.h"
#include <cmath>
#include <iostream>
#include <QDebug>
using namespace std;
Cube::Cube()
{

}
Cube::Cube(double x, double y, double z, double large){
    center.set(x,y,z);
    A.set(-large,-large,+large);
    B.set(+large,-large,+large);
    C.set(-large,+large,+large);
    D.set(+large,+large,+large);
    E.set(-large,-large,-large);
    F.set(+large,-large,-large);
    G.set(-large,+large,-large);
    H.set(+large,+large,-large);
}
void Cube::set(double x, double y, double z, double large){
    center.set(x,y,z);
    A.set(-large,-large,+large);
    B.set(+large,-large,+large);
    C.set(-large,+large,+large);
    D.set(+large,+large,+large);
    E.set(-large,-large,-large);
    F.set(+large,-large,-large);
    G.set(-large,+large,-large);
    H.set(+large,+large,-large);
}
void Cube::rotate(double obrotOX, double obrotOY, double obrotOZ){
    double MacierzObrotOX[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double MacierzObrotOY[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    double MacierzObrotOZ[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    MacierzObrotOX[0][0] = 1;
    MacierzObrotOX[1][1] = round(cos(obrotOX)*10000)/10000;
    MacierzObrotOX[1][2] = -round(sin(obrotOX)*10000)/10000;
    MacierzObrotOX[2][1] = round(sin(obrotOX)*10000)/10000;
    MacierzObrotOX[2][2] = round(cos(obrotOX)*10000)/10000;
    MacierzObrotOX[3][3] = 1;
    MacierzObrotOY[0][0] = round(cos(obrotOY)*10000)/10000;
    MacierzObrotOY[0][2] = -round(sin(obrotOY)*10000)/10000;
    MacierzObrotOY[1][1] = 1;
    MacierzObrotOY[2][0] = round(sin(obrotOY)*10000)/10000;
    MacierzObrotOY[2][2] = round(cos(obrotOY)*10000)/10000;
    MacierzObrotOY[3][3] = 1;
    MacierzObrotOZ[0][0] = round(cos(obrotOZ)*10000)/10000;
    MacierzObrotOZ[0][1] = -round(sin(obrotOZ)*10000)/10000;
    MacierzObrotOZ[1][0] = round(sin(obrotOZ)*10000)/10000;
    MacierzObrotOZ[1][1] = round(cos(obrotOZ)*10000)/10000;
    MacierzObrotOZ[2][2] = 1;
    MacierzObrotOZ[3][3] = 1;
    matrix(MacierzObrotOX);
    matrix(MacierzObrotOY);
    matrix(MacierzObrotOZ);
    update();
}
void Cube::scale(double skalowanieOX, double skalowanieOY, double skalowanieOZ){
    double MacierzSkal[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    MacierzSkal[0][0] = skalowanieOX;
    MacierzSkal[1][1] = skalowanieOY;
    MacierzSkal[2][2] = skalowanieOZ;
    MacierzSkal[3][3] = 1;
    matrix(MacierzSkal);
    update();
}
void Cube::slope(double pochylenieOX, double pochylenieOY, double pochylenieOZ){
    double MacierzPochylenieOX[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    double MacierzPochylenieOY[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    double MacierzPochylenieOZ[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    MacierzPochylenieOX[1][0] = pochylenieOY;
    MacierzPochylenieOX[2][0] = pochylenieOZ;
    MacierzPochylenieOY[0][1] = pochylenieOX;
    MacierzPochylenieOY[2][1] = pochylenieOZ;
    MacierzPochylenieOZ[0][2] = pochylenieOX;
    MacierzPochylenieOZ[1][2] = pochylenieOY;
    matrix(MacierzPochylenieOX);
    matrix(MacierzPochylenieOY);
    matrix(MacierzPochylenieOZ);
    update();
}
void Cube::move(double przesuniecieOX, double przesuniecieOY, double przesuniecieOZ){
    double MacierzPrzesun[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    MacierzPrzesun[0][3] = przesuniecieOX;
    MacierzPrzesun[1][3] = przesuniecieOY;
    MacierzPrzesun[2][3] = przesuniecieOZ;
    matrix(MacierzPrzesun);
    update();
    //center = center + Punkt(przesuniecieOX, przesuniecieOY, przesuniecieOZ);
}
void Cube::matrix(double (*B)[4]){
    double pomoc[4][4],s;
    int i,j,k;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            s = 0;
            for(k = 0; k < 4; k++)
                s += MacierzWynik[i][k] * B[k][j];
            pomoc[i][j] = s;
        }
    }
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            MacierzWynik[i][j] = pomoc[i][j];
}
void Cube::update(){
    A = A * MacierzWynik + Punkt(0,0,center.getZ());
    B = B * MacierzWynik + Punkt(0,0,center.getZ());
    C = C * MacierzWynik + Punkt(0,0,center.getZ());
    D = D * MacierzWynik + Punkt(0,0,center.getZ());
    E = E * MacierzWynik + Punkt(0,0,center.getZ());
    F = F * MacierzWynik + Punkt(0,0,center.getZ());
    G = G * MacierzWynik + Punkt(0,0,center.getZ());
    H = H * MacierzWynik + Punkt(0,0,center.getZ());
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            MacierzWynik[i][j] = 0;
        MacierzWynik[i][i] = 1;
    }
    a = convert(A);
    b = convert(B);
    c = convert(C);
    d = convert(D);
    e = convert(E);
    f = convert(F);
    g = convert(G);
    h = convert(H);
    //qDebug() << a << b << c << d << e << f << g << h;
}
pair<int,int> Cube::convert(Punkt punkt){
    double tmp;
    tmp = (Dwidza + punkt.getZ()) / Dwidza;
    if(tmp == 0.0){
        tmp = 0.0001;
    }
    return make_pair(static_cast<int>(punkt.getX() / tmp) + center.getX(),static_cast<int>(punkt.getY() / tmp) + center.getY());
}
bool Cube::checkTriangle(Punkt gora, Punkt dol, Punkt prawy){
    Punkt Pion = gora - dol;
    Punkt Poziom = prawy - dol;
    Punkt Warstwa = Pion * Poziom;
    double wynik = Warstwa.iloczyn(dol  + Punkt(0,0,Dwidza));
    return wynik < 0;
}
bool Cube::checkFront(){
    return checkTriangle(A,C,D);
}
pair<int,int>* Cube::Front(){
    pair<int,int>* punkty = new pair<int,int>[4];
    punkty[0] = a;
    punkty[1] = b;
    punkty[2] = c;
    punkty[3] = d;
    return punkty;
}
bool Cube::checkUp(){
    return checkTriangle(E,A,B);
}
pair<int,int>* Cube::Up(){
    pair<int,int>* punkty = new pair<int,int>[4];
    punkty[0] = e;
    punkty[1] = f;
    punkty[2] = a;
    punkty[3] = b;
    return punkty;
}
bool Cube::checkDown(){
    return checkTriangle(C,G,H);
}
pair<int,int>* Cube::Down(){
    pair<int,int>* punkty = new pair<int,int>[4];
    punkty[0] = c;
    punkty[1] = d;
    punkty[2] = g;
    punkty[3] = h;
    return punkty;
}
bool Cube::checkLeft(){
    return checkTriangle(E,G,C);
}
pair<int,int>* Cube::Left(){
    pair<int,int>* punkty = new pair<int,int>[4];
    punkty[0] = e;
    punkty[1] = a;
    punkty[2] = g;
    punkty[3] = c;
    return punkty;
}
bool Cube::checkRight(){
    return checkTriangle(B,D,H);
}
pair<int,int>* Cube::Right(){
    pair<int,int>* punkty = new pair<int,int>[4];
    punkty[0] = b;
    punkty[1] = f;
    punkty[2] = d;
    punkty[3] = h;
    return punkty;
}
bool Cube::checkBack(){
    return checkTriangle(G,E,F);
}
pair<int,int>* Cube::Back(){
    pair<int,int>* punkty = new pair<int,int>[4];
    punkty[0] = e;
    punkty[1] = f;
    punkty[2] = g;
    punkty[3] = h;
    return punkty;
}
