//
// Created by Xianyu on 2019-03-17.
//

#include "Spheres.h"
#include "cmath"

Sphere::Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_type refl_, int num, std::string file) :
        rad(rad_), Object(p_, e_, c_, refl_) {
    if (!file.empty())
        texture = new Texture(file, num);


    objt = Obj_type::SPHERE;
}

double Sphere::intersect(const Ray &r,  int &parameter){
    Vec op = position - r.o;
    double t = EPISILON;
    double b = op.dot(r.d), det = b * b + rad * rad - op.dot(op);
    if (det < 0)
        return 0;
    else
        det = sqrt(det);
    return (t = b - det) > EPISILON ? t : ((t = b + det) > EPISILON ? t : 0);
}

Vec Sphere::getNormal(const Ray &ray, const double &t) const {
    Vec point = ray.o + ray.d * t;
    return (point - this->position).norm();
}

Vec Sphere::getColor(const Vec &point) const {
    if (texture == nullptr)
        return color;
    else
        return texture->getSphereColor((point - this->position).norm());
}