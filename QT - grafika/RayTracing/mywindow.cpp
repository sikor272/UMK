#include "mywindow.h"
#include "ui_mywindow.h"
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <random>
#include <iostream>
#include <QTime>
using namespace std;
#define DOUBLE(x) (static_cast<double>(x))
#define INT(x) (static_cast<int>(x))
#define ULL(x) (static_cast<unsigned long long>(x))
#define UCHAR(x) (static_cast<unsigned char>(x))
struct Object;
struct Scene;
struct RayTracing;
inline double nextRand(){
    return  DOUBLE(rand()) / DOUBLE(RAND_MAX);
}
struct Color{
    double r, g, b;
    Color(double value = 0.0) : r(value), g(value), b(value) {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}
    Color operator  +  (Color add) { return Color(r + add.r, g + add.g, b + add.b); }
    Color operator  += (Color add) { return Color(r + add.r, g + add.g, b + add.b); }
    Color operator  *  (Color add) { return Color(r * add.r, g * add.g, b * add.b); }
    Color operator  *= (Color add) { return Color(r * add.r, g * add.g, b * add.b); }
    Color operator  *  (double add) { return Color(r * add, g * add, b * add); }
    Color operator  *= (double add) { return Color(r * add, g * add, b * add); }
    Color operator  /  (double add) { return Color(r / add, g / add, b / add); }
    Color operator  /= (double add) { return Color(r / add, g / add, b / add); }
    Color repair() { return Color(min(1.0, max(0.0 , r)), min(1.0, max(0.0 , g)), min(1.0, max(0.0 , b))); }
    double R() { return r * 255; }
    double G() { return g * 255; }
    double B() { return b * 255; }
};

