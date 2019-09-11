//
// Created by Xianyu on 2019-03-17.
//

#include "Vec.h"
#include "Constant.h"

Vec::Vec(double x_, double y_, double z_) :
        x(x_), y(y_), z(z_) {
    array[0] = x;
    array[1] = y;
    array[2] = z;
}

Vec operator+(const Vec &left, const Vec &right) {
    return Vec(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vec operator-(const Vec &left, const Vec &right) {
    return Vec(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vec operator*(const Vec &left, double num) {
    return Vec(left.x * num, left.y * num, left.z * num);
}

double operator/(const Vec& left, const Vec& right){
    return sqrt(sqr(left.x - right.x) + sqr(left.y - right.y) + sqr(left.z - right.z));
}
Vec operator/(const Vec& left, double divisor){

        double x = left.getX() / divisor;
        double y = left.getY() / divisor;
        double z = left.getZ() / divisor;
        return Vec(x, y, z);

}

Vec Vec::multiplyVecByNum(const Vec &right) const {
    return Vec(this->x * right.x, this->y * right.y, this->z * right.z);
}

double Vec::dot(const Vec &right) const {
    return this->x * right.x + this->y * right.y + this->z * right.z;
}

Vec Vec::cross(const Vec &right) const {
    return Vec(this->y * right.z - this->z * right.y,
               this->z * right.x - this->x * right.z,
               this->x * right.y - this->y * right.x);
}

Vec &Vec::norm() {
    return *this = *this * (1 / sqrt(x * x + y * y + z * z));
}

std::ostream &operator<<(std::ostream &out, const Vec &a) {
    out << a.x << " " << a.y << " " << a.z;
    return out;
}

double Vec::abs() const {
    return sqrt(x * x + y * y + z * z);
}

void Vec::sub(Vec &out, Vec v2) {
    out.x = x - v2.x;
    out.y = y - v2.y;
    out.z = x - v2.z;
    out.array[0] = array[0] - v2.x;
    out.array[1] = array[1] - v2.y;
    out.array[2] = array[2] - v2.z;

}



Vec::~Vec() = default;


