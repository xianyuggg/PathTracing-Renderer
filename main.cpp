#include "const/Constant.h"
#include "world&camera/World.h"
#include <thread>
// #define CAMERA myworld->cam
// Ray的方向默认进行标准化
using namespace std;

int Rendering(Vec *img, World *myworld, int w, int h, int samps, int i);
//void WriteToFile();

int main(int argc, char *argv[]) {


    int samps = argc == 2 ? atoi(argv[1]) / 4 : DEFAULT_SAMPS; //samples,默认是10
    int w = 1024, h = 768;


    World *myworld;

    myworld = new World();
    //位置，方向（光线发出的位置和方向），长宽，参数（视角）
    myworld->initCam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm(), w, h, 0.5135);
    //int focal_length = 190;
    int focal_length = 0;
    double aperture = 2.5;
    CAMERA->setFOV(focal_length, aperture);
    //Scene: radius, position, emission, color, material
    myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF); //left
    myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);   //right

    myworld->addSphere(1e5, Vec(50, 40.8, 1e5), Vec(), Vec(.75, .75, .75), DIFF, 30000, "sourcepic/marble.bmp"); //back

    myworld->addSphere(1e5, Vec(50, 1e5, 81.6), Vec(), Vec(.75, .75, .75), DIFF, 4000 , "sourcepic/star.jpg");    //bottom
    myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
    myworld->addSphere(16.5, Vec(75, 16.5, 35), Vec(), Vec(1, 1, 1) * .999, SPEC); //glass

    myworld->addSphere(16.5, Vec(25, 16.5, 35), Vec(), Vec(1, 1, 1) * .999, DIFF, 2, "sourcepic/star.jpg"); //glass
    myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(14, 14, 14), Vec(), DIFF); //lite

    myworld->addObj(Vec(50, 45, 105), Vec(), Vec(1, 1, 1) * 0.99, REFR, 30,"Meshes/fixed.perfect.dragon.100K.0.07.obj");


    Vec *image = new Vec[w * h];


    // * multi-threading,
    // * default threads number : THREADNUM defined in Constant.h
    auto *threads = new std::thread[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i)
        threads[i] = std::thread(Rendering, image, myworld, w, h, samps, i);

    //Rendering(image, myworld, w, h, samps);
    for (int i = 0; i < THREAD_NUM; ++i)
        threads[i].join();

    //产生文件名: 月份-日期_小时-秒-ssp
    time_t t;
    struct tm *p;
    char filename[256] = {0};
    t = time(nullptr);
    p = gmtime(&t);
    sprintf(filename, "result/image%d_%d-%d_%d-F_%d-A_%f_%dssp.ppm", 1 + p->tm_mon, \
            p->tm_mday, p->tm_hour + 8, p->tm_min, focal_length, aperture, samps);

    //将img写入ppm文件
    FILE *f = std::fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i = 0; i < w * h; i++)
        fprintf(f, "%d %d %d ", toInt(image[i].x), toInt(image[i].y), toInt(image[i].z));

}


