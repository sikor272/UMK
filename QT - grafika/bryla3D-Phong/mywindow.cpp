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
    // Zakres [0,1]
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
    int x,y;
    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}
    Vector2 operator + (const Vector2& v) const { return Vector2(x+v.x, y+v.y); }
    Vector2 operator += (const Vector2& v) const { return Vector2(x+v.x, y+v.y); }
    Vector2 operator - (const Vector2& v) const { return Vector2(x-v.x, y-v.y); }
    Vector2 operator -= (const Vector2& v) const { return Vector2(x-v.x, y-v.y); }
    Vector2 operator * (int d) const { return Vector2(x*d, y*d); }
    Vector2 operator *= (int d) const { return Vector2(x*d, y*d); }
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
    void rotateOX(double value) { A.rotateOX(value); B.rotateOX(value); C.rotateOX(value); }
    void rotateOY(double value) { A.rotateOY(value); B.rotateOY(value); C.rotateOY(value); }
    void rotateOZ(double value) { A.rotateOZ(value); B.rotateOZ(value); C.rotateOZ(value); }
    void scaleOX(double value) { A.scaleOX(value); B.scaleOX(value); C.scaleOX(value); }
    void scaleOY(double value) { A.scaleOY(value); B.scaleOY(value); C.scaleOY(value); }
    void scaleOZ(double value) { A.scaleOZ(value); B.scaleOZ(value); C.scaleOZ(value); }
    bool visible(Vector3 visitor) { return (scalar(getNormal(), B - visitor) < 0); }
    void render(QImage* img, double** Zbufor, Light light){
        if(visible(widz)){
            Zbufor[0][0] = 0;
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
            tab = triangleValue(tab, pozA.x + 250, -pozA.y + 250, pozB.x + 250, -pozB.y + 250,
                                Na, Nb, Ia, Ib, A, B, Pa, Pb);
            tab = triangleValue(tab, pozA.x + 250, -pozA.y + 250, pozC.x + 250, -pozC.y + 250,
                                Na, Nc, Ia, Ib, A, C, Pa, Pb);
            tab = triangleValue(tab, pozC.x + 250, -pozC.y + 250, pozB.x + 250, -pozB.y + 250,
                                Nc, Nb, Ia, Ib, C, B, Pa, Pb);
            Vector3 R, V, N, L;
            Vector3 I_a, I_b, P_a, P_b, Pozycja;
            for(j = max(0,min3(250 -pozA.y, 250 -pozB.y, 250 -pozC.y)); j <= min(HEIGHT - 1,max3(250 -pozA.y,250 -pozB.y,250 -pozC.y)); j++){
                I_a = Ia[j]; I_b = Ib[j];
                P_a = Pa[j]; P_b = Pb[j];
                for(i = max(0,tab[j][0]); i <= min(WIDTH-1,tab[j][1]); i++){
                    N = I_a; Pozycja = P_a;
                    if(tab[j][0] != tab[j][1]){
                        N = I_b - ((I_b - I_a) * DOUBLE(tab[j][1] - i) / DOUBLE(tab[j][1] - tab[j][0]));
                        Pozycja = P_b - ((P_b - P_a) * DOUBLE(tab[j][1] - i) / DOUBLE(tab[j][1] - tab[j][0]));
                    }
                    L = light.position - Pozycja;
                    R = N.normalize() * scalar(N.normalize(),L.normalize()) * 2.0 - L.normalize(); // reflect
                    V = widz - Pozycja; // odcjac aktualny punkt z plaszczyzny
                    L = L.normalize();
                    N = N.normalize();
                    R = R.normalize();
                    V = V.normalize();
                    double ambient = 0.25;
                    double diffuse = max(0.0,scalar(N,L));
                    double specular = pow(max(0.0,scalar(R,V)),25);
                    //qDebug() << diffuse << specular;
                    setPixel(i,j,fill * (Color(diffuse + specular) * light.saturation + ambient),img->bits());

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

struct Scene{
    double** Zbufor;
    Color background;
    QVector <Object*> objects;
    Light light;
    Scene(Color background = Color(), Light light = Light(widz)) : background(background), light(light) {
        Zbufor = new double*[ULL(HEIGHT)];
        for(int i = 0; i < HEIGHT; i++){
            Zbufor[i] = new double[ULL(WIDTH)];
            for(int j = 0; j < WIDTH; j++){
                Zbufor[i][j] = DOUBLE(INFINITY);
            }
        }
    }
    void addObject(Object* item) { objects.push_back(item); }
    QImage* render(){
        QImage *img = new QImage(WIDTH,HEIGHT,QImage::Format_RGB32);
        int i,j;
        for(i = 0; i < HEIGHT; i++){
            for(j = 0; j < WIDTH; j++){
                setPixel(i,j,background,img->bits());
            }
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
    Scene obraz(Color(0.5,0.5,1),Light(Vector3(swiatloOX,swiatloOY,swiatloOZ), Color(R,G,B)));
    Cube* kostka = new Cube(Vector3(0,0,0),100,100,100,
                            Color(0.7,0.3,0.5),Color(1,0.8,0.5),Color(0.1,0.7,0.6),Color(0.37,0.0,0.712),Color(0.45,0.93,0.29),Color(0.04,0.01,0.94));
    kostka->rotateOZ(obrotOZ);
    kostka->rotateOX(obrotOX);
    kostka->rotateOY(obrotOY);
    kostka->move(Vector3(przesuniecieOX,przesuniecieOY,przesuniecieOZ));
    kostka->scaleOX(skalowanieOX);
    kostka->scaleOY(skalowanieOY);
    kostka->scaleOZ(skalowanieOZ);
    obraz.addObject(kostka);
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
