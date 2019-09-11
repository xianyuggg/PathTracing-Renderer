//
// Created by Xianyu on 2019-06-18.
//

#include "Obj.h"

Obj::Obj(Vec p_, Vec e_, Vec c_, Refl_type refl_, int times, std::string file)
        : Sphere(0, p_, e_, c_, refl_), times(times) {

    loadObj(file);

    calculateSphere();
//    this->rad += 35;
    std::cout << position << std::endl;
    std::cout << rad << std::endl;
    std::cout << "Vertex count : " << vertexes.size() << std::endl;
    std::cout << "Face count : " << faces.size() << std::endl;

    for(auto vertex:vertexes)
    {
        // Check if sphere is not valid
        if(vertex/position > rad)
        {
            assertfailed = true;
            std::cout << "Assert failed! " << std::endl;
            break;
        }
    }
    objt = OBJ;

    kdtree = new KdTree(&faces);


}


Vec Obj::getColor(const Vec &point) const {
    return color;
}

Vec Obj::getNormal(const Ray &r, const double& t) const {

    return faces[int(t)].getNormal(r,t);
}

double Obj::intersect(const Ray &r, int &parameter) {


    if( ! assertfailed &&!Sphere::intersect(r, parameter))
        return 0;
    std::vector<int> indices = kdtree->getTriangle(r);
    double tmin = 0;
    for (auto i : indices) {
        double t = faces[i].intersect(r);
        if (!t) continue;
        if (t < tmin || !tmin) {
            tmin = t;
            parameter = i;
        }
    }
    return tmin;

}


void Obj::loadObj(std::string file) {

    std::cout << "Loading from obj file " + file + " ... " << std::endl;
    std::ifstream input(file);
    while (input.getline(buffer, MAX_LENGTH)) {
        std::string line = buffer;
        if (!line.length()) continue;
        if (line[0] == 'v') addVertex(line);
        if (line[0] == 'f') addFace(line);
    }
    return;
}

std::string Obj::readNumber(std::string line, int &pos) {
    auto is_number = [](char c) -> bool {
        return ('0' <= c && c <= '9') || c == '.' || c == '-' || c == 'e';
    };
    int start = pos;
    while (start < line.length() && !is_number(line[start])) ++start;
    pos = start + 1;
    while (pos < line.length() && is_number(line[pos])) ++pos;
    return line.substr(start, pos - start);
}

void Obj::calculateSphere() {
    unsigned int maxx = 0, maxy = 0, maxz = 0, minx = -1, miny = -1, minz = -1;

    for (int i = 0; i < vertexes.size(); ++i) {
        if (vertexes[i].x > maxx) maxx = i;
        if (vertexes[i].x < minx) minx = i;
        if (vertexes[i].y > maxy) maxy = i;
        if (vertexes[i].y < miny) miny = i;
        if (vertexes[i].z > maxz) maxz = i;
        if (vertexes[i].z < minz) minz = i;
    }
    double x = 0;
    Vec sub1, sub2;
    sub1.x = vertexes[maxx].x;
    sub1.y = vertexes[maxx].y;
    sub1.z = vertexes[maxx].z;
    sub2.x = vertexes[minx].x;
    sub2.y = vertexes[minx].y;
    sub2.z = vertexes[minx].z;
    sub1.sub(sub1, sub2);
    x = sub1.dot(sub1);

    double y = 0;
    sub1.x = vertexes[maxy].x;
    sub1.y = vertexes[maxy].y;
    sub1.z = vertexes[maxy].z;
    sub2.x = vertexes[miny].x;
    sub2.y = vertexes[miny].y;
    sub2.z = vertexes[miny].z;
    sub1.sub(sub1, sub2);
    y = sub1.dot(sub1);

    double z = 0;
    sub1.x = vertexes[maxz].x;
    sub1.y = vertexes[maxz].y;
    sub1.z = vertexes[maxz].z;
    sub2.x = vertexes[minz].x;
    sub2.y = vertexes[minz].y;
    sub2.z = vertexes[minz].z;
    sub1.sub(sub1, sub2);
    z = sub1.dot(sub1);

    double dia = 0;
    int max = maxx, min = minx;
    if (z >= x && z >= y) {
        max = maxz;
        min = minz;
        dia = z;
    } else if (y >= x && y > z) {
        max = maxy;
        min = miny;
        dia = y;
    }

    this->position.x = 0.5 * (vertexes[max].x + vertexes[min].x);
    this->position.y = 0.5 * (vertexes[max].y + vertexes[min].y);
    this->position.z = 0.5 * (vertexes[max].z + vertexes[min].z);

    this->rad = 0.5 * sqrt(dia);

    // fix;
    for (int i = 0; i < vertexes.size(); ++i) {
        Vec d = Vec();
        vertexes[i].sub(d, this->position);
        double dist = d.dot(d);
        if (dist > this->rad * this->rad) {
            dist = sqrt(dist);
            double new_radius = (dist + this->rad) * 0.5;

            double k = (new_radius - this->rad) / dist;
            Vec tmp = d * k;

            this->rad = new_radius;
            this->position = tmp + this->position;
        }
    }



};

void Obj::addVertex(std::string line) {
    Vec vertex;
    int pos = 0;
    vertex.x = atof(readNumber(line, pos).c_str()) * times;
    vertex.y = atof(readNumber(line, pos).c_str()) * times;
    vertex.z = -atof(readNumber(line, pos).c_str()) * times;
    vertex = vertex + position;
    vertexes.push_back(vertex);
    return;
}

void Obj::addFace(std::string line) {
    int v[3];
    for (int i = 0, pos = 0; i < 3; ++i) {
        v[i] = atoi(readNumber(line, pos).c_str()) - 1;
    }
    Face face(vertexes[v[0]], vertexes[v[1]], vertexes[v[2]]);
    faces.push_back(face);
    return;
}



//bool Obj::checkPointinFaces(int index, const Vec &point) const {
//    Vec A = vertexes[faces[index].ids[0]];
//    Vec B = vertexes[faces[index].ids[1]];
//    Vec C = vertexes[faces[index].ids[2]];
//
//    Vec v0 = C - A;
//    Vec v1 = B - A;
//    Vec v2 = point - A;
//
//    // Compute dot products 计算点乘
//    double dot00 = v0.dot(v0);
//    double dot01 = v0.dot(v1);
//    double dot02 = v0.dot(v2);
//    double dot11 = v1.dot(v1);
//    double dot12 = v1.dot(v2);
//
//// Compute barycentric coordinates 计算系数坐标
//    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
//    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
//    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;
//
//// Check if point is in triangle 检测
//
//    return (u >= 0) && (v >= 0) && (u + v <= 1);
//}