int Rendering(Vec *img, World *myworld, int w, int h, int samps, int i) {
    Vec r;
    fprintf(stderr, "THREAD : %d Rendering\n", i);
    int range = w / THREAD_NUM;
    /* left boundary and right boundary */
    int lb, rb;
    lb = i * range;
    rb = (i == (THREAD_NUM - 1)) ? w : (i + 1) * (range);
    for (int y = 0; y < h; y++) // Loop over image rows
    {
        for (int x = lb; x < rb; x++)   // Loop cols
        {

            // 使用i确定当前渲染像素的序号，从左下角，自左往右，自下而上进行渲染
            for (int sy = 0, index = (h - y - 1) * w + x; sy < 2; sy++)             // 2x2 subpixel rows
                for (int sx = 0; sx < 2; sx++, r = Vec()) {   // 2x2 subpixel cols
                    Vec d = Vec();

                    if (CAMERA->flength == 0) {
                        for (int s = 0; s < samps; s++) {
                            /* Using no depth of field */
                            if (CAMERA->flength == 0) {
                                double r1 = 2 * erand(), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
                                double r2 = 2 * erand(), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
                                d = CAMERA->cx * (((sx + 0.5 + dx) / 2 + x) / w - .5) +
                                    CAMERA->cy * (((sy + 0.5 + dy) / 2 + y) / h - .5) + CAMERA->d;
                                r = r + myworld->radiance(Ray(CAMERA->o, d), 0) * (1. / samps);   //// o + d * 140
                            }

                        }
                    } else {
                        for (int j = 0; j < samps; ++j) {
                            double r1 = 2 * erand(), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
                            double r2 = 2 * erand(), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
                            d = CAMERA->cx * (((sx + 0.5 + dx) / 2 + x) / w - .5) +
                                CAMERA->cy * (((sy + 0.5 + dy) / 2 + y) / h - .5) + CAMERA->d;
                            d = d.norm() * CAMERA->flength;
                            double rand1 = erand() * 2 - 1.0;
                            double rand2 = erand() * 2 - 1.0;

                            Vec v1 = CAMERA->r1 * rand1 * CAMERA->aperture;
                            Vec v2 = CAMERA->r2 * rand2 * CAMERA->aperture;
                            /*
                             * focal point and start point;
                             * start point equals to camera position in a plane area(aperture)
                             */
                            Vec sp = CAMERA->o + v1 + v2;
                            Vec fp = d + CAMERA->o;
                            d = (fp - sp);
                            r = r + myworld->radiance(Ray(sp, d), 0) * (1. / double(samps));
                        }

                    }
                    img[index] = img[index] + Vec(clamp(r.x), clamp(r.y), clamp(r.z)) * .25;

                }
        }
        if (y % 25 == 0)
            fprintf(stderr, "\rTHREAD : %d Rendering (%d spp) %5.2f%%", i, samps * 4, 100. * y / (h - 1));
    }
    fprintf(stderr, "\nTHREAD : %d Rendering Complete!", i);
    return 0;

}




//一个经典场景
// myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF);  //left
// myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);    //right
// myworld->addSphere(1e5, Vec(50, 40.8, 1e5),     Vec(), Vec(.75, .75, .75), DIFF);    //back
// myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), Vec(),           DIFF);    //front
// myworld->addSphere(1e5, Vec(50, 1e5, 81.6),    Vec(), Vec(.75, .75, .75), DIFF); //bottom
// myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);    //top
// myworld->addSphere(16.5, Vec(27, 16.5, 47),       Vec(), Vec(1, 1, 1)*.999, DIFF);   //mirror
// myworld->addSphere(16.5, Vec(73, 16.5, 78),       Vec(), Vec(1, 1, 1)*.999, REFR);   //glass
// myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(12, 12, 12),  Vec(), DIFF);  //lite

/*
myworld = new World();
myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF); //left
myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);   //right

myworld->addSphere(1e5, Vec(50, 40.8, 1e5),     Vec(), Vec(.75, .75, .75), DIFF,"sourcepic/floor.bmp"); //back
//myworld->addPlane(10,Vec(),Vec(10,10,10),Vec(0,0,1),DIFF);
//myworld->addPlane(-30,Vec(),Vec(1,1,1),Vec(1,1,1),SPEC);
//myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), Vec(),           DIFF); //front
myworld->addSphere(1e5, Vec(50, 1e5, 81.6),    Vec(), Vec(.75, .75, .75), DIFF);    //bottom
myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
myworld->addSphere(20, Vec(35, 16.5, 30),       Vec(), Vec(1, 1, 1)*.999, DIFF,"sourcepic/huaji.jpeg"); //mirror
myworld->addSphere(16.5, Vec(65, 16.5, 108),       Vec(), Vec(1, 1, 1)*.999, DIFF, "sourcepic/huaji.jpeg"); //glass
myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(12, 12, 12),  Vec(), DIFF); //lite

//位置，方向（光线发出的位置和方向），长宽，参数（视角）

myworld->initCam(Vec(50, 25, 200), Vec(0, -0.022612, -1).norm(), w, h, 0.5135);
 */