struct Vector2{
    double x,y;
    Vector2(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    Vector2 operator + (const Vector2& add) const { return Vector2(x + add.x, y + add.y); }
    Vector2 operator += (const Vector2& add) const { return Vector2(x + add.x, y + add.y); }
    Vector2 operator - (const Vector2& add) const { return Vector2(x - add.x, y - add.y); }
    Vector2 operator -= (const Vector2& add) const { return Vector2(x - add.x, y - add.y); }
    Vector2 operator * (double add) const { return Vector2(x * add, y * add); }
    Vector2 operator *= (double add) const { return Vector2(x * add, y * add); }
    Vector2 operator / (double add) const { return Vector2(x / add, y / add); }
    Vector2 operator /= (double add) const { return Vector2(x / add, y / add); }
};
struct Vector3{
    double x,y,z;
    Vector3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
    Vector3 operator + (const Vector3& add) const { return Vector3(x + add.x, y + add.y, z + add.z); }
    Vector3 operator += (const Vector3& add) const { return Vector3(x + add.x, y + add.y, z + add.z); }
    Vector3 operator - (const Vector3& add) const { return Vector3(x - add.x, y - add.y, z - add.z); }
    Vector3 operator -= (const Vector3& add) const { return Vector3(x - add.x, y - add.y, z - add.z); }
    Vector3 operator - () const { return Vector3(-x, -y, -z); }
    Vector3 operator * (double add) const { return Vector3(x * add, y * add, z * add); }
    Vector3 operator *= (double add) const { return Vector3(x * add, y * add, z * add); }
    Vector3 operator / (double add) const { return Vector3(x / add, y / add, z / add); }
    Vector3 operator /= (double add) const { return Vector3(x / add, y / add, z / add); }
    Vector3 normalize() const { double lg = lenght(); return Vector3(x / lg, y / lg, z / lg); }
    bool operator == (const Vector3& add) const { return x - add.x == 0.0 && y - add.y == 0.0 && z - add.z == 0.0; }
    double lenght() const { return sqrt(x*x + y*y + z*z); }
    double powLength() const { return (x*x+y*y+z*z); }
    Vector3 cross(Vector3 add) { return Vector3((y * add.z) - (z * add.y), (z * add.x) - (x * add.z), (x * add.y) - (y * add.x)); }
    double dot(Vector3 add) { return x * add.x + y * add.y + z * add.z; }
};
inline Vector3 Reflect(Vector3 vec, Vector3 normal) { return normal * normal.dot(vec) * 2 - vec; }


struct Ray{
    double Epsilon = 0.0001, Huge = DOUBLE(INFINITY);
    Vector3 origin, direction;
    Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction.normalize()) {}
};
struct HitInfo{
    int Depth = 0;
    Object* hitObjects = nullptr;
    Scene* scene;
    Vector3 normal;
    Vector3 hitPoint;
    Ray ray = Ray(Vector3(),Vector3());
};
/* Sampling i Antyaliasing */
struct InterfaceSampleGenerator {
    virtual Vector2* Sample(int count) = 0;
    virtual ~InterfaceSampleGenerator();
};
InterfaceSampleGenerator::~InterfaceSampleGenerator() {}
struct InterfaceSampleDistrib {
    virtual Vector2 MapSample(Vector2 sample) = 0;
    virtual ~InterfaceSampleDistrib();
};
InterfaceSampleDistrib::~InterfaceSampleDistrib() {}
struct PureRandom : public InterfaceSampleGenerator {
    Vector2* Sample(int count);
};
Vector2* PureRandom::Sample(int count){
    Vector2 *sample = new Vector2[ULL(count)];
    for(int i = 0; i < count; i++){
        sample[i] = Vector2(nextRand(), nextRand());
    }
    return sample;
}
struct Regular : public InterfaceSampleGenerator {
    Vector2* Sample(int count);
};
Vector2* Regular::Sample(int count){
    int sampleCount = INT(sqrt(count));
    Vector2 *sample = new Vector2[ULL(sampleCount * sampleCount)];
    for(int x = 0; x < sampleCount; x++){
        for(int y = 0; y < sampleCount; y++){
            sample[x * sampleCount + y] = Vector2(DOUBLE(x + 0.5) / DOUBLE(sampleCount), DOUBLE(y + 0.5) / DOUBLE(sampleCount));
        }
    }
    return sample;
}
struct Jittered : public InterfaceSampleGenerator {
    Vector2* Sample(int count);
};
Vector2* Jittered::Sample(int count){
    int sampleCount = INT(sqrt(count));
    Vector2 *sample = new Vector2[ULL(sampleCount * sampleCount)];
    for(int x = 0; x < sampleCount; x++){
        for(int y = 0; y < sampleCount; y++){
            sample[x * sampleCount + y] = Vector2(DOUBLE(x + nextRand()) / DOUBLE(sampleCount), DOUBLE(y + nextRand()) / DOUBLE(sampleCount));
        }
    }
    return sample;
}
struct NRooks : public InterfaceSampleGenerator {
    Vector2* Sample(int count);
    void ShuffleX(Vector2* samples, int count)
    {
        for (int i = 0; i < count - 1; i++)
            swap(samples[i].x, samples[rand() % count].x);
    }

};
Vector2* NRooks::Sample(int count){
    Vector2 *sample = new Vector2[ULL(count)];
    for(int i = 0; i < count; i++){
        sample[i] = Vector2(i + nextRand(), i + nextRand());
    }
    ShuffleX(sample, count);
    return sample;
}
struct SquareDistrib : public InterfaceSampleDistrib {
    Vector2 MapSample(Vector2 sample);
};
Vector2 SquareDistrib::MapSample(Vector2 sample){
    return sample;
}
struct Sampler {
    QVector <Vector2*> sets;
    int sampleNdx = 0;
    int setNdx = 0;
    int sampleCount;
    int count;
    Sampler(InterfaceSampleGenerator* sampler, InterfaceSampleDistrib* mapper, int sampleCount, int count) {
        this->sampleCount = sampleCount;
        this->count = count;
        for(int i = 0; i < count; i++){
            Vector2* sample = sampler->Sample(sampleCount);
            Vector2* listSample = new Vector2[ULL(sampleCount)];
            for(int j = 0; j < sampleCount; j++){
                listSample[j] = mapper->MapSample(sample[j]);
            }
            sets.append(listSample);
        }
    }
    Vector2 Single(){
        Vector2 sample = sets[setNdx][sampleNdx];
        sampleNdx++;
        if(sampleNdx >= sampleCount){
            sampleNdx = 0;
            setNdx = rand() % count;
        }
        return sample;
    }
};
struct DiskDistrib : public InterfaceSampleDistrib {
    Vector2 MapSample(Vector2 sample);
};
Vector2 DiskDistrib::MapSample(Vector2 sample){
    sample.x = sample.x * 2 - 1;
    sample.y = sample.y * 2 - 1;
    double r;
    double phi;
    if (sample.x > -sample.y)
        if (sample.x > sample.y) {
            r = sample.x;
            phi = sample.y / sample.x;
        } else {
            r = sample.y;
            phi = 2 - sample.x / sample.y;
        }
    else
        if (sample.x < sample.y) {
            r = -sample.x;
            phi = 4 + sample.y / sample.x;
        } else {
            r = -sample.y;
            phi = 6 - sample.x / sample.y;
        }
    if (sample.x == 0.0 && sample.y == 0.0) phi = 0;
    phi *= M_PI_4;
    return Vector2(r * cos(phi), r * sin(phi));
}
/* KAMERA */
struct InterfaceCamera{
    virtual Ray getRayTo(Vector2 view) = 0;
    virtual ~InterfaceCamera();
};
InterfaceCamera::~InterfaceCamera() {}
// Wprost
struct Orthogonal :public InterfaceCamera {
    Vector3 eyePosition;
    double angel;
    Vector2 cameraSize;
    Orthogonal(Vector3 eyePosition, double angel, Vector2 cameraSize) : eyePosition(eyePosition), angel(angel), cameraSize(cameraSize) {}
    Ray getRayTo(Vector2 view);
};
Ray Orthogonal::getRayTo(Vector2 view){
    Vector3 direction = Vector3(sin(angel),0,cos(angel)).normalize();
    Vector2 cameraLook(view.x * cameraSize.x, view.y * cameraSize.y);
    Vector3 camera(eyePosition.x + cameraLook.x * cos(angel),
                   eyePosition.y + cameraLook.y,
                   eyePosition.z + cameraLook.x * sin(angel));
    return Ray(camera, direction);
}

