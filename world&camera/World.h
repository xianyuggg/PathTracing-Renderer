//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_WORLD_H
#define HW2_PT_WORLD_H

#include "../object/Spheres.h"
#include "../object/Plane.h"
#include "../object/Obj.h"
#include "Camera.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../const/Constant.h"

class World {
public:
    std::vector<Object *> v;
    Camera *cam;
    int num = 0;

    //令这个世界存在最多10个物体
    World() {
        this->v.assign(15, nullptr);        //这个世界最多有10个物体
    }

    /* position direction width height aperture */
    void addPlane(double d_, Vec e_, Vec c_, Vec n_, Refl_type refl_);

    void initCam(Vec p_, Vec d_, int w_, int h_, double a_);

    void addSphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_type refl_, int num = 0, const std::string &file = "");

    void addObj(Vec p_, Vec e_, Vec c_, Refl_type refl_, int times, const std::string &file = "");

    bool intersect(const Ray &r, double &t, int &id, int &parameter);

    Vec radiance(const Ray &r, int depth);


};

#endif //HW2_PT_WORLD_H
