#include "punkt.h"
#include <cmath>
Punkt::Punkt()
{

}
Punkt::Punkt(double x, double y, double z){
    X = x;
    Y = y;
    Z = z;
}
void Punkt::set(double x, double y, double z){
    X = x;
    Y = y;
    Z = z;
}
double Punkt::getX(){
    return X;
}
double Punkt::getY(){
    return Y;
}
double Punkt::getZ(){
    return Z;
}
Punkt Punkt::operator+(const Punkt &add){
    return Punkt(X + add.X, Y + add.Y, Z + add.Z);
}
Punkt Punkt::operator-(const Punkt &add){
    return Punkt(X - add.X, Y - add.Y, Z - add.Z);
}
Punkt Punkt::operator*(const Punkt &add){
    return Punkt(Y * add.Z - Z * add.Y,Z * add.X - X * add.Z,X * add.Y - Y * add.X);
}
Punkt Punkt::operator*(const double &add){
    return Punkt(X * add, Y * add, Z * add);
}
Punkt Punkt::operator*(const double (*matrix)[4]){
    double x, y, z;
    x = X * matrix[0][0] + Y * matrix[0][1] + Z * matrix[0][2] + matrix[0][3];
    y = X * matrix[1][0] + Y * matrix[1][1] + Z * matrix[1][2] + matrix[1][3];
    z = X * matrix[2][0] + Y * matrix[2][1] + Z * matrix[2][2] + matrix[2][3];
    return Punkt(x,y,z);
}
double Punkt::iloczyn(const Punkt &add){
    return X * add.X + Y * add.Y + Z * add.Z;
}
