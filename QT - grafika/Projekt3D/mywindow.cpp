#include "mywindow.h"
#include <cmath>
#include <QDebug>
#include "ui_mywindow.h"
#include <unistd.h>
static int WIDTH = 501;
static int HEIGHT = 501;
static int Widz = 500;
#define DOUBLE(x) (static_cast<double>(x))
#define INT(x) (static_cast<int>(x))
#define ULL(x) (static_cast<unsigned long long>(x))
#define UCHAR(x) (static_cast<unsigned char>(x))
struct Color{
    double red;
    double green;
    double blue;
    Color() : red(0), green(0), blue(0) {}
    Color(double value) : red(value), green(value), blue(value) {}
    Color(double red, double green, double blue) : red(red), green(green), blue(blue) {}
    Color operator + (Color d) { return Color(red+d.red,green+d.green,blue+d.blue); }
    Color operator += (Color d) { return Color(red+d.red,green+d.green,blue+d.blue); }
    Color operator * (Color d) { return Color(red*d.red,green*d.green,blue*d.blue); }
    Color operator *= (Color d) { return Color(red*d.red,green*d.green,blue*d.blue); }
    Color operator * (double t) { return Color(red*t,green*t,blue*t); }
    Color operator *= (double t) { return Color(red*t,green*t,blue*t); }
    Color operator / (double t) { return Color(red/t,green/t,blue/t); }
    Color operator /= (double t) { return Color(red/t,green/t,blue/t); }
    double getRed() { return min(1.0,red)*255; }
    double getGreen() { return min(1.0,green)*255; }
    double getBlue() { return min(1.0,blue)*255; }
};
struct Vector2{
    double x,y;
    Vector2() : x(0), y(0) {}
    Vector2(double x, double y) : x(x), y(y) {}
    Vector2 operator + (const Vector2& v) const { return Vector2(x+v.x, y+v.y); }
    Vector2 operator += (const Vector2& v) const { return Vector2(x+v.x, y+v.y); }
    Vector2 operator - (const Vector2& v) const { return Vector2(x-v.x, y-v.y); }
    Vector2 operator -= (const Vector2& v) const { return Vector2(x-v.x, y-v.y); }
    Vector2 operator * (int d) const { return Vector2(x*d, y*d); }
    Vector2 operator *= (int d) const { return Vector2(x*d, y*d); }
    Vector2 operator * (const Vector2& v) const { return Vector2(x*v.x, y*v.y); }
    Vector2 operator *= (const Vector2& v) const { return Vector2(x*v.x, y*v.y); }
    Vector2 operator / (int d) const { return Vector2(x/d, y/d); }
    Vector2 operator /= (int d) const { return Vector2(x/d, y/d); }
};
struct Vector3{
    double x,y,z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector3 operator + (const Vector3& v) const { return Vector3(x+v.x, y+v.y, z+v.z); }
    Vector3 operator += (const Vector3& v) const { return Vector3(x+v.x, y+v.y, z+v.z); }
    Vector3 operator - (const Vector3& v) const { return Vector3(x-v.x, y-v.y, z-v.z); }
    Vector3 operator -= (const Vector3& v) const { return Vector3(x-v.x, y-v.y, z-v.z); }
    Vector3 operator - () const { return Vector3(-x, -y, -z); }
    Vector3 operator * (double d) const { return Vector3(x*d, y*d, z*d); }
    Vector3 operator *= (double d) const { return Vector3(x*d, y*d, z*d); }
    Vector3 operator / (double d) const { return Vector3(x/d, y/d, z/d); }
    Vector3 operator /= (double d) const { return Vector3(x/d, y/d, z/d); }
    Vector3 normalize() const { double lg = lenght(); return Vector3(x/lg,y/lg,z/lg); }
    bool operator == (const Vector3& v) const { return x - v.x == 0.0 && y - v.y == 0.0 && z - v.z == 0.0; }
    double lenght() const { return sqrt(x*x + y*y + z*z); }
    double powLength() const { return (x*x+y*y+z*z); }
    Vector3 cross(Vector3 v) { return Vector3((y * v.z) - (z * v.y),(z * v.x) - (x * v.z),(x * v.y) - (y * v.x)); }
    Vector2 toVector2(int Dwidza) const {
        double tmp = 1.0 - z / Dwidza;
        if(tmp == 0.0)tmp = 0.0001;
        return Vector2(static_cast<int>(x / tmp),static_cast<int>(y / tmp));
    }
    void rotateOX(double value) {
        const double radian = (value / 180.0) * M_PI;
        const double cosA = cos(radian), sinA = sin(radian);
        const double tmpY = cosA * y - sinA * z, tmpZ = cosA * z + sinA * y;
        z = tmpZ; y = tmpY;
    }
    void rotateOY(double value) {
        const double radian = (value / 180.0) * M_PI;
        const double cosA = cos(radian), sinA = sin(radian);
        const double tmpZ = cosA * z - sinA * x, tmpX = cosA * x + sinA * z;
        z = tmpZ; x = tmpX;
    }
    void rotateOZ(double value) {
        const double radian = (value / 180.0) * M_PI;
        const double cosA = cos(radian), sinA = sin(radian);
        const double tmpX = cosA * x - sinA * y, tmpY = cosA * y + sinA * x;
        x = tmpX; y = tmpY;
    }
    void scaleOX(double value){ x *= value; }
    void scaleOY(double value){ y *= value; }
    void scaleOZ(double value){ z *= value; }
};
struct Light{
    Vector3 position;
    Color saturation;
    Light(Vector3 position, Color saturation = Color(1,1,1)) : position(position) , saturation(saturation) {}
};
void setPixel(int x, int y, Color value, unsigned char *ptr){
    if(x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT){
        ptr[WIDTH * 4 * y + 4 * x] = UCHAR(value.getBlue());
        ptr[WIDTH * 4 * y + 4 * x + 1] = UCHAR(value.getGreen());
        ptr[WIDTH * 4 * y + 4 * x + 2] = UCHAR(value.getRed());
    }
}

static Vector3 widz(0,0,500);
static Vector3 swiatlo(0,0,500);

