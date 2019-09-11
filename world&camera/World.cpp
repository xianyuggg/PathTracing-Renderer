//
// Created by Xianyu on 2019-03-17.
//

#include "World.h"
#include <iostream>

void World::addSphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_type refl_, int num, const std::string &file) {
    v[this->num++] = new Sphere(rad_, p_, e_, c_, refl_, num, file);
}

void World::addObj(Vec p_, Vec e_, Vec c_, Refl_type refl_, int times, const std::string &file) {
    v[this->num++] = new Obj(p_, e_, c_, refl_, times, file);
}

void World::addPlane(double d_, Vec e_, Vec c_, Vec n_, Refl_type refl_) {
    v[num++] = new Plane(Vec(d_), e_, c_, n_, refl_);
}

void World::initCam(Vec p_, Vec d_, int w_, int h_, double a_) {
    this->cam = new Camera(p_, d_, w_, h_, a_);
}

bool World::intersect(const Ray &r, double &t, int &id, int &parameter) {


    double d;
    t = INFINITY;    //无穷
    // d 用于计算 当前距离
    // t 用于表示 当前的最小值
    for (int i = this->num; i--;) {

        if ((d = v[i]->intersect(r, parameter)) && d < t) {
            t = d;
            id = i;
        }
    }
    return t < INFINITY;

}

Vec World::radiance(const Ray &r, int depth) {
    if(depth > 10)
        return Vec(0,0,0);
    double t;        //t用于表示当前的最小值(参数t)
    int id = 0;        //与第i个球相交
    int parameter = -1;
    if (!intersect(r, t, id, parameter))
        return Vec();               //(0,0,0)

    Object *obj = v[id];

    Vec x = r.o + r.d * t;          //交点，x,y,z
    Vec n;
    if(obj->objt == OBJ)
        n = obj->getNormal(r, parameter);
    else
        n = obj->getNormal(r, t);

    Vec f = obj->getColor(x);             //getColor

    Vec nl = n.dot(r.d) < 0 ? n : n * -1;

    double p = (f.x > f.y && f.x > f.z) ? f.x : (f.y > f.z) ? f.y : f.z; // max refl
    if (++depth > 5 || !p) {
        if (erand() < p) { f = f * (1 / p); }
        else { return obj->emission; }
    }
    if (obj->refl == DIFF) {                  // Ideal DIFFUSE reflection
        double r1 = 2 * M_PI * erand(), r2 = erand(), r2s = sqrt(r2);
        Vec w = nl, u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)).cross(w)).norm(), v = w.cross(u); //w，v，u为正交基
        Vec d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();
        return obj->emission + f.multiplyVecByNum(radiance(Ray(x, d), depth));
    } else if (obj->refl == SPEC)            // Ideal SPECULAR reflection
        return obj->emission + f.multiplyVecByNum(radiance(Ray(x, r.d - n * 2 * n.dot(r.d)), depth));

    Ray reflRay(x, r.d - n * 2 * n.dot(r.d));     // Ideal dielectric REFRACTION 由平行四边形的方法求得反射光的direction
    bool into = n.dot(nl) > 0;              // Ray from outside going in?
    double nc = 1, nt = 1.5, nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;

    if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) < 0) // Total internal reflection
        return obj->emission + f.multiplyVecByNum(radiance(reflRay, depth));

    Vec tdir = (r.d * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t)))).norm();
    double a = nt - nc, b = nt + nc, R0 = a * a / (b * b), c = 1 - (into ? -ddn : tdir.dot(n));
    double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re, P = .25 + .5 * Re, RP = Re / P, TP = Tr / (1 - P);
    return obj->emission + f.multiplyVecByNum(depth > 2 ? (erand() < P ? // Russian roulette
                                                           radiance(reflRay, depth) * RP :
                                                           radiance(Ray(x, tdir), depth) * TP) :
                                              radiance(reflRay, depth) * Re + radiance(Ray(x, tdir), depth) * Tr);
}