/*
 *  myworld = new World();
    myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), SPEC); //left
    myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .45, .75), SPEC);   //right

    myworld->addSphere(1e5, Vec(50, 40.8, 1e5),     Vec(), Vec(.75, .75, .75), DIFF, 20000, "sourcepic/marble.bmp"); //back
    myworld->addPlane(85,Vec(),Vec(0.25,.45,.75),Vec(-1,0.015,0),SPEC);
    //myworld->addPlane(-30,Vec(),Vec(1,1,1),Vec(1,1,1),SPEC);
    //myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), Vec(),           DIFF);  //front
    myworld->addSphere(1e5, Vec(50, 1e5, 81.6),    Vec(), Vec(.75, .75, .75), DIFF);    //bottom
    myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
    myworld->addSphere(10, Vec(40, 10, 30),       Vec(), Vec(1, 1, 1)*.999, DIFF, 3, "sourcepic/huaji.jpeg"); //mirror
    myworld->addSphere(8, Vec(60, 8, 108),       Vec(), Vec(1, 1, 1)*.999, DIFF, 4, "sourcepic/star.jpg");  //glass
    myworld->addSphere(600, Vec(50, 681.6 - .27, 110), Vec(18, 18, 18),  Vec(), DIFF);  //lite

    //位置，方向（光线发出的位置和方向），长宽，参数（视角）
    //myworld->initCam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm(), w, h, 0.5135);
    myworld->initCam(Vec(50, 3, 160), Vec(0.11, 0.14, -1).norm(), w, h, 0.6);

 */
/*
int focal_length = 180;
double aperture = 4.0;
CAMERA->setFOV(focal_length, aperture);



myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF); //left
myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);   //right

myworld->addSphere(1e5, Vec(50, 40.8, 1e5),     Vec(), Vec(.75, .75, .75), DIFF,30000, "sourcepic/marble.bmp"); //back

//myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), Vec(),           DIFF); //front
myworld->addSphere(1e5, Vec(50, 1e5, 81.6),    Vec(), Vec(.75, .75, .75), DIFF);    //bottom
myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
myworld->addSphere(20, Vec(35, 16.5, 30),       Vec(), Vec(1, 1, 1)*.999, DIFF,3, "sourcepic/huaji.jpeg"); //mirror
myworld->addSphere(16.5, Vec(65, 16.5, 108),       Vec(), Vec(1, 1, 1)*.999, DIFF,4 , "sourcepic/star.jpg"); //glass
myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(12, 12, 12),  Vec(), DIFF); //lite
*/


//myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF); //left
//myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);   //right
//
//myworld->addSphere(1e5, Vec(50, 40.8, 1e5), Vec(), Vec(.75, .75, .75), DIFF, 30000, "sourcepic/marble.bmp"); //back
//
////myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), Vec(),           DIFF); //front
//myworld->addSphere(1e5, Vec(50, 1e5, 81.6), Vec(), Vec(.75, .75, .75), DIFF, 2000 , "sourcepic/star.jpg");    //bottom
//myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
////myworld->addSphere(20, Vec(35, 16.5, 30),       Vec(), Vec(1, 1, 1)*.999, DIFF,3, "sourcepic/huaji.jpeg"); //mirror
//myworld->addSphere(16.5, Vec(65, 16.5, 30), Vec(), Vec(1, 1, 1) * .999, SPEC); //glass
//myworld->addSphere(16.5, Vec(70, 16.5, 105), Vec(), Vec(1, 1, 1) * .999, DIFF, 3, "sourcepic/huaji.jpeg"); //glass
//myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(12, 12, 12), Vec(), DIFF); //lite
////myworld->addObj(Vec(30, 0, 105), Vec(), Vec(1, 0.5, 0.3) * 0.88, SPEC, 25, "Meshes/cube.obj");
//myworld->addObj(Vec(35, 25, 105), Vec(), Vec(1, 0.5, 0.3) * 0.88, SPEC, 25,"Meshes/arma_0.01.obj");
//
//// myworld->addPlane(-75,Vec(0,0,0),Vec(1,1,1),Vec(0,0,-1) ,DIFF);



