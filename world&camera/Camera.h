//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_CAMERA_H
#define HW2_PT_CAMERA_H


#include "../const/Ray.h"

class Camera : public Ray {
public:
    int w, h;
    double angle;

    double flength;
    double aperture;

    Vec r1, r2;         //used for calculate the aperture...

    Vec cx, cy;      //cx,cy定义视角
    Camera(const Vec &p_, Vec d_, int w_, int h_, double a_) :
            Ray(p_, d_), w(w_), h(h_), angle(a_) {

        flength = 0;
        aperture = 0;

        // Ax + By + Cz = 0
        double randx = erand() - 0.5;
        double randy = erand() - 0.5;
        double randz = (0.0 - d.x * randx - d.y * randx) / d.z;
        r1 = Vec(randx, randy, randz).norm();
        r2 = r1.cross(d).norm();

        cx = Vec(w * angle / h);
        cy = (cx.cross(d)).norm() * angle;

    }

    void setFOV(double f_, double a_) {
        flength = f_;
        aperture = a_;
    }

    ~Camera() = default;


};

#endif //HW2_PT_CAMERA_H
