//
// Created by Xianyu on 2019-03-19.
//

#include "Texture.h"
#include "../const/Constant.h"

using namespace std;


Vec Texture::getSphereColor(Vec point) {

    double u = 0.5 + (atan2(point.z, point.x)) / (2 * M_PI);

    double v = 0.5 - asin(point.y) / M_PI;
    //cout << u << " " << v << endl;
    u = fmod(u * n, 1);
    v = fmod(v * n, 1);
    //cout << u <<" " << v << endl;
    int i = (h - int(v * h) - 1) * w + int(w * u);
    return img[i];
}

Texture::Texture(const std::string &f, int num) {
    cv::Mat img = cv::imread(f, 1);
    n = num;


    this->w = img.cols;
    this->h = img.rows;
    //int n = 2;

    this->img = new Vec[w * h];


    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            //int i = (h - y - 1) * w + x;
            int i = (w - x - 1) * h + y;
            this->img[i].x = double(img.at<cv::Vec3b>(x, y)[2]) / 255.0;
            this->img[i].y = double(img.at<cv::Vec3b>(x, y)[1]) / 255.0;
            this->img[i].z = double(img.at<cv::Vec3b>(x, y)[0]) / 255.0;
        }

    /*
    for(int i=1;i<n*n;++i)
        for(int j=0;j<w*h;++j)
        {
            this->img[i*w*h+j].x = this->img[j].x;
            this->img[i*w*h+j].y = this->img[j].y;
            this->img[i*w*h+j].z = this->img[j].z;

        }

    //通过opencv读取图片，存到我们的Vec里面
    this->h *= n;
    this->w *= n;
    */
    /*
    FILE *file = fopen("image2.ppm", "w");         // Write image to PPM file.
    fprintf(file, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i = 0; i < w * h; i++)
        fprintf(file, "%d %d %d ", toInt(this->img[i].x), toInt(this->img[i].y), toInt(this->img[i].z));
    */
}


