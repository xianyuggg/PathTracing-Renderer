//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_SPHERES_H
#define HW2_PT_SPHERES_H


#include "Object.h"

class Sphere : public Object {
public:
    double rad;        //半价,radius

    Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_type refl_, int num = 0, std::string file = "");

    ~Sphere() = default;

    //返回距离，如果没有命中的话返回0
    double intersect(const Ray &r, int &parameter) override;

    Vec getNormal(const Ray &r, const double &t) const override;

    Vec getColor(const Vec &point) const override;
};


#endif //HW2_PT_SPHERES_H
