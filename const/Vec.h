//
// Created by Xianyu on 2019-03-17.
//

#ifndef HW2_PT_VEC_H
#define HW2_PT_VEC_H

#include <iostream>

class Vec {
public:
    double x, y, z;
    double array[3];
    explicit Vec(double x_ = 0, double y_ = 0, double z_ = 0);

    friend Vec operator+(const Vec &left, const Vec &right);

    friend Vec operator-(const Vec &left, const Vec &right);

    friend Vec operator*(const Vec &left, double num);

    friend Vec operator/(const Vec& left, double divisor);
    Vec multiplyVecByNum(const Vec &right) const;

    //Calculate distance
    friend double operator/(const Vec& left, const Vec& right);

    //点乘
    double dot(const Vec &right) const;

    //叉乘
    Vec cross(const Vec &right) const;

    //标准化
    Vec &norm();

    void sub(Vec &out, Vec v2);

    double abs() const;

    friend std::ostream &operator<<(std::ostream &out, const Vec &a);

    double getX()const {return x;}
    double getY()const {return y;}
    double getZ()const {return z;}
    double getDimension(int dimension) const{return array[dimension];}
    ~Vec();

};

#endif //HW2_PT_VEC_H
