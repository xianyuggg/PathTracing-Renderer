//
// Created by Xianyu on 2019-03-17.
//

#include "Plane.h"

Plane::Plane(Vec p_, Vec e_, Vec c_, Vec n_, Refl_type refl_)
        : Object(p_, e_, c_, refl_), n(n_.norm()) {
    objt = Obj_type::PLANE;
}

//	The equation for the Plane :
//	H(p) = n*P + D = 0
//	Ax + By + Cz + D = 0
//	使用p.x表示D
double Plane::intersect(const Ray &r, int &parameter) {
    if (n.dot(r.d) > 0)
        return 0;    //若和法线方向保持一致，此时不符合我们的设想

    double son = -position.x - n.dot(r.o);
    double mom = n.dot(r.d);
    double t = son / mom;
    if (t < 0)
        return INFINITY;
    else
        return t;
}

Vec Plane::getNormal(const Ray& r, const double &t) const {
    return n;
}

Vec Plane::getColor(const Vec &point) const {
    return color;
}