void prosta(QImage *img, Color value, int StartX, int StartY, int EndX, int EndY){
    double a, b;
    int pom, i;
    if(abs(StartX - EndX) > abs(StartY - EndY)){
        if(StartX > EndX){
            swap(StartX,EndX);
            swap(StartY,EndY);
        }
        a = (EndY - StartY) / DOUBLE(EndX - StartX);
        b = StartY - a * StartX;
        for(i = StartX; i <= EndX; i++){
            pom = INT(a * i + b);
            setPixel(i, pom, value, img->bits());
        }
    } else {
        if(StartY > EndY){
            swap(StartX,EndX);
            swap(StartY,EndY);
        }
        a = (EndX - StartX) / DOUBLE(EndY - StartY);
        b = StartX - a * StartY;
        for(i = StartY; i <= EndY; i++){
            pom = INT(a * i + b);
            setPixel(pom, i, value, img->bits());
        }
    }
}
int** triangleValue(int **tab,int StartX, int StartY, int EndX, int EndY,
                    Vector3 I, Vector3 II, Vector3 *Ia, Vector3 *Ib,
                    Vector3 A, Vector3 B, Vector3 *Pa, Vector3 *Pb){
    double a, b;
    int pom, i;
    if(abs(StartX - EndX) > abs(StartY - EndY)){
        if(StartX > EndX){
            swap(StartX,EndX);
            swap(StartY,EndY);
            swap(I, II);
            swap(A,B);
        }
        a = (EndY - StartY) / DOUBLE(EndX - StartX);
        b = StartY - a * StartX;
        for(i = StartX; i <= EndX; i++){
            pom = INT(a * i + b);
            if(pom < 0 || pom >= HEIGHT)continue;
            if(i < tab[pom][0]){
                tab[pom][0] = i;
                Ia[pom] = I - (I - II) * (DOUBLE(StartX - i) / DOUBLE(StartX - EndX));
                Pa[pom] = A - (A - B) * (DOUBLE(StartX - i) / DOUBLE(StartX - EndX));
            }
            if(i > tab[pom][1]){
                tab[pom][1] = i;
                Ib[pom] = I - (I - II) * (DOUBLE(StartX - i) / DOUBLE(StartX - EndX));
                Pb[pom] = A - (A - B) * (DOUBLE(StartX - i) / DOUBLE(StartX - EndX));
            }
        }
    } else {
        if(StartY > EndY){
            swap(StartX,EndX);
            swap(StartY,EndY);
            swap(I, II);
            swap(A,B);
        }
        a = (EndX - StartX) / DOUBLE(EndY - StartY);
        b = StartX - a * StartY;
        for(i = max(0,StartY); i <= min(HEIGHT-1,EndY); i++){
            pom = INT(a * i + b);
            if(pom < tab[i][0]){
                tab[i][0] = pom;
                Ia[i] = I - (I - II) * (DOUBLE(StartY - i) / DOUBLE(StartY - EndY));
                Pa[i] = A - (A - B) * (DOUBLE(StartY - i) / DOUBLE(StartY - EndY));
            }
            if(pom > tab[i][1]){
                tab[i][1] = pom;
                Ib[i] = I - (I - II) * (DOUBLE(StartY - i) / DOUBLE(StartY - EndY));
                Pb[i] = A - (A - B) * (DOUBLE(StartY - i) / DOUBLE(StartY - EndY));
            }
        }
    }
    return tab;
}
int min3(int a, int b, int c){
    if(a < b && a < c) return a;
    if(b < c) return b;
    return c;
}
int max3(int a, int b, int c){
    if(a > b && a > c) return a;
    if(b > c) return b;
    return c;
}

inline double scalar(const Vector3& a, const Vector3& b) { return (a.x*b.x + a.y*b.y + a.z*b.z); }
double Interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}

