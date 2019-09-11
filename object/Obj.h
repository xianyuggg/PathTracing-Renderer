//
// Created by Xianyu on 2019-06-18.
//

#ifndef HW2_PT_OBJ_H
#define HW2_PT_OBJ_H

#include "KdTree.h"
#include "Spheres.h"

#include "Face.h"
class KdTree;
class Obj : public Sphere {
public:

    bool assertfailed = false;
    KdTree* kdtree;

    int times = 1;
    std::vector<Vec> vertexes;
    std::vector<Face> faces;
    char buffer[MAX_LENGTH];

    Obj(Vec p_, Vec e_, Vec c_, Refl_type refl_, int times = 10, std::string file = "");

    ~Obj() = default;

    Vec getColor(const Vec &point) const override;

    Vec getNormal(const Ray&r , const double &t) const override;

    double intersect(const Ray &r, int &parameter) override;

    void loadObj(std::string file = "");

    void calculateSphere();


    std::string readNumber(std::string line, int &pos);

    void addVertex(std::string line);

    void addFace(std::string line);


};


#endif //HW2_PT_OBJ_H
