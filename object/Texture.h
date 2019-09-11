//
// Created by Xianyu on 2019-03-19.
//

#ifndef HW2_PT_TEXTURE_H
#define HW2_PT_TEXTURE_H

#include "../const/Constant.h"
#include "../const/Vec.h"
#include "opencv2/opencv.hpp"

class Texture {
public:
    Vec *img;
    int w, h;
    int n;

    explicit Texture(const std::string &f, int num);

    Vec getSphereColor(Vec point);


};


#endif //HW2_PT_TEXTURE_H