struct Triangle{
    Vector3 A, B, C;
    Vector3 Na,Nb,Nc;
    Color fill;
    QImage *Image = nullptr;
    Vector2 a, b, c;
    Triangle() {}
    Triangle(Vector3 A, Vector3 B, Vector3 C, Color fill) : A(A), B(B), C(C), fill(fill) {}
    Triangle(Vector3 A, Vector3 B, Vector3 C, QImage *Image, Vector2 a, Vector2 b, Vector2 c) :
        A(A), B(B), C(C), Image(Image), a(a), b(b), c(c) {}
    Triangle operator + (Vector3 move) {
        if(Image == nullptr) {
            return Triangle(A + move, B + move, C + move, fill);
        }
        else {
            return Triangle(A + move, B + move, C + move, Image, a, b, c);
        }
    }
    Triangle operator += (Vector3 move) {
        if(Image == nullptr)
            return Triangle(A + move, B + move, C + move, fill);
        else {
            return Triangle(A + move, B + move, C + move, Image, a, b, c);
        }
    }
    Vector3 getNormal(){
        return (A-B).cross(C-B);
    }
    void setNormal(Vector3 NA, Vector3 NB, Vector3 NC) { Na = NA; Nb = NB; Nc = NC; }
    void rotateOX(double value) { A.rotateOX(value); B.rotateOX(value); C.rotateOX(value);
                                  Na.rotateOX(value); Nb.rotateOX(value); Nc.rotateOX(value); }
    void rotateOY(double value) { A.rotateOY(value); B.rotateOY(value); C.rotateOY(value);
                                  Na.rotateOY(value); Nb.rotateOY(value); Nc.rotateOY(value); }
    void rotateOZ(double value) { A.rotateOZ(value); B.rotateOZ(value); C.rotateOZ(value);
                                  Na.rotateOZ(value); Nb.rotateOZ(value); Nc.rotateOZ(value); }
    void scaleOX(double value) { A.scaleOX(value); B.scaleOX(value); C.scaleOX(value); }
    void scaleOY(double value) { A.scaleOY(value); B.scaleOY(value); C.scaleOY(value); }
    void scaleOZ(double value) { A.scaleOZ(value); B.scaleOZ(value); C.scaleOZ(value); }
    bool visible(Vector3 visitor) { return (scalar(getNormal(), B - visitor) < 0); }
    void render(QImage* img, double** Zbufor, Light light){
        if(visible(widz)){
            Vector2 pozA = A.toVector2(Widz), pozB = B.toVector2(Widz), pozC = C.toVector2(Widz);
            int **tab = new int*[ULL(HEIGHT)];
            Vector3 *Ia = new Vector3[ULL(HEIGHT)];
            Vector3 *Ib = new Vector3[ULL(HEIGHT)];
            Vector3 *Pa = new Vector3[ULL(HEIGHT)];
            Vector3 *Pb = new Vector3[ULL(HEIGHT)];

            int i, j;
            for(i = 0; i < HEIGHT; i++){
                tab[i] = new int[2];
                tab[i][0] = WIDTH;
                tab[i][1] = -1;
            }
            pozA.x = pozA.x + 250; pozA.y = 250 - pozA.y;
            pozB.x = pozB.x + 250; pozB.y = 250 - pozB.y;
            pozC.x = pozC.x + 250; pozC.y = 250 - pozC.y;
            tab = triangleValue(tab, INT(pozA.x), INT(pozA.y), INT(pozB.x), INT(pozB.y),
                                Na, Nb, Ia, Ib, A, B, Pa, Pb);
            tab = triangleValue(tab, INT(pozA.x), INT(pozA.y), INT(pozC.x), INT(pozC.y),
                                Na, Nc, Ia, Ib, A, C, Pa, Pb);
            tab = triangleValue(tab, INT(pozC.x), INT(pozC.y), INT(pozB.x), INT(pozB.y),
                                Nc, Nb, Ia, Ib, C, B, Pa, Pb);
            Vector3 R, V, N, L;
            Vector3 I_a, I_b, P_a, P_b, Pozycja;
            for(j = max(0,min3(INT(pozA.y), INT(pozB.y),INT(pozC.y))); j <= min(HEIGHT - 1,max3(INT(pozA.y),INT(pozB.y),INT(pozC.y))); j++){
                I_a = Ia[j]; I_b = Ib[j];
                P_a = Pa[j]; P_b = Pb[j];
                for(i = max(0,tab[j][0]); i <= min(WIDTH-1,tab[j][1]); i++){
                    N = I_a; Pozycja = P_a;
                    if(tab[j][0] != tab[j][1]){
                        N = I_b - ((I_b - I_a) * DOUBLE(tab[j][1] - i) / DOUBLE(tab[j][1] - tab[j][0]));
                        Pozycja = P_b - ((P_b - P_a) * DOUBLE(tab[j][1] - i) / DOUBLE(tab[j][1] - tab[j][0]));
                    }
                    if(Zbufor[i][j] < Pozycja.z){
                        Zbufor[i][j] = Pozycja.z;
                        L = light.position - Pozycja;
                        R = N.normalize() * scalar(N.normalize(),L.normalize()) * 2.0 - L.normalize();
                        V = widz - Pozycja;
                        L = L.normalize();
                        N = N.normalize();
                        R = R.normalize();
                        V = V.normalize();
                        double ambient = 0.111;
                        double diffuse = max(0.0,scalar(N,L));
                        double specular = pow(max(0.0,scalar(R,V)),25);
                        //qDebug() << diffuse << specular;
                        if(Image == nullptr) {
                            setPixel(i,j,fill * Color(ambient + diffuse + specular) * light.saturation,img->bits());
                        } else {
                            unsigned char *org = Image->bits();
                            double u,v,w,delta,an,bn;
                            int x,y,xn,yn;
                            int ImageWIDTH = Image->width();
                            int ImageHEIGHT = Image->height();
                            delta = (((pozB.x - pozA.x) * (pozC.y - pozA.y)) - ((pozC.x - pozA.x) * (pozB.y - pozA.y)));
                            v = (((i - pozA.x) * (pozC.y - pozA.y)) - ((pozC.x - pozA.x) * (j - pozA.y))) / delta;
                            w = (((pozB.x - pozA.x) * (j - pozA.y)) - ((i - pozA.x) * (pozB.y - pozA.y))) / delta;
                            u = 1 - v - w;
                            an = static_cast<double>(u * a.x + v * b.x + w * c.x);
                            bn = static_cast<double>(u * a.y + v * b.y + w * c.y);
                            x = static_cast<int>(an);
                            y = static_cast<int>(bn);
                            if(x >= ImageWIDTH) x = ImageWIDTH - 1;
                                if(x < 0) x = 0;
                                if(y >= ImageHEIGHT) y = ImageHEIGHT - 1;
                                if(y < 0) y = 0;
                            //if(x >= ImageWIDTH || y >= ImageHEIGHT || x < 0 || y < 0)continue;
                            xn = x + 1;
                            yn = y + 1;
                            an -=x;
                            bn -=y;
                            if(yn == ImageHEIGHT)
                                yn--;
                            if(xn == ImageWIDTH)
                                xn--;

                            double red = DOUBLE(INT(round(Interpolacja(static_cast<int>(Interpolacja(org[ImageWIDTH*4*y + 4*x + 2],org[ImageWIDTH*4*yn + 4*x + 2],bn)),
                                                    static_cast<int>(Interpolacja(org[ImageWIDTH*4*y + 4*xn + 2],org[ImageWIDTH*4*yn + 4*xn + 2],bn)),an)))/255.0);
                            double green = DOUBLE(INT(round(Interpolacja(static_cast<int>(Interpolacja(org[ImageWIDTH*4*y + 4*x + 1],org[ImageWIDTH*4*yn + 4*x + 1],bn)),
                                                      static_cast<int>(Interpolacja(org[ImageWIDTH*4*y + 4*xn + 1],org[ImageWIDTH*4*yn + 4*xn + 1],bn)),an)))/255.0);
                            double blue = DOUBLE(INT(round(Interpolacja(static_cast<int>(Interpolacja(org[ImageWIDTH*4*y + 4*x],org[ImageWIDTH*4*yn + 4*x],bn)),
                                                     static_cast<int>(Interpolacja(org[ImageWIDTH*4*y + 4*xn],org[ImageWIDTH*4*yn + 4*xn],bn)),an)))/255.0);
                            setPixel(i,j,Color(red,green,blue) * Color(ambient + diffuse + specular) * light.saturation,img->bits());

                        }
                    }
                }
            }
        }
    }
};
struct Wall{
    Triangle Up,Down;
    Wall(){}
    Wall(Vector3 A, Vector3 B, Vector3 C, Vector3 D, Color fill): Up(A,B,C,fill), Down(C,D,A,fill) {}
    Wall(Vector3 A, Vector3 B, Vector3 C, Vector3 D, QImage *Image) :
        Up(A,B,C,Image,Vector2(0,0),Vector2(Image->width(),0),Vector2(Image->width(),Image->height())),
        Down(C,D,A,Image,Vector2(Image->width(),Image->height()), Vector2(0,Image->height()), Vector2(0,0)) {}
    Wall(Triangle First, Triangle Second) : Up(First), Down(Second) {}
    Vector3 getNormal(){ return Up.getNormal(); }
    Wall operator + (Vector3 move) { return Wall(Up += move, Down += move); }
    Wall operator += (Vector3 move) { return Wall(Up += move, Down += move); }
    void rotateOX(double value) { Up.rotateOX(value); Down.rotateOX(value); }
    void rotateOY(double value) { Up.rotateOY(value); Down.rotateOY(value); }
    void rotateOZ(double value) { Up.rotateOZ(value); Down.rotateOZ(value); }
    void scaleOX(double value) { Up.scaleOX(value); Down.scaleOX(value); }
    void scaleOY(double value) { Up.scaleOY(value); Down.scaleOY(value); }
    void scaleOZ(double value) { Up.scaleOZ(value); Down.scaleOZ(value); }
    void render(QImage* img, double** Zbufor, Light light){
        Up.render(img, Zbufor, light);
        Down.render(img, Zbufor, light);
    }
    void setNormal(Vector3 Na, Vector3 Nb, Vector3 Nc, Vector3 Nd){
        Up.Na = Down.Nc = Na;
        Up.Nb = Nb;
        Up.Nc = Down.Na = Nc;
        Down.Nb = Nd;
    }
};

