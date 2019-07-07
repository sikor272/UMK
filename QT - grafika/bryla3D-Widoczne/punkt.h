#ifndef PUNKT_H
#define PUNKT_H


class Punkt
{
private:
    double X;
    double Y;
    double Z;
public:
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
    double iloczyn(const Punkt &add);
};

#endif // PUNKT_H
