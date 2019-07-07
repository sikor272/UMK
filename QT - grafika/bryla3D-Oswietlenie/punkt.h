#ifndef PUNKT_H
#define PUNKT_H


class Punkt
{
/*private:
    double X;
    double Y;
    double Z;*/
public:
    double X;
    double Y;
    double Z;
    Punkt();
    Punkt(double x, double y, double z);
    void set(double x, double y, double z);
    double getX();
    double getY();
    double getZ();
    Punkt operator+(const Punkt &add);
    Punkt operator-(const Punkt &add);
    Punkt operator*(const Punkt &add);
    Punkt operator*(const double &add);
    Punkt operator*(const double matrix[4][4]);
    Punkt operator/(const double &div);
    Punkt counter();
    double iloczyn(const Punkt &add);
    double dlugosc();
    double odleglosc(const Punkt &add);
    Punkt normalizacja();
};

#endif // PUNKT_H