struct Object{
    Vector3 center;
    Object() {}
    Object(Vector3 center) : center(center) {}
    virtual void render(QImage* img, double** Zbufor, Light light) = 0;
    virtual ~Object();
};
Object::~Object(){

}

struct Cube : Object {
    Wall walls[6];
    Cube(Vector3 center, double x, double y, double z, Color fill) : Object(center) {
        x /= 2.0; y /= 2.0; z /= 2.0;
        Vector3 A(-x,y,z),B(x,y,z),C(x,-y,z),D(-x,-y,z),E(-x,y,-z),F(x,y,-z),G(x,-y,-z),H(-x,-y,-z);
        walls[0] = Wall(A,B,C,D,fill); // front
        walls[1] = Wall(B,F,G,C,fill); // right
        walls[2] = Wall(E,A,D,H,fill); // left
        walls[3] = Wall(E,F,B,A,fill); // up
        walls[4] = Wall(D,C,G,H,fill); // down
        walls[5] = Wall(F,E,H,G,fill); // back
    }
    Cube(Vector3 center, double x, double y, double z, Color fill_1, Color fill_2, Color fill_3,
         Color fill_4, Color fill_5, Color fill_6) : Object(center) {
        x /= 2.0; y /= 2.0; z /= 2.0;
        Vector3 A(-x,y,z),B(x,y,z),C(x,-y,z),D(-x,-y,z),E(-x,y,-z),F(x,y,-z),G(x,-y,-z),H(-x,-y,-z);
        walls[0] = Wall(A,B,C,D,fill_1); // front
        walls[1] = Wall(B,F,G,C,fill_2); // right
        walls[2] = Wall(E,A,D,H,fill_3); // left
        walls[3] = Wall(E,F,B,A,fill_4); // up
        walls[4] = Wall(D,C,G,H,fill_5); // down
        walls[5] = Wall(F,E,H,G,fill_6); // back
    }
    Cube(Vector3 center, double x, double y, double z, QImage *Image) : Object(center) {
        x /= 2.0; y /= 2.0; z /= 2.0;
        Vector3 A(-x,y,z),B(x,y,z),C(x,-y,z),D(-x,-y,z),E(-x,y,-z),F(x,y,-z),G(x,-y,-z),H(-x,-y,-z);
        walls[0] = Wall(A,B,C,D,Image); // front
        walls[1] = Wall(B,F,G,C,Image); // right
        walls[2] = Wall(E,A,D,H,Image); // left
        walls[3] = Wall(E,F,B,A,Image); // up
        walls[4] = Wall(D,C,G,H,Image); // down
        walls[5] = Wall(F,E,H,G,Image); // back
    }
    Cube(Vector3 center, double x, double y, double z,QImage *Image_1,
         QImage *Image_2, QImage *Image_3, QImage *Image_4, QImage *Image_5, QImage *Image_6) : Object(center) {
        x /= 2.0; y /= 2.0; z /= 2.0;
        Vector3 A(-x,y,z),B(x,y,z),C(x,-y,z),D(-x,-y,z),E(-x,y,-z),F(x,y,-z),G(x,-y,-z),H(-x,-y,-z);
        walls[0] = Wall(A,B,C,D,Image_1); // front
        walls[1] = Wall(B,F,G,C,Image_2); // right
        walls[2] = Wall(E,A,D,H,Image_3); // left
        walls[3] = Wall(E,F,B,A,Image_4); // up
        walls[4] = Wall(D,C,G,H,Image_5); // down
        walls[5] = Wall(F,E,H,G,Image_6); // back
    }
    void rotateOX(double value) { for(int i = 0; i < 6; i++) walls[i].rotateOX(value); }
    void rotateOY(double value) { for(int i = 0; i < 6; i++) walls[i].rotateOY(value); }
    void rotateOZ(double value) { for(int i = 0; i < 6; i++) walls[i].rotateOZ(value); }
    void scaleOX(double value) { for(int i = 0; i < 6; i++) walls[i].scaleOX(value); }
    void scaleOY(double value) { for(int i = 0; i < 6; i++) walls[i].scaleOY(value); }
    void scaleOZ(double value) { for(int i = 0; i < 6; i++) walls[i].scaleOZ(value); }
    void move(Vector3 value) { center = center + value; }
    void render(QImage* img, double** Zbufor, Light light);
    ~Cube() {}
};
void Cube::render(QImage* img, double** Zbufor, Light light){
    Wall front = Wall(walls[0] + center), left = Wall(walls[2] + center), right = Wall(walls[1] + center);
    Wall up = Wall(walls[3] + center), down = Wall(walls[4] + center), back = Wall(walls[5] + center);
    Vector3 Nfront = front.getNormal(), Nleft = left.getNormal(), Nright = right.getNormal();
    Vector3 Nup = up.getNormal(), Ndown = down.getNormal(), Nback = back.getNormal();
    front.setNormal ((Nfront + Nup + Nleft)/3.0, (Nfront + Nup + Nright)/3.0, (Nfront + Ndown + Nright)/3.0, (Nfront + Ndown + Nleft)/3.0);
    left.setNormal  ((Nleft + Nback + Nup)/3.0, (Nleft + Nup + Nfront)/3.0, (Nleft + Nfront + Ndown)/3.0, (Nleft + Nback + Ndown)/3.0);
    right.setNormal ((Nright + Nfront + Nup)/3.0, (Nright + Nup + Nback)/3.0, (Nright + Nback + Ndown)/3.0, (Nright + Ndown + Nfront)/3.0);
    up.setNormal    ((Nup + Nback + Nleft)/3.0, (Nup + Nback + Nright)/3.0, (Nup + Nright + Nfront)/3.0, (Nup + Nfront + Nleft)/3.0);
    down.setNormal  ((Ndown + Nfront + Nleft)/3.0, (Ndown + Nfront + Nright)/3.0, (Ndown + Nright + Nback)/3.0, (Ndown + Nback + Nleft)/3.0);
    back.setNormal  ((Nback + Nright + Nup)/3.0, (Nback + Nup + Nleft)/3.0, (Nback + Nleft + Ndown)/3.0, (Nback + Ndown + Nright)/3.0);

    front.render(img, Zbufor, light);
    left.render(img, Zbufor, light);
    right.render(img, Zbufor, light);
    up.render(img, Zbufor, light);
    down.render(img, Zbufor, light);
    back.render(img, Zbufor, light);
}
struct Ball : public Object {
    QVector <Triangle> walls;
    double R;
    Ball(Vector3 center, double r, Color color) : Object(center), R(r) {
        Triangle FrontUpLeft(Vector3(0,0,r),Vector3(-r,0,0),Vector3(0,r,0), color);
        Triangle FrontUpRight(Vector3(r,0,0),Vector3(0,0,r),Vector3(0,r,0), color);
        Triangle FrontDownLeft(Vector3(-r,0,0),Vector3(0,0,r),Vector3(0,-r,0), color);
        Triangle FrontDownRight(Vector3(0,0,r),Vector3(r,0,0),Vector3(0,-r,0), color);
        // Looking front
        Triangle BackUpLeft(Vector3(-r,0,0),Vector3(0,0,-r),Vector3(0,r,0), color);
        Triangle BackUpRight(Vector3(0,0,-r),Vector3(r,0,0),Vector3(0,r,0), color);
        Triangle BackDownLeft(Vector3(0,0,-r),Vector3(-r,0,0),Vector3(0,-r,0), color);
        Triangle BackDownRight(Vector3(r,0,0),Vector3(0,0,-r),Vector3(0,-r,0), color);
        FrontUpLeft.setNormal(Vector3(0,0,1),Vector3(-1,0,0),Vector3(0,1,0));
        FrontUpRight.setNormal(Vector3(1,0,0),Vector3(0,0,1),Vector3(0,1,0));
        FrontDownLeft.setNormal(Vector3(-1,0,0),Vector3(0,0,1),Vector3(0,-1,0));
        FrontDownRight.setNormal(Vector3(0,0,1),Vector3(1,0,0),Vector3(0,-1,0));

        BackUpLeft.setNormal(Vector3(-1,0,0),Vector3(0,0,-1),Vector3(0,1,0));
        BackUpRight.setNormal(Vector3(0,0,-1),Vector3(1,0,0),Vector3(0,1,0));
        BackDownLeft.setNormal(Vector3(0,0,-1),Vector3(-1,0,0),Vector3(0,-1,0));
        BackDownRight.setNormal(Vector3(1,0,0),Vector3(0,0,-1),Vector3(0,-1,0));

        walls.push_back(FrontUpLeft);
        walls.push_back(FrontUpRight);
        walls.push_back(FrontDownLeft);
        walls.push_back(FrontDownRight);
        walls.push_back(BackUpLeft);
        walls.push_back(BackUpRight);
        walls.push_back(BackDownLeft);
        walls.push_back(BackDownRight);
    }
    Ball(Vector3 center, double r, QImage *ful, QImage *fur, QImage *fdl, QImage *fdr,
         QImage *bur, QImage *bul, QImage *bdr, QImage *bdl) : Object(center), R(r) {
        Triangle FrontUpLeft(Vector3(0,0,r),Vector3(-r,0,0),Vector3(0,r,0), ful, Vector2(500,500), Vector2(0,500), Vector2(250,0));
        Triangle FrontUpRight(Vector3(r,0,0),Vector3(0,0,r),Vector3(0,r,0), fur, Vector2(500,500), Vector2(0,500), Vector2(250,0));
        Triangle FrontDownLeft(Vector3(-r,0,0),Vector3(0,0,r),Vector3(0,-r,0), fdl, Vector2(0,0), Vector2(500,0), Vector2(250,500));
        Triangle FrontDownRight(Vector3(0,0,r),Vector3(r,0,0),Vector3(0,-r,0), fdr, Vector2(0,0), Vector2(500,0), Vector2(250,500));
        // Looking front
        Triangle BackUpLeft(Vector3(-r,0,0),Vector3(0,0,-r),Vector3(0,r,0), bul, Vector2(500,500), Vector2(0,500), Vector2(250,0));
        Triangle BackUpRight(Vector3(0,0,-r),Vector3(r,0,0),Vector3(0,r,0), bur, Vector2(500,500), Vector2(0,500), Vector2(250,0));
        Triangle BackDownLeft(Vector3(0,0,-r),Vector3(-r,0,0),Vector3(0,-r,0), bdl, Vector2(0,0), Vector2(500,0), Vector2(250,500));
        Triangle BackDownRight(Vector3(r,0,0),Vector3(0,0,-r),Vector3(0,-r,0), bdr, Vector2(0,0), Vector2(500,0), Vector2(250,500));

        FrontUpLeft.setNormal(Vector3(0,0,1),Vector3(-1,0,0),Vector3(0,1,0));
        FrontUpRight.setNormal(Vector3(1,0,0),Vector3(0,0,1),Vector3(0,1,0));
        FrontDownLeft.setNormal(Vector3(-1,0,0),Vector3(0,0,1),Vector3(0,-1,0));
        FrontDownRight.setNormal(Vector3(0,0,1),Vector3(1,0,0),Vector3(0,-1,0));

        BackUpLeft.setNormal(Vector3(-1,0,0),Vector3(0,0,-1),Vector3(0,1,0));
        BackUpRight.setNormal(Vector3(0,0,-1),Vector3(1,0,0),Vector3(0,1,0));
        BackDownLeft.setNormal(Vector3(0,0,-1),Vector3(-1,0,0),Vector3(0,-1,0));
        BackDownRight.setNormal(Vector3(1,0,0),Vector3(0,0,-1),Vector3(0,-1,0));
        walls.push_back(FrontUpLeft);
        walls.push_back(FrontUpRight);
        walls.push_back(FrontDownLeft);
        walls.push_back(FrontDownRight);
        walls.push_back(BackUpLeft);
        walls.push_back(BackUpRight);
        walls.push_back(BackDownLeft);
        walls.push_back(BackDownRight);
    }
    void rotateOX(double value) { for(int i = 0; i < walls.size(); i++) walls[i].rotateOX(value); }
    void rotateOY(double value) { for(int i = 0; i < walls.size(); i++) walls[i].rotateOY(value); }
    void rotateOZ(double value) { for(int i = 0; i < walls.size(); i++) walls[i].rotateOZ(value); }
    void scaleOX(double value) { for(int i = 0; i < walls.size(); i++) walls[i].scaleOX(value); }
    void scaleOY(double value) { for(int i = 0; i < walls.size(); i++) walls[i].scaleOY(value); }
    void scaleOZ(double value) { for(int i = 0; i < walls.size(); i++) walls[i].scaleOZ(value); }
    void move(Vector3 value) { center = center + value; }
    void render(QImage* img, double** Zbufor, Light light);
    void division(int n) { for(int i = 0 ; i < n; i++) partition(); }
    void partition(){
        QVector <Triangle> old = walls;
        walls.clear();
        for(int i = 0; i < old.size(); i++){
            Vector3 A = old[i].A, B = old[i].B, C = old[i].C;
            Vector3 AB = (A+B)/2.0, AC = (A+C)/2.0 , BC = (B+C)/2.0;
            AB = AB * sqrt( (R * R) / AB.powLength());
            AC = AC * sqrt( (R * R) / AC.powLength());
            BC = BC * sqrt( (R * R) / BC.powLength());
            Triangle Up, Left, Central, Right;
            if(old[i].Image != nullptr){
                Up = Triangle(AC,BC,C,old[i].Image,(old[i].a + old[i].c)/2.0, (old[i].b + old[i].c)/2.0 , old[i].c);
                Left = Triangle(AB,B,BC,old[i].Image,(old[i].b + old[i].c)/2.0, old[i].b, (old[i].a + old[i].b)/2.0);
                Central = Triangle(BC,AC,AB,old[i].Image,(old[i].b + old[i].c)/2.0, (old[i].a + old[i].c)/2.0 , (old[i].a + old[i].b)/2.0);
                Right = Triangle(A,AB,AC,old[i].Image,old[i].a, (old[i].a + old[i].b)/2.0 , (old[i].a + old[i].c)/2.0);
            } else {
                Up = Triangle(AC,BC,C,old[i].fill);
                Left = Triangle(AB,B,BC,old[i].fill);
                Central = Triangle(BC,AC,AB,old[i].fill);
                Right = Triangle(A,AB,AC,old[i].fill);
            }

            Up.setNormal((old[i].Na + old[i].Nc)/2.0, (old[i].Nb + old[i].Nc)/2.0, old[i].Nc);
            Left.setNormal((old[i].Na + old[i].Nb)/2.0, old[i].Nb, (old[i].Nb + old[i].Nc)/2.0);
            Central.setNormal((old[i].Nb + old[i].Nc)/2.0, (old[i].Na + old[i].Nc)/2.0, (old[i].Na + old[i].Nb)/2.0);
            Right.setNormal(old[i].Na, (old[i].Na + old[i].Nb)/2.0, (old[i].Na + old[i].Nc)/2.0);
            walls.push_back(Up);
            walls.push_back(Left);
            walls.push_back(Central);
            walls.push_back(Right);
        }
    }
    ~Ball() {}
};
void Ball::render(QImage* img, double** Zbufor, Light light){
    for(int i = 0; i < walls.size(); i++){
        Triangle tmp = walls[i] + center;
        tmp.setNormal(walls[i].Na, walls[i].Nb, walls[i].Nc);
        tmp.render(img,Zbufor,light);
    }
}
struct Sphere : public Object {
    QVector <Triangle> walls;
    Sphere(Vector3 center, double R, double stacks, double sectors, Color fill) : Object(center) {
        QVector <Vector3> Points;
        QVector <Vector3> Normal;
        QVector <Vector2> Texture;
        double sectorstep = 2 * M_PI / sectors;
        double stackstep = M_PI / stacks;
        double alfa, beta;
        double normals = DOUBLE(1.0f) / R;
        double x, y, z;
        int i, j;
        for(i = 0; i <= stacks; i++){
            alfa = M_PI / 2.0 - i * stackstep;
            z = R * sin(alfa);
            for(j = 0; j <= sectors; j++){
                beta = j * sectorstep;
                x = R * cos(alfa) * cos(beta);
                y = R * cos(alfa) * sin(beta);
                Points.push_back(Vector3(x,y,z));
                Normal.push_back((Vector3(x,y,z) * normals));
                Texture.push_back(Vector2((j / sectors), (i / stacks)));
            }
        }
        int k1, k2;
        for(i = 0; i < stacks; i++){
            k1 = i * INT(sectors + 1);
            k2 = k1 + INT(sectors) + 1;
            for(j = 0; j < sectors; j++, k1++, k2++){
                if(i != 0){
                    Triangle tmp(Points[k2],Points[k1],Points[k1+1],fill);
                    tmp.setNormal(Normal[k2],Normal[k1],Normal[k1+1]);
                    walls.push_back(tmp);
                    qDebug() << Texture[k2].x << Texture[k2].y;
                    qDebug() << Texture[k1].x << Texture[k1].y;
                    qDebug() << Texture[k1 + 1].x << Texture[k1 + 1].y;
                    qDebug() << "-----";
                }
                if(i != INT(stacks - 1)){
                    Triangle tmp(Points[k2 + 1],Points[k2],Points[k1 + 1],fill);
                    tmp.setNormal(Normal[k2 + 1],Normal[k2],Normal[k1 + 1]);
                    walls.push_back(tmp);
                    qDebug() << Texture[k2 + 1].x << Texture[k2 + 1].y;
                    qDebug() << Texture[k2].x << Texture[k2].y;
                    qDebug() << Texture[k1 + 1].x << Texture[k1 + 1].y;
                    qDebug() << "-----";
                }
            }
        }
    }
    Sphere(Vector3 center, double R, double stacks, double sectors, QImage *image) : Object(center) {
        QVector <Vector3> Points;
        QVector <Vector3> Normal;
        QVector <Vector2> Texture;
        double sectorstep = 2 * M_PI / sectors;
        double stackstep = M_PI / stacks;
        double alfa, beta;
        double normals = DOUBLE(1.0f) / R;
        double x, y, z;
        int i, j;
        for(i = 0; i <= stacks; i++){
            alfa = M_PI / 2.0 - i * stackstep;
            z = R * sin(alfa);
            for(j = 0; j <= sectors; j++){
                beta = j * sectorstep;
                x = R * cos(alfa) * cos(beta);
                y = R * cos(alfa) * sin(beta);
                Points.push_back(Vector3(x,y,z));
                Normal.push_back((Vector3(x,y,z) * normals));
                Texture.push_back(Vector2((j / sectors), (i / stacks)));
            }
        }
        int k1, k2;
        for(i = 0; i < stacks; i++){
            k1 = i * INT(sectors + 1);
            k2 = k1 + INT(sectors) + 1;
            for(j = 0; j < sectors; j++, k1++, k2++){
                if(i != 0){
                    Triangle tmp(Points[k2],Points[k1],Points[k1+1],image,
                            Texture[k2] * Vector2(image->width(), image->height()),
                            Texture[k1] * Vector2(image->width(), image->height()),
                            Texture[k1 + 1] * Vector2(image->width(), image->height()));
                    tmp.setNormal(Normal[k2],Normal[k1],Normal[k1+1]);
                    walls.push_back(tmp);
                }
                if(i != INT(stacks - 1)){
                    Triangle tmp(Points[k2 + 1],Points[k2],Points[k1 + 1],image,
                            Texture[k2 + 1] * Vector2(image->width(), image->height()),
                            Texture[k2] * Vector2(image->width(), image->height()),
                            Texture[k1 + 1] * Vector2(image->width(), image->height()));
                    tmp.setNormal(Normal[k2 + 1],Normal[k2],Normal[k1 + 1]);
                    walls.push_back(tmp);
                }
            }
        }
    }
    void rotateOX(double value) { for(int i = 0; i < walls.size(); i++) walls[i].rotateOX(value); }
    void rotateOY(double value) { for(int i = 0; i < walls.size(); i++) walls[i].rotateOY(value); }
    void rotateOZ(double value) { for(int i = 0; i < walls.size(); i++) walls[i].rotateOZ(value); }
    void scaleOX(double value) { for(int i = 0; i < walls.size(); i++) walls[i].scaleOX(value); }
    void scaleOY(double value) { for(int i = 0; i < walls.size(); i++) walls[i].scaleOY(value); }
    void scaleOZ(double value) { for(int i = 0; i < walls.size(); i++) walls[i].scaleOZ(value); }
    void move(Vector3 value) { center = center + value; }
    void render(QImage* img, double** Zbufor, Light light);
    ~Sphere() {}
};
void Sphere::render(QImage* img, double** Zbufor, Light light){
    for(int i = 0; i < walls.size(); i++){
        Triangle tmp = walls[i] + center;
        tmp.setNormal(walls[i].Na, walls[i].Nb, walls[i].Nc);
        tmp.render(img,Zbufor,light);
    }
}
struct Scene{
    double** Zbufor;
    Color background;
    QImage *image = nullptr;
    QVector <Object*> objects;
    Light light;
    Scene(Color background = Color(), Light light = Light(widz)) : background(background), light(light) {
        Zbufor = new double*[ULL(HEIGHT)];
        for(int i = 0; i < HEIGHT; i++){
            Zbufor[i] = new double[ULL(WIDTH)];
            for(int j = 0; j < WIDTH; j++){
                Zbufor[i][j] = -DOUBLE(INFINITY);
            }
        }
    }
    Scene(QImage* image, Light light = Light(widz)) : image(image), light(light) {
        Zbufor = new double*[ULL(HEIGHT)];
        for(int i = 0; i < HEIGHT; i++){
            Zbufor[i] = new double[ULL(WIDTH)];
            for(int j = 0; j < WIDTH; j++){
                Zbufor[i][j] = -DOUBLE(INFINITY);
            }
        }
    }
    void addObject(Object* item) { objects.push_back(item); }
    QImage* render(){
        QImage *img = new QImage(WIDTH,HEIGHT,QImage::Format_RGB32);
        int i,j;
        if(image == nullptr)
            for(i = 0; i < HEIGHT; i++){
                for(j = 0; j < WIDTH; j++){
                    setPixel(i,j,background,img->bits());
                }
            }
        else {
            *img = image->copy();
        }

        for(i = 0; i < objects.size(); i++){
            objects[i]->render(img,Zbufor,light);
        }
        return img;
    }
};


