//
// Created by Xianyu on 2019-06-29.
//

#include "KdTree.h"


AABB::AABB() {}

AABB::AABB(Vec min, Vec max) {
    this->min = min;
    this->max = max;
    boxHalfSize = (max - min) / 2;
    center = min + boxHalfSize;

    Vec p0 = min;
    Vec p1 = Vec(min.getX(), min.getY(), max.getZ());
    Vec p2 = Vec(max.getX(), min.getY(), max.getZ());
    Vec p3 = Vec(max.getX(), min.getY(), min.getZ());

    Vec p7 = max;
    Vec p4 = Vec(min.getX(), max.getY(), min.getZ());
    Vec p5 = Vec(max.getX(), max.getY(), min.getZ());
    Vec p6 = Vec(min.getX(), max.getY(), max.getZ());

    Ray line = Ray(p0, p1);
    lines.push_back(line);
    line = Ray(p1, p2);
    lines.push_back(line);
    line = Ray(p2, p3);
    lines.push_back(line);
    line = Ray(p3, p0);
    lines.push_back(line);

    line = Ray(p4, p6);
    lines.push_back(line);
    line = Ray(p6, p7);
    lines.push_back(line);
    line = Ray(p7, p5);
    lines.push_back(line);
    line = Ray(p5, p4);
    lines.push_back(line);

    line = Ray(p0, p4);
    lines.push_back(line);
    line = Ray(p3, p5);
    lines.push_back(line);
    line = Ray(p2, p7);
    lines.push_back(line);
    line = Ray(p1, p6);
    lines.push_back(line);
}

bool AABB::isIntersect(const Ray& ray) {
    //Vector rayDirection = Vector::normalize(ray.getEndPoint() - ray.getOriginPoint());
    //Vector dirFrac(1 / rayDirection.getX(), 1 / rayDirection.getY(), 1 / rayDirection.getZ());
    Vec dirFrac = ray.getDirFrac();

    double t1 = (min.getX() - ray.getOriginPoint().getX()) * dirFrac.getX();
    double t2 = (max.getX() - ray.getOriginPoint().getX()) * dirFrac.getX();

    double t3 = (min.getY() - ray.getOriginPoint().getY()) * dirFrac.getY();
    double t4 = (max.getY() - ray.getOriginPoint().getY()) * dirFrac.getY();

    double t5 = (min.getZ() - ray.getOriginPoint().getZ()) * dirFrac.getZ();
    double t6 = (max.getZ() - ray.getOriginPoint().getZ()) * dirFrac.getZ();

    double tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    double tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    if(tmax < 0) {
        return false;
    }

    if(tmin > tmax) {
        return false;
    }

    return true;
}

bool AABB::isIntersect(Face triangle) {
    Vec v0 = Vec(0, 0, 0) + (triangle.getP0() - center);
    Vec v1 = Vec(0, 0, 0) + (triangle.getP1() - center);
    Vec v2 = Vec(0, 0, 0) + (triangle.getP2() - center);

    Vec edge0 = v1 - v0;
    Vec edge1 = v2 - v1;
    Vec edge2 = v0 - v2;

    return aabbDetection(v0, v1, v2) &&
           planeDetection(triangle.getNormal(), v0, boxHalfSize) &&
           edgeDetection(v0, v1, v2, edge0, edge1, edge2);
}

bool AABB::edgeDetection(Vec v0, Vec v1, Vec v2, Vec edge0, Vec edge1, Vec edge2) {
    double fex = fabs(edge0.getX());
    double fey = fabs(edge0.getY());
    double fez = fabs(edge0.getZ());
    if (!axisTestX(edge0.getZ(), edge0.getY(), fez, fey, v0, v2)) {
        return false;
    }
    if (!axisTestY(edge0.getZ(), edge0.getX(), fez, fex, v0, v2)) {
        return false;
    }
    if (!axisTestZ(edge0.getY(), edge0.getX(), fey, fex, v1, v2)) {
        return false;
    }

    fex = fabs(edge1.getX());
    fey = fabs(edge1.getY());
    fez = fabs(edge1.getZ());
    if (!axisTestX(edge1.getZ(), edge1.getY(), fez, fey, v0, v2)) {
        return false;
    }
    if (!axisTestY(edge1.getZ(), edge1.getX(), fez, fex, v0, v2)) {
        return false;
    }
    if (!axisTestZ(edge1.getY(), edge1.getX(), fey, fex, v0, v1)) {
        return false;
    }

    fex = fabs(edge2.getX());
    fey = fabs(edge2.getY());
    fez = fabs(edge2.getZ());
    if (!axisTestX(edge2.getZ(), edge2.getY(), fez, fey, v0, v1)) {
        return false;
    }
    if (!axisTestY(edge2.getZ(), edge2.getX(), fez, fex, v0, v1)) {
        return false;
    }
    if (!axisTestZ(edge2.getY(), edge2.getX(), fey, fex, v1, v2)) {
        return false;
    }

    return true;
}

