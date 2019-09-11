//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_OBJECT_H
#define HW2_PT_OBJECT_H

#include "../const/Constant.h"
#include "../const/Ray.h"
#include "Texture.h"

class Object {
public:
    Vec position, emission, color;
    Refl_type refl;
    Obj_type objt;
    Texture *texture;   //初始值为空
    Object(const Vec &p_, const Vec &e_, const Vec &c_, Refl_type refl_ = DIFF) :
            position(p_), emission(e_), color(c_), refl(refl_), texture(nullptr) {
    }

    virtual double intersect(const Ray &r, int &parameter) = 0;    //返回光束与物体的交点（最近的交点）
    virtual Vec getNormal(const Ray &r, const double& t) const = 0;    //返回一个点所处的法向量值
    virtual Vec getColor(const Vec &point) const = 0;


};


#endif //HW2_PT_OBJECT_H
