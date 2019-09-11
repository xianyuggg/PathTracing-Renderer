//
// Created by Xianyu on 2019-06-29.
//

#ifndef PATHTRACING_KDTREE_H
#define PATHTRACING_KDTREE_H

#include "../const/Vec.h"
#include "../const/Ray.h"
#include <vector>
#include <map>
#include "Obj.h"
#include "AABB.h"
#include "Face.h"



#define MAX_LEVEL 20
#define MIN_TRIANGLE 25
class AABB {
public:
    AABB();
    AABB(Vec min, Vec max);
    bool isIntersect(const Ray& ray);
    bool isIntersect(Face face);

    Vec min;
    Vec max;
    Vec center;
    Vec boxHalfSize;
    std::vector<Ray> getLines() const;

private:
    bool edgeDetection(Vec v0, Vec v1, Vec v2, Vec edge0, Vec edge1, Vec edge2);
    bool aabbDetection(Vec v0, Vec v1, Vec v2);
    bool planeDetection(Vec normal, Vec vertex, Vec boxHalfSize);
    bool axisTestX(double a, double b, double fa, double fb, Vec v0, Vec v1);
    bool axisTestY(double a, double b, double fa, double fb, Vec v0, Vec v1);
    bool axisTestZ(double a, double b, double fa, double fb, Vec v0, Vec v1);

    std::vector<Ray> lines;
};

class KdTree {
public:
    KdTree();
    KdTree(std::vector<Face> * triangles);
    std::vector<int> getTriangle(const Ray& ray);
    std::vector<Ray> getLines(const Ray& ray);

private:

    class Node {
    public:
        Node(std::vector<int> triangles, KdTree * root, AABB aabbParent, int level, int dimension, int maxLevel, int minTriangle);
        Node();

        std::vector<int> getTriangle(const Ray& ray);
        std::vector<Ray> getLines(const Ray& ray);

    private:
        double generateSplit(std::vector<int> triangles);

        int level;
        Node * left = nullptr;
        Node * right = nullptr;
        std::vector<int> triangles;
        int dimension = 0;
        KdTree * root;
        AABB aabb;
        bool leaf = false;
    };

    std::vector<Face>*  triangles;
    Node * initNode;
};


#endif //PATHTRACING_KDTREE_H