struct OrthonormalBasis
{
    Vector3 u, v, w;
    OrthonormalBasis(Vector3 origin, Vector3 lookAt, Vector3 up) {
        w = (origin - lookAt).normalize();
        u = (up.cross(w)).normalize();
        v = w.cross(u);
    }
    OrthonormalBasis(Vector3 front, Vector3 up) {
        w = front.normalize();
        u = (up.cross(w)).normalize();
        v = w.cross(u);
    }
};
inline Vector3 operator * (OrthonormalBasis onb, Vector3 add)
{
    return (onb.u * add.x + onb.v * add.y + onb.w * add.z);
}
// Perspektywa
struct Pinhole :public InterfaceCamera {
    OrthonormalBasis onb;
    Vector3 origin;
    Vector2 scale;
    double distance;
    Pinhole(Vector3 origin, Vector3 lookAt, Vector3 up, Vector2 scale, double distance) : onb(OrthonormalBasis(origin - lookAt, up)),
        origin(origin), scale(scale), distance(distance) {}
    Ray getRayTo(Vector2 view);
    Vector3 RayDirection(Vector2 view) {
        return onb * Vector3(view.x, view.y, -distance);
    }
};
Ray Pinhole::getRayTo(Vector2 view){
    Vector2 newView(view.x * scale.x, view.y * scale.y);
    return Ray(origin, RayDirection(newView));
}
// Soczewka
struct ThinLens : public InterfaceCamera {
    OrthonormalBasis onb;
    Vector3 origin;
    Vector2 scale;
    double distance;
    Sampler* distrib;
    double radius;
    double focal;
    ThinLens(Vector3 origin, Vector3 lookAt, Vector3 up, Vector2 scale, double distance, Sampler* distrib, double radius, double focal) :
        onb(OrthonormalBasis(origin - lookAt, up)),origin(origin), scale(scale), distance(distance), distrib(distrib), radius(radius), focal(focal) {}
    Vector3 RayDirection(Vector2 view, Vector2 lens) {
        Vector2 point = view * focal / distance;
        return onb * Vector3(point.x - lens.x, point.y - lens.y, -focal);
    }
    Ray getRayTo(Vector2 view);
};
Ray ThinLens::getRayTo(Vector2 view){
    Vector2 newView(view.x * scale.x, view.y * scale.y);
    Vector2 lensPoint = distrib->Single() * radius;
    Vector3 rayOrigin = origin + onb * Vector3(lensPoint.x, lensPoint.y, 0);
    return Ray(rayOrigin, RayDirection(newView, lensPoint));
}


/* SWIATLO */
struct PointLight{
    Vector3 position;
    Color color;
    PointLight(Vector3 position, Color color) : position(position), color(color) {}
};
struct Light {
    Vector3 center;
    double radius;
    Sampler* sampler;
    Color color;
    Light(Vector3 center, Color color) : center(center), radius(0), sampler(nullptr), color(color) {}
    Light(Vector3 center, Color color, Sampler* sampler, double radius) : center(center), radius(radius), sampler(sampler), color(color) {}
    Vector3 sample(){
        if(radius == 0.0) return center;
        return center + sampleUnitSphere(sampler->Single()) * radius;
    }
    Vector3 sampleUnitSphere(Vector2 sample){
        double z = 2 * sample.x - 1;
        double t = 2 * M_PI * sample.y;
        double r = sqrt(1 - z * z);
        return Vector3(r * cos(t), r * sin(t), z);
    }
};

