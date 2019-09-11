//
// Created by Xianyu on 2019-06-29.
//

#ifndef PATHTRACING_FACE_H
#define PATHTRACING_FACE_H

#include "../const/Vec.h"

class Face {
public:
    Vec p0, p1, p2;
    Vec centroid;
    Face(Vec _p0, Vec _p1, Vec _p2):
            p0(_p0), p1(_p1), p2(_p2){
        centroid = Vec((p0.getX() + p1.getX() + p2.getX()) / 3, (p0.getY() + p1.getY() + p2.getY()) / 3, (p0.getZ() + p1.getZ() + p2.getZ()) / 3);

    }
    double intersect(const Ray& r){
        Vec e1 = p1 - p0;
        Vec e2 = p2 - p0;
        Vec p = (r.d).cross(e2);
        double det = e1.dot(p);
        Vec tt;
        if (det > 0) tt = r.o - p0;
        else {
            tt = p0 - r.o;
            det = -det;
        }
        if (det < 0.0001f) return 0;
        double u = tt.dot(p);
        if (u < 0.0f || u > det) return 0;
        Vec q = tt.cross(e1);
        double v = r.d.dot(q);
        if (v < 0.0f || u+v > det) return 0;
        if (e2.dot(q) <= 0) return 0;
        double t = e2.dot(q);
        double invDet = 1.0f / det;
        t *= invDet;
        return t;
    }
    Vec getP0(){return p0;}
    Vec getP1(){return p1;}
    Vec getP2(){return p2;}
    Vec getCentroid(){return centroid;}
    Vec getNormal(const Ray& r, const double t) const{
        double a = (p1.y-p0.y) * (p2.z-p0.z) - (p1.z-p0.z) * (p2.y-p0.y);
        double b = (p1.z-p0.z) * (p2.x-p0.x) - (p1.x-p0.x) * (p2.z-p0.z);
        double c = (p1.x-p0.x) * (p2.y-p0.y) - (p1.y-p0.y) * (p2.x-p0.x);
        Vec n(a,b,c);
        n.norm();
        return n.dot(r.d) < 0 ? n : n*-1;
    }
    Vec getNormal()const{
        double a = (p1.y-p0.y) * (p2.z-p0.z) - (p1.z-p0.z) * (p2.y-p0.y);
        double b = (p1.z-p0.z) * (p2.x-p0.x) - (p1.x-p0.x) * (p2.z-p0.z);
        double c = (p1.x-p0.x) * (p2.y-p0.y) - (p1.y-p0.y) * (p2.x-p0.x);
        Vec n(a,b,c);
        n.norm();
        return n;
    }

};

#endif //PATHTRACING_FACE_H