MyWindow::MyWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();
    img = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
    wykonaj();
}
MyWindow::~MyWindow()
{
    delete ui;
}
void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}
void MyWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}
void MyWindow::rysujPunkty(int x, int y, int r, int g, int b){
    int i,j;
    for(i = x - 2; i <= x + 2; i++){
        for(j = y - 2; j <= y + 2; j++){
            rysujPiksel(i,j,r,g,b);
        }
    }
}
void MyWindow::rysujPiksel(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = static_cast<unsigned char>(b);
        ptr[szer * 4 * y + 4 * x + 1] = static_cast<unsigned char>(g);
        ptr[szer * 4 * y + 4 * x + 2] = static_cast<unsigned char>(r);
    }
}

void MyWindow::wykonaj(){
    /*czysc();
    reset();
    Scalowanie();
    Przesuniecie();
    ObrotOX();
    ObrotOY();
    ObrotOZ();
    PochylenieOX();
    PochylenieOY();
    PochylenieOZ();
    for(int i = 0; i < 4; i++){
        wynik[i][i] = 1;
    }
    Mnozenie(MacierzObrotOX);
    Mnozenie(MacierzObrotOY);
    Mnozenie(MacierzObrotOZ);
    Mnozenie(MacierzPochylenieOX);
    Mnozenie(MacierzPochylenieOY);
    Mnozenie(MacierzPochylenieOZ);
    Mnozenie(MacierzSkal);
    Mnozenie(MacierzPrzesun);
    Rysowanie();*/
    //Scene obraz(Color(0.5,0.5,1),Light(Vector3(swiatloOX,swiatloOY,swiatloOZ), Color(R,G,B)));
    /*Cube* kostka = new Cube(Vector3(0,0,0),100,100,100,
                            Color(0.7,0.3,0.5),Color(1,0.8,0.5),Color(0.1,0.7,0.6),Color(0.37,0.0,0.712),Color(0.45,0.93,0.29),Color(0.04,0.01,0.94));
    kostka->rotateOZ(obrotOZ);
    kostka->rotateOX(obrotOX);
    kostka->rotateOY(obrotOY);
    kostka->move(Vector3(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
    kostka->scaleOX(skalowanieOX);
    kostka->scaleOY(skalowanieOY);
    kostka->scaleOZ(skalowanieOZ);
    Cube* kostka2 = new Cube(Vector3(0,0,0),100,100,100,Color(0.6));
    kostka2->rotateOZ(-obrotOZ);
    kostka2->rotateOX(-obrotOX);
    kostka2->rotateOY(-obrotOY);
    Cube* kostka3 = new Cube(Vector3(0,0,0),100,100,100,Color(0.4,0.15,0.87));
    kostka3->rotateOZ(obrotOZ);
    kostka3->rotateOX(obrotOX);
    kostka3->rotateOY(obrotOY);
    kostka3->move(Vector3(-przesuniecieOX,-przesuniecieOY,-przesuniecieOZ));
    kostka3->scaleOX(skalowanieOX);
    kostka3->scaleOY(skalowanieOY);
    kostka3->scaleOZ(skalowanieOZ);*/
    //obraz.addObject(kostka);
    //obraz.addObject(kostka2);
    //obraz.addObject(kostka3);
    //Ball* ziemia = new Ball(Vector3(0,0,0), 100, Color(0.5,0.7,0.3));
    /*Ball* ziemia = new Ball(Vector3(0,0,0), 100,
                            new QImage(":/FrontUpLeft.png"), new QImage(":/FrontUpRight.png"),
                            new QImage(":/FrontDownLeft.png"), new QImage(":/FrontDownRight.png"),
                            new QImage(":/BackUpRight.png"), new QImage(":/BackUpLeft.png"),
                            new QImage(":/BackDownRight.png"), new QImage(":/BackDownLeft.png"));*/
    /*Ball* ziemia = new Ball(Vector3(0,0,0), 100,
                            new QImage(":/logoUp.png"), new QImage(":/logoUp.png"),
                            new QImage(":/logoDown.png"), new QImage(":/logoDown.png"),
                            new QImage(":/logoUp.png"), new QImage(":/logoUp.png"),
                            new QImage(":/logoDown.png"), new QImage(":/logoDown.png"));
    ziemia->division(divi);*/
    //Sphere* ziemia = new Sphere(Vector3(0,0,0), 100, 3, 3, Color(0.3,0.8,0.4));
    Scene obraz(new QImage(":/tlo.jpg"),Light(Vector3(swiatloOX,swiatloOY,swiatloOZ), Color(R,G,B)));
    Sphere* ziemia = new Sphere(Vector3(0,0,0), 100, rowniki, poludniki, new QImage(":/ziemia.jpg"));

    ziemia->rotateOZ(obrotOZ);
    ziemia->rotateOX(obrotOX);
    ziemia->rotateOY(obrotOY);
    ziemia->move(Vector3(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
    ziemia->scaleOX(skalowanieOX);
    ziemia->scaleOY(skalowanieOY);
    ziemia->scaleOZ(skalowanieOZ);
    obraz.addObject(ziemia);

    img = obraz.render();
    update();
}

void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    przesuniecieOX = value - 250;
    wykonaj();
}

void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    przesuniecieOY = value - 250;
    wykonaj();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    przesuniecieOZ = value - 250;
    wykonaj();
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    skalowanieOX = value / 250.0;
    wykonaj();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    skalowanieOY = value / 250.0;
    wykonaj();
}

