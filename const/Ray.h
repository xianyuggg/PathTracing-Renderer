//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_RAY_H
#define HW2_PT_RAY_H

#include "Vec.h"

class Ray {
public:
    Vec o, d;    //起始与方向
    Ray(const Vec &o_, Vec d_) : o(o_), d(d_.norm()) {}
    // Ray的方向默认进行标准化
    Vec getOriginPoint() const {
        return o;
    }

    Vec getDirFrac() const{
        return Vec(1 / d.getX(), 1 / d.getY(), 1 / d.getZ());
    }
};

#endif //HW2_PT_RAY_H