//Final1 Scene:
//myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF); //left
//myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);   //right
//
//myworld->addSphere(1e5, Vec(50, 40.8, 1e5), Vec(), Vec(.75, .75, .75), DIFF, 30000, "sourcepic/marble.bmp"); //back
//
////myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(0.75,0.35,.25), Vec(),           DIFF); //front
//myworld->addSphere(1e5, Vec(50, 1e5, 81.6), Vec(), Vec(.75, .75, .75), DIFF, 4000 , "sourcepic/star.jpg");    //bottom
//myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
////myworld->addSphere(20, Vec(35, 16.5, 30),       Vec(), Vec(1, 1, 1)*.999, DIFF,3, "sourcepic/huaji.jpeg"); //mirror
//myworld->addSphere(16.5, Vec(75, 16.5, 35), Vec(), Vec(1, 1, 1) * .999, SPEC); //glass
//myworld->addSphere(16.5, Vec(25, 16.5, 35), Vec(), Vec(1, 1, 1) * .999, DIFF, 4, "sourcepic/star.jpg"); //glass
////myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(12, 12, 12), Vec(), DIFF); //lite
//myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(14, 14, 14), Vec(), DIFF); //lite
//
//myworld->addObj(Vec(50, 25, 95), Vec(), Vec(1, 0.5, 0.3) * 0.94, SPEC, 25,"Meshes/arma_0.01.obj");
//
//// myworld->addPlane(-75,Vec(0,0,0),Vec(1,1,1),Vec(0,0,-1) ,DIFF);


//
////Final1 Scene:
//myworld->addSphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF); //left
//myworld->addSphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF);   //right
//
//myworld->addSphere(1e5, Vec(50, 40.8, 1e5), Vec(), Vec(.75, .75, .75), DIFF, 30000, "sourcepic/marble.bmp"); //back
//
////myworld->addSphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(0.75,0.35,.25), Vec(),           DIFF); //front
//myworld->addSphere(1e5, Vec(50, 1e5, 81.6), Vec(), Vec(.75, .75, .75), DIFF, 4000 , "sourcepic/star.jpg");    //bottom
//myworld->addSphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF);   //top
//
////myworld->addSphere(16, Vec(20, 16, 30),       Vec(), Vec(1, 1, 1), DIFF, 3, "sourcepic/huaji.jpeg" ); //mirror
//myworld->addSphere(16, Vec(70, 60, 50),       Vec(), Vec(1, 1, 1)*.8, SPEC); //mirror
//
//
//myworld->addSphere(600, Vec(50, 681.6 - .27, 81.6), Vec(14, 14, 14), Vec(), DIFF); //lite
//
//myworld->addObj(Vec(50 , 40, 115), Vec(), Vec(1, 0.7, 0.3) * 0.92, REFR, 30,"Meshes/dragon_0.01.obj");
//

//
////Final1 Scene:
//myworld->addSphere(2.5e3,   Vec(.82,.92,-2)*1e4,    Vec(1,1,1)*.9e2,     Vec(), DIFF); //left
//myworld->addSphere(2.5e4, Vec(50, 0, 0),  Vec(0.114, 0.133, 0.212)*1e-2,  Vec(.216,.384,1)*0.003, DIFF);   //right
//
//myworld->addSphere(5e0,   Vec(-.2,0.16,-1)*1e4, Vec(1.00, 0.843, 0.698)*1e2,   Vec(), DIFF); //back
//myworld->addSphere(12e0,   Vec(-.1,0.17,-0.8)*1e4, Vec(1.00, 0.843, 0.698)*1e2,   Vec(), DIFF); //back
//myworld->addSphere(12e0,   Vec(-.1,0.23,-0.7)*1e4, Vec(1.00, 0.843, 0.698)*1e2,   Vec(), DIFF); //back
//
//myworld->addSphere(8e0,   Vec(.2,  0.18,-0.9)*1e4, Vec(1.00, 0.851, 0.710)*1e2,  Vec(), DIFF);    //bottom
//myworld->addSphere(5e0,   Vec(.3, 0.15,-1)*1e4, Vec(0.671, 0.780, 1.00)*1e2,   Vec(), DIFF);   //top
//
//myworld->addSphere(16.5,  Vec(17,0,47),         Vec(),              Vec(1,1,1)*.98, SPEC); //mirror
//myworld->addObj(Vec(65 , 15, 90), Vec(), Vec(1, 1, 1) * 0.92, REFR, 30,"Meshes/dragon_0.01.obj");
//
//myworld->addSphere(30, Vec(50, 181.6 - .27, 91.6), Vec(10, 10, 10), Vec(), DIFF); //lite
//myworld->addSphere(5e4,   Vec(-500,-5e4+0, 0),   Vec(),      Vec(1,1,1)*.35,  DIFF);