struct InterfaceMaterial{
    virtual Color Shade(RayTracing* tracer, HitInfo hit) = 0;
    virtual ~InterfaceMaterial();
};
InterfaceMaterial::~InterfaceMaterial() {}

/* OBJEKTY 3D */
struct Object{
    InterfaceMaterial* material;
    Object() {}
    Object(InterfaceMaterial* material) : material(material) {}
    virtual bool HitTest(Ray ray, double *minDistance, Vector3 *normal) = 0;
    virtual ~Object();
};
Object::~Object() {}
// Sfera
struct Sphere : public Object {
    Vector3 center;
    double r;
    Sphere(Vector3 center, double r, InterfaceMaterial* material) : Object(material), center(center), r(r) {}
    bool HitTest(Ray ray, double *minDistance, Vector3 *normal);
};
bool Sphere::HitTest(Ray ray, double *minDistance, Vector3 *outNormal){
    Vector3 distance = ray.origin - center;
    double a = ray.direction.powLength();
    double b = (distance * 2).dot(ray.direction);
    double c = distance.powLength() - r * r;
    double delta = b * b - 4 * a * c;
    if(delta < 0) return false;
    double t = (-b - sqrt(delta)) / (2 * a);
    if(t < ray.Epsilon) t = (-b + sqrt(delta)) / (2 * a);
    if(t < ray.Epsilon) return false;
    *minDistance = t;
    Vector3 hitPoint = ray.origin + ray.direction * t;
    *outNormal = (hitPoint - center).normalize();
    return true;
}
// Plaszczyzna
struct Plane : public Object {
    Vector3 point, normal;
    Plane(Vector3 point, Vector3 normal, InterfaceMaterial* material) : Object(material), point(point), normal(normal){}
    bool HitTest(Ray ray, double *minDistance, Vector3 *normal);
};
bool Plane::HitTest(Ray ray, double *minDistance, Vector3 *outNormal){
    double t = (point - ray.origin).dot(normal) / ray.direction.dot(normal);
    if(t > ray.Epsilon){
        *minDistance = t;
        *outNormal = this->normal;
        return true;
    }
    return false;
}