void MyWindow::on_horizontalSlider_6_valueChanged(int value)
{
    skalowanieOZ = value / 250.0;
    wykonaj();
}

void MyWindow::on_dial_valueChanged(int value)
{
    obrotOX = value;
    wykonaj();
}

void MyWindow::on_dial_2_valueChanged(int value)
{
    obrotOY = value;
    wykonaj();
}

void MyWindow::on_dial_3_valueChanged(int value)
{
    obrotOZ = value;
    wykonaj();
}


void MyWindow::on_pushButton_clicked()
{
    przesuniecieOX = 0;
    przesuniecieOY = 0;
    przesuniecieOZ = 0;
    skalowanieOX = 1;
    skalowanieOY = 1;
    skalowanieOZ = 1;
    obrotOX = 0;
    obrotOY = 0;
    obrotOZ = 0;
    ui->horizontalSlider->setValue(250);
    ui->horizontalSlider_2->setValue(250);
    ui->horizontalSlider_3->setValue(250);
    ui->horizontalSlider_4->setValue(250);
    ui->horizontalSlider_5->setValue(250);
    ui->horizontalSlider_6->setValue(250);
    ui->horizontalScrollBar->setValue(18);
    ui->horizontalScrollBar_2->setValue(36);
    ui->dial->setValue(0);
    ui->dial_2->setValue(0);
    ui->dial_3->setValue(0);
    wykonaj();
}

