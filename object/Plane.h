//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_PLANE_H
#define HW2_PT_PLANE_H

#include "Object.h"

class Plane : public Object {
public:
    Vec n;

    Plane(Vec p_, Vec e_, Vec c_, Vec n_, Refl_type refl_ = SPEC);

    double intersect(const Ray &r, int &parameter) override;

    Vec getNormal(const Ray& r, const double& t) const override;

    ~Plane() = default;

    Vec getColor(const Vec &point) const override;

};

#endif //HW2_PT_PLANE_H
