//
// Created by Xianyu on 2019-03-17.
//

#include "Constant.h"

std::default_random_engine re(time(0));

//生成0-1随机数
double erand() {


    return (double) (re() % 100000) / ((double) 100000);
}

//将所有的颜色转化为0，255的范围
double clamp(double x) { return x < 0 ? 0 : x > 1 ? 1 : x; }

//pow(clamp(x), 1/ 2.2),gamma校正方法
int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

double sqr(double x) {
    return x * x;
}