void MyWindow::on_horizontalSlider_16_valueChanged(int value)
{
    swiatloOX = value - 500;
    wykonaj();
}

void MyWindow::on_horizontalSlider_17_valueChanged(int value)
{
    swiatloOY = value - 500;
    wykonaj();
}

void MyWindow::on_horizontalSlider_18_valueChanged(int value)
{
    swiatloOZ = value - 500;
    wykonaj();
}

void MyWindow::on_horizontalSlider_13_valueChanged(int value)
{
    R = value/255.0;
    wykonaj();
}

void MyWindow::on_horizontalSlider_14_valueChanged(int value)
{
    G = value/255.0;
    wykonaj();
}

void MyWindow::on_horizontalSlider_15_valueChanged(int value)
{
    B = value/255.0;
    wykonaj();
}

void MyWindow::on_pushButton_3_clicked()
{
    swiatloOX = 0;
    swiatloOY = 0;
    swiatloOZ = 500;
    R = G = B = 0.5;
    ui->horizontalSlider_16->setValue(500);
    ui->horizontalSlider_17->setValue(500);
    ui->horizontalSlider_18->setValue(1000);
    ui->horizontalSlider_13->setValue(127);
    ui->horizontalSlider_14->setValue(127);
    ui->horizontalSlider_15->setValue(127);
    wykonaj();
}

void MyWindow::on_horizontalScrollBar_valueChanged(int value)
{
    rowniki = value;
    wykonaj();
}

void MyWindow::on_horizontalScrollBar_2_valueChanged(int value)
{
    poludniki = value;
    wykonaj();
}
