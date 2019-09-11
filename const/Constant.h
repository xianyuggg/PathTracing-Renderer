//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_CONSTANT_H
#define HW2_PT_CONSTANT_H
# define MAX_LENGTH 65536ul
#define M_PI 3.1415926
#define M_1_PI (1.0 / M_PI)
#define EPISILON 1e-4
#define INFINITY 1e20
#define THREAD_NUM 24
#define DEFAULT_SAMPS 250;


#define CAMERA myworld->cam

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <random>
#include <ctime>

//生成0-1随机数
double erand();

//将所有的颜色转化为0，255的范围
double clamp(double x);

//pow(clamp(x), 1/ 2.2),gamma校正方法
int toInt(double x);

double sqr(double x);

enum Refl_type {
    DIFF = 0,
    SPEC,
    REFR,    // diffuse, specular, refractive
};
enum Obj_type {
    SPHERE = 0,
    OBJ = 1,
    PLANE = 2,

};

#endif //HW2_PT_CONSTANT_H