bool AABB::aabbDetection(Vec v0, Vec v1, Vec v2) {
    double max = fmax(fmax(v0.getX(), v1.getX()), v2.getX());
    double min = fmin(fmin(v0.getX(), v1.getX()), v2.getX());
    if (min > boxHalfSize.getX() || max < -boxHalfSize.getX()) {
        return false;
    }

    max = fmax(fmax(v0.getY(), v1.getY()), v2.getY());
    min = fmin(fmin(v0.getY(), v1.getY()), v2.getY());
    if (min > boxHalfSize.getY() || max < -boxHalfSize.getY()) {
        return false;
    }

    max = fmax(fmax(v0.getZ(), v1.getZ()), v2.getZ());
    min = fmin(fmin(v0.getZ(), v1.getZ()), v2.getZ());
    if (min > boxHalfSize.getZ() || max < -boxHalfSize.getZ()) {
        return false;
    }

    return true;
}

bool AABB::planeDetection(Vec normal, Vec vertex, Vec boxHalfSize) {
    double vMax[3], vMin[3];
    double v;

    v = vertex.getX();
    if (normal.getX() > 0) {
        vMin[0] = -boxHalfSize.getX() - v;
        vMax[0] = boxHalfSize.getX() - v;
    } else {
        vMin[0] = boxHalfSize.getX() - v;
        vMax[0] = -boxHalfSize.getX() - v;
    }

    v = vertex.getY();

    if (normal.getY() > 0) {
        vMin[1] = -boxHalfSize.getY() - v;
        vMax[1] = boxHalfSize.getY() - v;
    } else {
        vMin[1] = boxHalfSize.getY() - v;
        vMax[1] = -boxHalfSize.getY() - v;
    }

    v = vertex.getZ();

    if (normal.getZ() > 0) {
        vMin[2] = -boxHalfSize.getZ() - v;
        vMax[2] = boxHalfSize.getZ() - v;
    } else {
        vMin[2] = boxHalfSize.getZ() - v;
        vMax[2] = -boxHalfSize.getZ() - v;
    }


    Vec max(vMax[0], vMax[1], vMax[2]);
    Vec min(vMin[0], vMin[1], vMin[2]);

    if (normal.dot(min) > 0) {
        return false;
    }
    if (normal.dot(max) >= 0) {
        return true;
    }

    return false;
}

bool AABB::axisTestX(double a, double b, double fa, double fb, Vec v0, Vec v1) {
    double p0 = a*v0.getY() - b*v0.getZ();
    double p2 = a*v1.getY() - b*v1.getZ();

    double min = fmin(p0, p2);
    double max = fmax(p0, p2);

    double rad = fa * boxHalfSize.getY() + fb * boxHalfSize.getZ();

    if (min > rad || max < -rad) {
        return false;
    } else {
        return true;
    }
}

bool AABB::axisTestY(double a, double b, double fa, double fb, Vec v0, Vec v1) {
    double p0 = a*v0.getX() - b*v0.getZ();
    double p2 = a*v1.getX() - b*v1.getZ();

    double min = fmin(p0, p2);
    double max = fmax(p0, p2);

    double rad = fa * boxHalfSize.getX() + fb * boxHalfSize.getZ();

    if (min > rad || max < -rad) {
        return false;
    } else {
        return true;
    }
}
bool AABB::axisTestZ(double a, double b, double fa, double fb, Vec v0, Vec v1) {
    double p0 = a*v0.getX() - b*v0.getY();
    double p2 = a*v1.getX() - b*v1.getY();

    double min = fmin(p0, p2);
    double max = fmax(p0, p2);

    double rad = fa * boxHalfSize.getX() + fb * boxHalfSize.getY();

    if (min > rad || max < -rad) {
        return false;
    } else {
        return true;
    }
}
std::vector<Ray> AABB::getLines() const
{
    return lines;
}