struct Scene{
    Color background;
    QVector <Object*> Objects;
    QVector <Light*> Lights;
    Scene(Color background) : background(background) {}
    void addObject(Object* object) { Objects.push_back(object); }
    void addLight(Light* light) { Lights.push_back(light); }
    HitInfo traceRay(Ray ray){
        HitInfo result;
        result.hitObjects = nullptr;
        Vector3 normal;
        double minDistance = DOUBLE(INFINITY);
        double lastHit = 0;
        for(int i = 0; i < Objects.size(); i++){
            if(Objects[i]->HitTest(ray, &lastHit, &normal) && lastHit < minDistance){
                minDistance = lastHit;
                result.hitObjects = Objects[i];
                result.normal = normal;
            }
        }
        if(result.hitObjects != nullptr){
            result.hitPoint = ray.origin + ray.direction * minDistance;
            result.ray = ray;
            result.scene = this;
        }
        return result;
    }
    bool anyObject(Vector3 A, Vector3 B){
        Vector3 AB = B - A;
        double dist = AB.lenght();
        double actual = DOUBLE(INFINITY);
        Ray ray(A, AB);
        Vector3 ignore;
        for(int i = 0; i < Objects.size(); i++){
            if(Objects[i]->HitTest(ray, &actual, &ignore) && actual < dist){
                return true;
            }
        }
        return false;
    }
};
// Rozpraszanie
struct PerfectDiffuse : public InterfaceMaterial{
    Color material;
    PerfectDiffuse(Color color) : material(color) {}
    Color Shade(RayTracing* tracer, HitInfo hit);
};
Color PerfectDiffuse::Shade(RayTracing* tracer, HitInfo hit){
    Color total;
    for(int i = 0; i < hit.scene->Lights.size(); i++){
        Vector3 lightPosition = hit.scene->Lights[i]->sample();
        Vector3 inDirection = (lightPosition - hit.hitPoint).normalize();
        double diffuseFactor = inDirection.dot(hit.normal);
        if(diffuseFactor < 0) continue;
        if(hit.scene->anyObject(hit.hitPoint, lightPosition))
            continue;
        total =  total + hit.scene->Lights[i]->color * material * diffuseFactor;
    }
    return total;

}
// Phong
struct Phong : public InterfaceMaterial{
    Color material;
    double diffuse;
    double specular;
    double specularExp;
    Phong(Color material,double diffuse, double specular, double specularExp) :
        material(material), diffuse(diffuse), specular(specular), specularExp(specularExp) {}
    Color Shade(RayTracing* tracer, HitInfo hit);
    double phongFactor(Vector3 inDirect, Vector3 normal, Vector3 toCamera){
        Vector3 reflect = Reflect(inDirect, normal);
        double angle = reflect.dot(toCamera);
        if(angle <= 0) return 0;
        return pow(angle, specularExp);
    }
};
Color Phong::Shade(RayTracing* tracer, HitInfo hit){
    Color total;
    for(int i = 0; i < hit.scene->Lights.size(); i++){
        Vector3 lightPosition = hit.scene->Lights[i]->sample();
        Vector3 inDirection = (lightPosition - hit.hitPoint).normalize();
        double diffuseFactor = inDirection.dot(hit.normal);
        if(diffuseFactor < 0) continue;
        if(hit.scene->anyObject(hit.hitPoint, lightPosition))
            continue;
        Color result = hit.scene->Lights[i]->color * material * diffuseFactor * diffuse;
        double Phong = phongFactor(inDirection, hit.normal, -hit.ray.direction);
        if(Phong != 0.0) result = result + material * specular * Phong;
        total =  total + result;
    }
    return total;
}
// Odbicie
struct Reflective : public InterfaceMaterial{
    Phong direct;
    double reflect;
    Color material;
    Reflective(Color material,double diffuse, double specular, double specularExp, double reflect) : direct(material, diffuse, specular, specularExp),
        reflect(reflect), material(material) {}
    Color Shade(RayTracing* tracer, HitInfo hit);
};
struct RayTracing{
    int maxDepth;
    RayTracing(int maxDepth) : maxDepth(maxDepth) {}
    QImage* rayTrace(QImage* img,int H, int W, Scene* scene, InterfaceCamera* camera){
        Sampler* sampler = new Sampler(new Regular(), new SquareDistrib(), 1, 1);
        return rayTrace(img, H, W, scene, camera, sampler);
    }
    QImage* rayTrace(QImage* img,int H, int W, Scene* scene, InterfaceCamera* camera, Sampler* sampler){
        int i, j, k;
        unsigned char *ptr;
        for(j = 0; j < H; j++){
            ptr = img->scanLine(j);
            for(i = 0; i < W; i++){
                Color color;
                for(k = 0; k < sampler->sampleCount; k++){
                    Vector2 sample = sampler->Single();
                    Vector2 view(DOUBLE(i + sample.x) / W * 2 - 1, DOUBLE(j + sample.y) / W * 2 - 1);
                    Ray ray = camera->getRayTo(view);
                    color = color + ShadeRay(scene, ray, 0) / DOUBLE(sampler->sampleCount);
                }
                ptr[4 * i] = UCHAR(color.B());
                ptr[4 * i + 1] = UCHAR(color.G());
                ptr[4 * i + 2] = UCHAR(color.R());
            }
        }
        return img;
    }
    Color ShadeRay(Scene* scene, Ray ray, int currDepth){
        if(currDepth > maxDepth) return Color();
        HitInfo info = scene->traceRay(ray);
        info.Depth = currDepth + 1;
        if(info.hitObjects == nullptr) return scene->background;
        InterfaceMaterial* material = info.hitObjects->material;
        return (material->Shade(this, info)).repair();
    }
};
Color Reflective::Shade(RayTracing* tracer, HitInfo hit){
    Vector3 toCamera = -hit.ray.direction;
    Color radiance = direct.Shade(tracer, hit);
    Vector3 reflectDir = Reflect(toCamera, hit.normal);
    Ray ray(hit.hitPoint, reflectDir);
    radiance = radiance + tracer->ShadeRay(hit.scene, ray, hit.Depth) * material * reflect;
    return radiance;
}
/* Przezroczystosc */
struct Transparent : public InterfaceMaterial {
    Phong direct;
    double refract, reflect, transmiss, specular;
    Color color;
    Transparent(Color color, double diffuse, double specular, double exp, double reflect, double refract,
                double transmiss) : direct(Phong(color, diffuse, specular, exp)),
        refract(refract), reflect(reflect), transmiss(transmiss), specular(specular), color(color) {}
    Color Shade(RayTracing* tracer, HitInfo hit);
    double findRefraction(double eta, double cosAngle){
        return 1 - (1 - cosAngle * cosAngle) / (eta * eta);
    }
    bool isTotalReflect(double refraction){
        return refraction < 0.0 ;
    }
    Ray reflex(Vector3 hitPoint, Vector3 toCamera, Vector3 normal,
               double eta, double cosTransmitted, double cosIncident) {
        if(cosIncident < 0){
            normal = -normal;
            cosIncident = -cosIncident;
        }
        Vector3 direction = -toCamera / eta - normal * (cosTransmitted  - cosIncident / eta);
        return Ray(hitPoint, direction);
    }
    Color computeColor(double eta){
        return Color(transmiss) / (eta * eta);
    }
};
Color Transparent::Shade(RayTracing *tracer, HitInfo hit){
    Color final = direct.Shade(tracer, hit);
    Vector3 toCamera = -hit.ray.direction;
    double cosAngle = hit.normal.dot(toCamera);
    double tmp = cosAngle > 0 ? refract : 1 / refract;
    double refraction = findRefraction(tmp, cosAngle);
    Ray rayreflect(hit.hitPoint, Reflect(toCamera, hit.normal));
    Color colorreflect = color * reflect;
    if(isTotalReflect(refraction)){
        final = final + tracer->ShadeRay(hit.scene, rayreflect, hit.Depth);
    } else {
        Ray raytrans = reflex(hit.hitPoint, toCamera, hit.normal, tmp, sqrt(refraction), cosAngle);
        Color colortrans = computeColor(tmp);
        final = final + tracer->ShadeRay(hit.scene, rayreflect, hit.Depth) * colorreflect;
        final = final + tracer->ShadeRay(hit.scene, raytrans, hit.Depth) * colortrans;
    }
    return final;
}
/* Kolory */
static Color white = Color(1, 1, 1);
static Color black = Color(0, 0, 0);
static Color red = Color(1, 0, 0);
static Color green = Color(0, 1, 0);
static Color blue = Color(0, 0, 1);
static Color yellow = Color(1, 1, 0);
static Color cyan = Color(0, 1, 1);
static Color magenta = Color(1, 0, 1);
static Color gray = Color(0.7, 0.7, 0.7);
/* Diffuse */
static InterfaceMaterial* redMat = new PerfectDiffuse(red);
static InterfaceMaterial* greenMat = new PerfectDiffuse(green);
static InterfaceMaterial* blueMat = new PerfectDiffuse(blue);
static InterfaceMaterial* grayMat = new PerfectDiffuse(gray);
static InterfaceMaterial* whiteMat = new PerfectDiffuse(white);
static InterfaceMaterial* blackMat = new PerfectDiffuse(black);
static InterfaceMaterial* yellowMat = new PerfectDiffuse(yellow);
static InterfaceMaterial* magentaMat = new PerfectDiffuse(magenta);
static InterfaceMaterial* cyanMat = new PerfectDiffuse(cyan);
/* Reflex */
static InterfaceMaterial* redMet = new Phong(red, 0.7, 1, 30);
static InterfaceMaterial* greenMet = new Phong(green, 0.7, 1, 30);
static InterfaceMaterial* blueMet = new Phong(blue, 0.7, 1, 30);
static InterfaceMaterial* grayMet = new Phong(gray, 0.7, 1, 30);
static InterfaceMaterial* whiteMet = new Phong(white, 0.7, 1, 30);
static InterfaceMaterial* blackMet = new Phong(black, 0.7, 1, 30);
static InterfaceMaterial* yellowMet = new Phong(yellow, 0.7, 1, 30);
static InterfaceMaterial* magentaMet = new Phong(magenta, 0.7, 1, 30);
static InterfaceMaterial* cyanMet = new Phong(cyan, 0.7, 1, 30);
/* Mirror */
static InterfaceMaterial* redMir = new Reflective(red, 0.4, 1, 300, 0.6);
static InterfaceMaterial* greenMir = new Reflective(green, 0.4, 1, 300, 0.6);
static InterfaceMaterial* blueMir = new Reflective(blue, 0.4, 1, 300, 0.6);
static InterfaceMaterial* grayMir = new Reflective(gray, 0.4, 1, 300, 0.6);
static InterfaceMaterial* whiteMir = new Reflective(white, 0.4, 1, 300, 0.6);
static InterfaceMaterial* blackMir = new Reflective(black, 0.4, 1, 300, 0.6);
static InterfaceMaterial* yellowMir = new Reflective(yellow, 0.4, 1, 300, 0.6);
static InterfaceMaterial* magentaMir = new Reflective(magenta, 0.4, 1, 300, 0.6);
static InterfaceMaterial* cyanMir = new Reflective(cyan, 0.4, 1, 300, 0.6);
MyWindow::MyWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();
    img = new QImage(szer,wys,QImage::Format_RGB32);
    czysc();
}
MyWindow::~MyWindow() {
    delete ui;
}
void MyWindow::on_exitButton_clicked() {
    qApp->quit();
}
void MyWindow::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}
void MyWindow::on_cleanButton_clicked() {
    czysc();
}
void MyWindow::czysc() {
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++) {
        for(j=0; j<szer; j++) {
            ptr[szer*4*i + 4*j] = 255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
    update();
}
void MyWindow::on_pushButton_clicked() {
    Scene* scene = new Scene(cyan);
    scene->addObject(new Sphere(Vector3(-2.5,0,0),2, redMat));
    scene->addObject(new Sphere(Vector3(2.5,0,0),2, greenMat));
    scene->addObject(new Sphere(Vector3(0,0,2.5),2, blueMat));
    scene->addLight(new Light(Vector3(0,5,-5), white));
    InterfaceCamera* camera = new Orthogonal(Vector3(0,0,-5), 0, Vector2(5, 5));
    RayTracing ray(5);
    img = ray.rayTrace(img,wys,szer,scene, camera);
    update();
}
void MyWindow::on_pushButton_2_clicked() {
    QTime time = QTime::currentTime();
    ui->label_2->setText(time.toString());
    Scene* scene = new Scene(cyan);
    scene->addObject(new Sphere(Vector3(-4,0,2),2, redMir));
    scene->addObject(new Sphere(Vector3(4,0,2),2, greenMir));
    scene->addObject(new Sphere(Vector3(0,2,3),2, blueMir));
    scene->addObject(new Sphere(Vector3(0,0,0), 2,
                                new Transparent(Color(173/255.0,216/255.0,230/255.0), 0.1, 0, 0, 0.3, 1.05, 0.9)));
    scene->addObject(new Plane(Vector3(0,-2,0),Vector3(0,1,0), grayMet));
    scene->addLight(new Light(Vector3(0,5,-5), white));
    scene->addLight(new Light(Vector3(-3,5,-4), red));
    scene->addLight(new Light(Vector3(3,5,-4), blue));
    InterfaceCamera* camera = new Pinhole(Vector3(0, 1, -8), Vector3(0, 0, 0), Vector3(0, -1, 0), Vector2(1, 1),  1);
    Sampler* antiAlias = new Sampler(new Regular(), new SquareDistrib(), 5, 1);
    // lepsze cieniowanie (dziala prawie poprawnie dla sfer)
    /*Sampler* areaLightSampler = new Sampler(new Jittered(), new SquareDistrib(), 5, 1);
    scene->addLight(new Light(Vector3(0,5,-5), white, areaLightSampler, 2));
    scene->addLight(new Light(Vector3(-3,5,-5), red, areaLightSampler, 3));
    scene->addLight(new Light(Vector3(3,5,-5), blue, areaLightSampler, 1));*/
    // soczewka
    //InterfaceCamera* camera = new ThinLens(Vector3(0, 1, -8), Vector3(0, 0, 0), Vector3(0, -1, 0), Vector2(1, 1),  1, antiAlias, 1, 1);
    RayTracing ray(10);
    img = ray.rayTrace(img,wys,szer,scene, camera, antiAlias);
    time = QTime::currentTime();
    ui->label_4->setText(time.toString());
    update();
}
void MyWindow::on_pushButton_3_clicked() {
    QTime time = QTime::currentTime();
    ui->label_2->setText(time.toString());
    Scene* scene = new Scene(cyan);
    scene->addObject(new Sphere(Vector3(0, 2, 0), 15,
                                new Reflective(Color(200/255.0,200/255.0,200/255.0),0,1,30,1)));
    scene->addObject(new Sphere(Vector3(-4,0,2),2,
                                new Transparent(Color(173/255.0,216/255.0,230/255.0), 0.1, 0, 0, 0.3, 1.15, 0.9)));
    scene->addObject(new Sphere(Vector3(4,0,2),2,
                                new Transparent(Color(173/255.0,216/255.0,230/255.0), 0.1, 0, 0, 0.3, 1.15, 0.9)));
    scene->addObject(new Sphere(Vector3(0,2,3),2,
                                new Transparent(Color(173/255.0,216/255.0,230/255.0), 0.1, 0, 0, 0.3, 1.15, 0.9)));
    scene->addObject(new Sphere(Vector3(0,0,0), 2,
                                new Transparent(Color(173/255.0,216/255.0,230/255.0), 0.1, 0, 0, 0.3, 1.15, 0.9)));
    scene->addObject(new Plane(Vector3(0,-2,0),Vector3(0,1,0),
                               new Reflective(gray, 0.5, 1, 30, 0.5)));
    scene->addLight(new Light(Vector3(0,5,-5), white));
    scene->addLight(new Light(Vector3(-3,5,-4), red));
    scene->addLight(new Light(Vector3(3,5,-4), blue));
    InterfaceCamera* camera = new Pinhole(Vector3(0, 1, -8), Vector3(0, 0, 0), Vector3(0, -1, 0), Vector2(1, 1),  1);
    Sampler* antiAlias = new Sampler(new Regular(), new SquareDistrib(), 5, 1);
    // lepsze cieniowanie (dziala prawie poprawnie dla sfer)
    /*Sampler* areaLightSampler = new Sampler(new Jittered(), new SquareDistrib(), 5, 1);
    scene->addLight(new Light(Vector3(0,5,-5), white, areaLightSampler, 2));
    scene->addLight(new Light(Vector3(-3,5,-5), red, areaLightSampler, 3));
    scene->addLight(new Light(Vector3(3,5,-5), blue, areaLightSampler, 1));*/
    // soczewka
    //InterfaceCamera* camera = new ThinLens(Vector3(0, 1, -8), Vector3(0, 0, 0), Vector3(0, -1, 0), Vector2(1, 1),  1, antiAlias, 1, 1);
    RayTracing ray(10);
    img = ray.rayTrace(img,wys,szer,scene, camera, antiAlias);
    time = QTime::currentTime();
    ui->label_4->setText(time.toString());
    update();
}

void MyWindow::on_pushButton_4_clicked() {
    QTime time = QTime::currentTime();
    ui->label_2->setText(time.toString());
    Scene* scene = new Scene(cyan);
    scene->addObject(new Sphere(Vector3(0, 2, 0), 15, new Reflective(white,0,1,30,1)));
    scene->addObject(new Sphere(Vector3(-4,0,2),2, redMir));
    scene->addObject(new Sphere(Vector3(4,0,2),2, greenMir));
    scene->addObject(new Sphere(Vector3(0,2,3),2, blueMir));
    scene->addObject(new Sphere(Vector3(0,0,0), 2,
                                new Transparent(Color(173/255.0,216/255.0,230/255.0), 0.1, 0, 0, 0.3, 1.05, 0.9)));
    scene->addObject(new Plane(Vector3(0,-2,0),Vector3(0,1,0), grayMir));
    scene->addLight(new Light(Vector3(0,5,-5), white));
    scene->addLight(new Light(Vector3(-3,5,-4), red));
    scene->addLight(new Light(Vector3(3,5,-4), blue));
    InterfaceCamera* camera = new Pinhole(Vector3(0, 1, -8), Vector3(0, 0, 0), Vector3(0, -1, 0), Vector2(1, 1),  1);
    Sampler* antiAlias = new Sampler(new Regular(), new SquareDistrib(), 5, 1);
    // lepsze cieniowanie (dziala prawie poprawnie dla sfer)
    /*Sampler* areaLightSampler = new Sampler(new Jittered(), new SquareDistrib(), 5, 1);
    scene->addLight(new Light(Vector3(0,5,-5), white, areaLightSampler, 2));
    scene->addLight(new Light(Vector3(-3,5,-5), red, areaLightSampler, 3));
    scene->addLight(new Light(Vector3(3,5,-5), blue, areaLightSampler, 1));*/
    // soczewka
    //InterfaceCamera* camera = new ThinLens(Vector3(0, 1, -8), Vector3(0, 0, 0), Vector3(0, -1, 0), Vector2(1, 1),  1, antiAlias, 1, 1);
    RayTracing ray(5);
    img = ray.rayTrace(img,wys,szer,scene, camera, antiAlias);
    time = QTime::currentTime();
    ui->label_4->setText(time.toString());
    update();
}
